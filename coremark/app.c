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
#include "sl_memory.h"

unsigned int CoreMark_Main(void);
extern void *_printf_float;

void print_cpuid(void) {
  uint32_t uint32 = *(uint32_t*)0xe000ed00;
  struct cpuid {
    uint32_t revision:4, partno:12, constant:4, variant:4, implementer:8;
  } *cpuid = (struct cpuid *)&uint32;
  const char *architecture = "unknown";
  const char *partno = "unknown: 0x3x (constant: 0x%x)";
  switch(cpuid->constant) {
    case 0xc:
      switch(cpuid->partno) {
        case 0xc20:
          architecture = "ARMv6-M";
          partno = "Cortex-M0";
          break;
        case 0xc60:
          architecture = "ARMv6-M";
          partno = "Cortex-M0+";
          break;
      }
      break;
    case 0xf:
      switch(cpuid->partno) {
        case 0xc24:
          architecture = "ARMv7-M";
          partno = "Cortex-M4";
          break;
        case 0xd21:
          architecture = "ARMv8-M";
          partno = "Cortex-M33";
          break;
        }
      break;
  }
  printf("CPUID:\n  architecture: %s\n  partno: ", architecture);
  printf(partno,cpuid->partno, cpuid->constant);
  printf("\n  revision: %d\n  variant: %d\n",cpuid->revision, cpuid->variant);
}
/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void)
{
  unsigned int total_ticks;
  (void)_printf_float;
  sl_memory_region_t region = sl_memory_get_heap_region();
  double Hz = CMU_ClockFreqGet(cmuClock_CORE);
  double MHz = Hz*1e-6;
  printf("heap: %p (%zd)\n",region.addr, region.size);
  printf("CORE frequency: %.0f\n",Hz);
  printf("Calling Coremark_Main()\n");
  total_ticks = CoreMark_Main();
  double elapsed = total_ticks / Hz;
  double coremark = ITERATIONS / elapsed;
  printf("Elapsed time: %.2f%s\n",elapsed,(elapsed < 10)?" (Consider increasing ITERATIONS)":"");
  printf("Coremark: %.2f Iterations/s\n",coremark);
  printf("Coremark/MHz: %.3f\n",coremark/MHz);
  print_cpuid();
}

/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void)
{
}
