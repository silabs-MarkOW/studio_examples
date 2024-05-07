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

struct cpuid {
  uint32_t revision:4, partno:12, architecture:4, variant:4, implementer:8;
};
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
  uint32_t uicpuid = *(uint32_t*)0xe000ed00;
  struct cpuid *cpuid = &uicpuid;
  printf("CPUID:\n  architecture: ");
  if(0xc == cpuid->architecture) printf("ARMv6-M\n");
  else printf("0x%x\n",cpuid->architecture);
  printf("  partno: ");
  if(0xc20 == cpuid->partno) printf("Cortex-M0");
  else if(0xc60 == cpuid->partno) printf("Cortex-M0+\n");
  else printf("%03x\n",cpuid->partno);
}

/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void)
{
}
