
#include "em_cmu.h"
#include "em_gpio.h"
#include "em_prs.h"

void show_rac_init(void) {
  CMU_ClockEnable(cmuClock_GPIO,1);
  CMU_ClockEnable(cmuClock_PRS, 1);
  GPIO_PinModeSet(gpioPortF,5,gpioModePushPull,0);
  GPIO_PinModeSet(gpioPortF,6,gpioModePushPull,0);
  PRS->CH[0].CTRL = PRS_RAC_TX;
  PRS->CH[1].CTRL = PRS_RAC_RX;
  PRS->ROUTELOC0 |= (5u << 0u);
  PRS->ROUTELOC0 |= (5u << 8u);
  PRS->ROUTEPEN |= (1u << 0u) | (1u << 1u);
}
