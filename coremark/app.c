/***************************************************************************//**
 * @file
 * @brief Top level application functions
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/

#include <stdio.h>
#include "em_cmu.h"

unsigned int CoreMark_Main(void);
extern void *_printf_float;
/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void)
{
  unsigned int total_ticks;
  (void)_printf_float;
  double Hz = CMU_ClockFreqGet(cmuClock_CORE);
  double MHz = Hz*1e-6;
  printf("CORE frequency: %.0f\n",Hz);
  printf("Calling Coremark_Main()\n");
  total_ticks = CoreMark_Main();
  double elapsed = total_ticks / Hz;
  double coremark = ITERATIONS / elapsed;
  printf("Elapsed time: %.2f\n",elapsed);
  printf("Coremark: %.2f Iterations/s\n",coremark);
  printf("Coremark/MHz: %.3f\n",coremark/MHz);
}

/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void)
{
}
