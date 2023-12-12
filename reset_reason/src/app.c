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

/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/

#include "app_log.h"
#include "em_rmu.h"
#include "em_emu.h"

void app_init(void)
{
  uint32_t reason = RMU_ResetCauseGet();
#if defined(_EMU_RSTCAUSE_MASK)
  uint32_t fromRegister = EMU->RSTCAUSE;
#endif
#if defined(_RMU_RSTCAUSE_MASK)
  uint32_t fromRegister = RMU->RSTCAUSE;
#endif
  app_log("Board: %s, RSTCAUSE register: 0x%lx, RMU_ResetCauseGet() returns 0x%lx\n", SL_BOARD_NAME, fromRegister, reason);
}

/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void)
{
}
