#include "em_device.h"
#include "em_chip.h"
#include "em_core.h"
#include "em_cmu.h"
#include "em_emu.h"
#include "em_gpio.h"
#include "em_iadc.h"
#include "em_ldma.h"
#include "em_letimer.h"
#include "em_prs.h"

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

// Set CLK_ADC to 10 MHz
#define CLK_SRC_ADC_FREQ        20000000  // CLK_SRC_ADC
#define CLK_ADC_FREQ            10000000  // CLK_ADC - 10 MHz max in normal mode

/*
 * Specify the IADC input using the IADC_PosInput_t typedef.  This
 * must be paired with a corresponding macro definition that allocates
 * the corresponding ABUS to the IADC.  These are...
 *
 * GPIO->ABUSALLOC |= GPIO_ABUSALLOC_AEVEN0_ADC0
 * GPIO->ABUSALLOC |= GPIO_ABUSALLOC_AODD0_ADC0
 * GPIO->BBUSALLOC |= GPIO_BBUSALLOC_BEVEN0_ADC0
 * GPIO->BBUSALLOC |= GPIO_BBUSALLOC_BODD0_ADC0
 * GPIO->CDBUSALLOC |= GPIO_CDBUSALLOC_CDEVEN0_ADC0
 * GPIO->CDBUSALLOC |= GPIO_CDBUSALLOC_CDODD0_ADC0
 *
 * ...for port A, port B, and port C/D pins, even and odd, respectively.
 */
#define IADC_INPUT_0_PORT_PIN     iadcPosInputPortAPin5;

#define IADC_INPUT_0_BUS          ABUSALLOC
#define IADC_INPUT_0_BUSALLOC     GPIO_ABUSALLOC_AODD0_ADC0

// Desired LETIMER frequency in Hz
#define LETIMER_FREQ              10

// LETIMER GPIO toggle port/pin (toggled in EM2; requires port A/B GPIO)
#define LETIMER_OUTPUT_0_PORT     gpioPortB
#define LETIMER_OUTPUT_0_PIN      1

// Use specified LDMA/PRS channel
#define IADC_LDMA_CH              0
#define PRS_CHANNEL               3

// How many samples to capture
#define NUM_SAMPLES               1000

/*******************************************************************************
 ***************************   GLOBAL VARIABLES   *******************************
 ******************************************************************************/

// Globally declared LDMA link descriptor
static LDMA_Descriptor_t descriptor;

// Buffer for IADC samples
static uint32_t singleBuffer[NUM_SAMPLES];

// last sample read (LDMA XFERCNT)
static int16_t last_xfercnt = NUM_SAMPLES;

volatile bool rollover = false;

size_t get_samples(uint16_t *dest, size_t maxlen) {
  size_t count = 0;
  size_t index = NUM_SAMPLES - last_xfercnt;
  int16_t current_xfercnt;
  CORE_CRITICAL_SECTION(
      current_xfercnt= ((LDMA->CH[0].CTRL & _LDMA_CH_CTRL_XFERCNT_MASK) >> _LDMA_CH_CTRL_XFERCNT_SHIFT) + 1;
      if(rollover) {
          current_xfercnt -= NUM_SAMPLES;
      }
)
  while(last_xfercnt-- > current_xfercnt) {
      dest[count++] = singleBuffer[index++];
      if(NUM_SAMPLES == index) { // handle wrap around
          index = 0;
      }
      if(count == maxlen) {
          break;
      }
  }
  if(last_xfercnt < 0) { // this implies rollover is set
      rollover = false;
      last_xfercnt += NUM_SAMPLES;
  }
  return count;
}

/**************************************************************************//**
 * @brief  GPIO initialization
 *****************************************************************************/
void initGPIO(void)
{
  /*
   * Enable the GPIO register clock.
   *
   * Note: On EFR32xG21 devices, CMU_ClockEnable() calls have no effect
   * as clocks are enabled/disabled on-demand in response to peripheral
   * requests.  Deleting such lines is safe on xG21 devices and will
   * provide a small reduction in code size.
   */
  CMU_ClockEnable(cmuClock_GPIO, true);
}

/**************************************************************************//**
 * @brief  PRS initialization
 *****************************************************************************/
void initPRS(void)
{
  CMU_ClockEnable(cmuClock_PRS, true);

  // Connect the specified PRS channel to the LETIMER producer
  PRS_SourceAsyncSignalSet(PRS_CHANNEL,
                           PRS_ASYNC_CH_CTRL_SOURCESEL_LETIMER0,
                           PRS_LETIMER0_CH0);

  // Connect the specified PRS channel to the IADC as the consumer
  PRS_ConnectConsumer(PRS_CHANNEL,
                      prsTypeAsync,
                      prsConsumerIADC0_SINGLETRIGGER);
}

/**************************************************************************//**
 * @brief  IADC initialization
 *****************************************************************************/
void initIADC(void)
{
  // Declare initialization structures
  IADC_Init_t init = IADC_INIT_DEFAULT;
  IADC_AllConfigs_t initAllConfigs = IADC_ALLCONFIGS_DEFAULT;
  IADC_InitSingle_t initSingle = IADC_INITSINGLE_DEFAULT;

  // Single input structure
  IADC_SingleInput_t singleInput = IADC_SINGLEINPUT_DEFAULT;

  CMU_ClockEnable(cmuClock_IADC0, true);

  // Use the FSRC0 as the IADC clock so it can run in EM2
  CMU_ClockSelectSet(cmuClock_IADCCLK, cmuSelect_FSRCO);

  // Set the prescaler needed for the intended IADC clock frequency
  init.srcClkPrescale = IADC_calcSrcClkPrescale(IADC0, CLK_SRC_ADC_FREQ, 0);

  /*
   * These two settings are modified from the defaults to reduce the
   * IADC current.  In low-frequency use cases, such as this example,
   * iadcWarmupNormal shuts down the IADC between conversions, which
   * reduces current at the expense of requiring 5 microseconds of
   * warm-up time before a conversion can begin.
   *
   * In cases where a PRS event triggers single conversions, enabling
   * iadcClkSuspend1 gates off the ADC_CLK until the PRS trigger event
   * occurs and again upon the completion of the channel converted.
   */
  init.warmup = iadcWarmupNormal;
  init.iadcClkSuspend1 = true;

  /*
   * Configuration 0 is used by both scan and single conversions by
   * default.  Use internal bandgap as the reference and specify the
   * reference voltage in mV.
   *
   * Resolution is not configurable directly but is based on the
   * selected oversampling ratio (osrHighSpeed), which defaults to
   * 2x and generates 12-bit results.
   */
  initAllConfigs.configs[0].reference = iadcCfgReferenceInt1V2;
  initAllConfigs.configs[0].vRef = 1210;
  initAllConfigs.configs[0].osrHighSpeed = iadcCfgOsrHighSpeed2x;
  initAllConfigs.configs[0].analogGain = iadcCfgAnalogGain0P5x;

  /*
   * CLK_SRC_ADC is prescaled to derive the intended CLK_ADC frequency.
   *
   * Based on the default 2x oversampling rate (OSRHS)...
   *
   * conversion time = ((4 * OSRHS) + 2) / fCLK_ADC
   *
   * ...which, results in a maximum single-channel sampling rate of
   * 1 Msps because there is no need to change the input multiplexer
   * (thus incurring a 2-clock switching delay).
   */
  initAllConfigs.configs[0].adcClkPrescale = IADC_calcAdcClkPrescale(IADC0,
                                                                     CLK_ADC_FREQ,
                                                                     0,
                                                                     iadcCfgModeNormal,
                                                                     init.srcClkPrescale);

  /*
   * Trigger conversions on the PRS1 rising edge input (PRS1 is not a
   * specific channel but simply the dedicated trigger input for single
   * conversions.  PRS0 serves the same purpose for scan conversions.
   * Note that the IADC_TriggerSel_t typedef specifies PRS0 even when
   * PRS1 is used because the bit field encodings in the relevant
   * IADC_TRIGGER register are the same).
   *
   * Set the SINGLEFIFODVL flag when there are 2 entries in the scan
   * FIFO.  Note that in this example, the interrupt associated with
   * the SINGLEFIFODVL flag in the IADC_IF register is not used.
   *
   * Enable DMA wake-up to save the results when the specified FIFO
   * level is hit.
   *
   * Allow a single conversion to start as soon as there is a trigger
   * event.
   */
  initSingle.triggerSelect = iadcTriggerSelPrs0PosEdge;
  initSingle.dataValidLevel = iadcFifoCfgDvl2;
  initSingle.fifoDmaWakeup = true;
  initSingle.start = true;

  /*
   * Specify the input channel.  When negInput = iadcNegInputGnd, the
   * conversion is single-ended.
   */
  singleInput.posInput   = IADC_INPUT_0_PORT_PIN;
  singleInput.negInput   = iadcNegInputGnd;

  // Initialize IADC
  IADC_init(IADC0, &init, &initAllConfigs);

  // Initialize single conversion
  IADC_initSingle(IADC0, &initSingle, &singleInput);

  // Allocate the analog bus for IADC0 inputs
  GPIO->IADC_INPUT_0_BUS |= IADC_INPUT_0_BUSALLOC;
}

/**************************************************************************//**
 * @brief LETIMER initialization
 *****************************************************************************/
void initLETIMER(float frequency)
{
  LETIMER_Init_TypeDef letimerInit = LETIMER_INIT_DEFAULT;
  CMU_ClockEnable(cmuClock_LETIMER0, true);

  // Calculate the top value (frequency) based on clock source
  uint32_t topValue = CMU_ClockFreqGet(cmuClock_LETIMER0) / frequency;

  // Reload top on underflow, pulse output, and run in free mode
  letimerInit.comp0Top = true;
  letimerInit.topValue = topValue;
  letimerInit.ufoa0 = letimerUFOAPulse;
  letimerInit.repMode = letimerRepeatFree;

  // Enable LETIMER output 0
  GPIO->LETIMERROUTE[0].ROUTEEN = GPIO_LETIMER_ROUTEEN_OUT0PEN;
  GPIO->LETIMERROUTE[0].OUT0ROUTE = (LETIMER_OUTPUT_0_PORT << _GPIO_LETIMER_OUT0ROUTE_PORT_SHIFT) |
                                    (LETIMER_OUTPUT_0_PIN << _GPIO_LETIMER_OUT0ROUTE_PIN_SHIFT);

  // Initialize LETIMER
  LETIMER_Init(LETIMER0, &letimerInit);
}

/**************************************************************************//**
 * @brief
 *   LDMA initialization
 *
 * @param[in] buffer
 *   pointer to the array where ADC results will be stored.
 * @param[in] size
 *   size of the array
 *****************************************************************************/
void initLDMA(uint32_t *buffer, uint32_t size)
{
  LDMA_Init_t init = LDMA_INIT_DEFAULT;

  // Trigger LDMA transfer on IADC single completion
  LDMA_TransferCfg_t transferCfg =
    LDMA_TRANSFER_CFG_PERIPHERAL(ldmaPeripheralSignal_IADC0_IADC_SINGLE);

  /*
   * Set up a linked descriptor to save scan results to the
   * user-specified buffer.  By linking the descriptor to itself
   * (the last argument is the relative jump in terms of the number of
   * descriptors), transfers will run continuously until firmware
   * otherwise stops them.
   */
  descriptor =
    (LDMA_Descriptor_t)LDMA_DESCRIPTOR_LINKREL_P2M_WORD(&IADC0->SINGLEFIFODATA, buffer, size, 0);

  // Initialize LDMA with default configuration
  LDMA_Init(&init);

  /*
   * Start the LDMA channel.  The first transfer will not occurs until
   * the LETIMER counts down to 0 and generates a pulse that is
   * routed to the IADC scan trigger input via the PRS.
   */
  LDMA_StartTransfer(IADC_LDMA_CH, &transferCfg, &descriptor);
}

/**************************************************************************//**
 * @brief  LDMA IRQ Handler
 *****************************************************************************/
void LDMA_IRQHandler(void)
{
  // Clear interrupt flags
  LDMA_IntClear(1 << IADC_LDMA_CH);
  rollover = true;
}

void init_sampling(float frequency) {
  initGPIO();
  initPRS();
  initIADC();
  initLDMA(singleBuffer, NUM_SAMPLES);

  // Initialize the LETIMER (starts conversions)
  initLETIMER(frequency);
}
