#include "log.h"
#include "sl_simple_button_instances.h"
#include "external_signals.h"
#include "sl_bt_api.h"

// this will be called from interrupt context
void sl_button_on_change(const sl_button_t *handle)
{
  if(handle->get_state(handle)) {
      sl_bt_external_signal(BUTTON_PRESS);
  } else {
      sl_bt_external_signal(BUTTON_RELEASE);
  }
}
