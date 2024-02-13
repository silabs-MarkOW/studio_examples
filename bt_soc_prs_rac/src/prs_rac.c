#include <stdint.h>
#include <em_prs.h>
#include <em_cmu.h>
#include <em_gpio.h>
#include <app_log.h>

/* Declarations */
#define PORT_RAC_TX (gpioPortA)
#define PIN_RAC_TX (6u)
#define PORT_RAC_RX (gpioPortA)
#define PIN_RAC_RX (7u)

#ifdef PRS_ASYNC_CH_CTRL_SIGSEL_RACTX
#  define SOURCESEL (PRS_ASYNC_CH_CTRL_SOURCESEL_RAC)
#  define SIGSELTX (PRS_ASYNC_CH_CTRL_SIGSEL_RACTX)
#  define SIGSELRX (PRS_ASYNC_CH_CTRL_SIGSEL_RACRX)
#else
#  ifdef PRS_ASYNC_CH_CTRL_SIGSEL_RACLTX
#    define SOURCESEL (PRS_ASYNC_CH_CTRL_SOURCESEL_RAC)
#    define SIGSELTX (PRS_ASYNC_CH_CTRL_SIGSEL_RACLTX)
#    define SIGSELRX (PRS_ASYNC_CH_CTRL_SIGSEL_RACLRX)
#  else
#    error Find  SOURCESEL/SIGSEL define for your device
#  endif
#endif

#define P(X) app_log(#X ":%p\n",X);
#define Pd(X) app_log(#X ":%d\n",X);

/* Code */
void prs_rac_init(void) {
  volatile uint32_t * addr;
 CMU_ClockEnable(cmuClock_GPIO, true);
 CMU_ClockEnable(cmuClock_PRS, true);
 int rxChannel, txChannel;

 Pd(rxChannel= PRS_GetFreeChannel(prsTypeAsync));
 GPIO->PRSROUTE[0].ROUTEEN &= ~(0x1 << (rxChannel + _GPIO_PRS_ROUTEEN_ASYNCH0PEN_SHIFT));
 GPIO_PinModeSet(PORT_RAC_RX, PIN_RAC_RX, gpioModePushPull, 0);
 P(addr = &GPIO->PRSROUTE[0].ASYNCH0ROUTE);
 P(addr += rxChannel);
 *addr = ((uint32_t) PORT_RAC_TX << _GPIO_PRS_ASYNCH0ROUTE_PORT_SHIFT)
     | ((uint32_t) PIN_RAC_RX << _GPIO_PRS_ASYNCH0ROUTE_PIN_SHIFT);
 PRS_SourceAsyncSignalSet(rxChannel, SOURCESEL, SIGSELRX);
 GPIO->PRSROUTE[0].ROUTEEN |= 0x1 << (rxChannel + _GPIO_PRS_ROUTEEN_ASYNCH0PEN_SHIFT);

 Pd(txChannel = PRS_GetFreeChannel(prsTypeAsync));
 GPIO->PRSROUTE[0].ROUTEEN &= ~(0x1 << (txChannel + _GPIO_PRS_ROUTEEN_ASYNCH0PEN_SHIFT));
 GPIO_PinModeSet(PORT_RAC_TX, PIN_RAC_TX, gpioModePushPull, 0);
 P(addr = &GPIO->PRSROUTE[0].ASYNCH0ROUTE);
 P(addr += txChannel);
 *addr = ((uint32_t) PORT_RAC_TX << _GPIO_PRS_ASYNCH0ROUTE_PORT_SHIFT)
     | ((uint32_t) PIN_RAC_TX << _GPIO_PRS_ASYNCH0ROUTE_PIN_SHIFT);
 PRS_SourceAsyncSignalSet(txChannel, SOURCESEL, SIGSELTX);
 GPIO->PRSROUTE[0].ROUTEEN |= 0x1 << (txChannel + _GPIO_PRS_ROUTEEN_ASYNCH0PEN_SHIFT);

 Pd(PRS_GetFreeChannel(prsTypeAsync));
}
