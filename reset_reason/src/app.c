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
#include "sl_simple_button_instances.h"

volatile bool button_event = false;

void app_init(void)
{
  uint32_t reason = RMU_ResetCauseGet();
#if defined(_EMU_RSTCAUSE_MASK)
  uint32_t fromRegister = EMU->RSTCAUSE;
#endif
#if defined(_RMU_RSTCAUSE_MASK)
  uint32_t fromRegister = RMU->RSTCAUSE;
#endif
  app_log("Board: %s, RSTCAUSE reg: 0x%lx, RMU_ResetCauseGet(): 0x%lx\n", SL_BOARD_NAME, fromRegister, reason);
  sl_simple_button_init(&sl_button_btn0);
  sl_simple_button_enable(&sl_button_btn0);
}

void sl_button_on_change(const sl_button_t *handle)
{
  if(handle->get_state(handle)) { // print message of press, reset on release
      button_event = true;
  } else {
      NVIC_SystemReset();
  }
}

/***************************************************************************//**
 * App ticking function.
 ******************************************************************************/
void app_process_action(void)
{
  if(button_event) {
      app_log("Button pressed, issuing software reset\n");
      button_event = false;
  }
}
