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
#include "app_log.h"
#include "sl_usbd_class_msc_scsi.h"
#include "sl_usbd_class_msc_scsi_instances.h"
#include "app_assert.h"
#include <stdlib.h>

struct sector {
  uint32_t words[128];
} *image;

bool attached = false;

sl_status_t api_init(sl_usbd_msc_scsi_lun_t *p_scsi_lun) {
  app_log("api_init(%p)\r\n",p_scsi_lun);             ///< Initialize storage driver.
  return SL_STATUS_OK;
}

sl_status_t api_open(sl_usbd_msc_scsi_lun_t *p_scsi_lun) {             ///< Request exclusive access to media.
  app_log("api_open(%p)\r\n",p_scsi_lun);             ///< Initialize storage driver.
  return SL_STATUS_OK;
}

sl_status_t api_close(sl_usbd_msc_scsi_lun_t *p_scsi_lun) {            ///< Release exclusive access to media.
  app_log("api_close(%p)\r\n",p_scsi_lun);             ///< Initialize storage driver.
  return SL_STATUS_OK;
}

sl_status_t api_get_capacity(sl_usbd_msc_scsi_lun_t    *p_scsi_lun,
                              sl_usbd_msc_scsi_lb_qty_t *p_nbr_blks,
                              uint32_t                  *p_blk_size) {   ///< Retrieve storage media capacity.
  app_log("api_get_capacity(%p)\r\n",p_scsi_lun);
  *p_nbr_blks = 512;
  *p_blk_size = 512;
  return SL_STATUS_OK;
}

sl_status_t api_read(sl_usbd_msc_scsi_lun_t  *p_scsi_lun,
                       sl_usbd_msc_scsi_lba_t  blk_addr,
                       uint32_t                nbr_blks,
                       uint8_t                 *p_data_buf) {            ///< Read data from storage media.
  app_log("api_read(%p, blk_addr:0x%lx, nbr_blks: 0x%lx)\r\n",p_scsi_lun,blk_addr,nbr_blks);
  memcpy(p_data_buf, &image[blk_addr], 512*nbr_blks);
  return SL_STATUS_OK;
}

sl_status_t api_write(sl_usbd_msc_scsi_lun_t  *p_scsi_lun,
                        sl_usbd_msc_scsi_lba_t  blk_addr,
                        uint32_t                nbr_blks,
                        uint8_t                 *p_data_buf) {           ///< Write data to storage media.
  app_log("api_write(%p, blk_addr:0x%lx, nbr_blks: 0x%lx)\r\n",p_scsi_lun,blk_addr,nbr_blks);
  memcpy(&image[blk_addr], p_data_buf, 512*nbr_blks);
  return SL_STATUS_OK;
}

sl_usbd_msc_scsi_lun_api_t api = { .init = api_init, .open = api_open, .close = api_close, .get_capacity = api_get_capacity, .read = api_read, .write = api_write };
sl_usbd_msc_scsi_lun_info_t info = { &api, "Monkey", "Big Brain", 1, false};
sl_usbd_msc_scsi_lun_t *lun;

/*******************************************************************************
 ***************************   HOOK FUNCTIONS  *********************************
 ******************************************************************************/

/***************************************************************************//**
 *                          sl_usbd_on_bus_event()
 *
 * @brief  USB bus events.
 ******************************************************************************/
void sl_usbd_on_bus_event(sl_usbd_bus_event_t event)
{
  switch (event) {
    case SL_USBD_EVENT_BUS_CONNECT:
      // called when usb cable is inserted in a host controller
      app_log("sl_usbd_on_bus_event(SL_USBD_EVENT_BUS_CONNECT)\r\n");
      break;

    case SL_USBD_EVENT_BUS_DISCONNECT:
      // called when usb cable is removed from a host controller
      app_log("sl_usbd_on_bus_event(SL_USBD_EVENT_BUS_DISCONNECT)\r\n");
      break;

    case SL_USBD_EVENT_BUS_RESET:
      // called when the host sends reset command
      app_log("sl_usbd_on_bus_event(SL_USBD_EVENT_BUS_RESET)\r\n");
      break;

    case SL_USBD_EVENT_BUS_SUSPEND:
      // called when the host sends suspend command
      app_log("sl_usbd_on_bus_event(SL_USBD_EVENT_BUS_SUSPEND)\r\n");
      break;

    case SL_USBD_EVENT_BUS_RESUME:
      // called when the host sends wake up command
      app_log("sl_usbd_on_bus_event(SL_USBD_EVENT_BUS_RESUME)\r\n");
      break;

    default:
      break;
  }
}

/***************************************************************************//**
 *                         sl_usbd_on_config_event()
 *
 * @brief  USB configuration events.
 ******************************************************************************/
void sl_usbd_on_config_event(sl_usbd_config_event_t event, uint8_t config_nbr)
{
  (void)config_nbr;

  switch (event) {
    case SL_USBD_EVENT_CONFIG_SET:
      // called when the host sets a configuration after reset
      app_log("sl_usbd_on_config_event(SL_USBD_EVENT_CONFIG_SET,%d)\r\n",config_nbr);
      break;

    case SL_USBD_EVENT_CONFIG_UNSET:
      // called when a configuration is unset due to reset command
      app_log("sl_usbd_on_config_event(SL_USBD_EVENT_CONFIG_UNSET,%d)\r\n",config_nbr);
      break;

    default:
      break;
  }
}

void sl_usbd_msc_scsi_msc_scsi_on_enable_event(void) {
  app_log("sl_usbd_msc_scsi_msc_scsi_on_enable_event()\r\n");
  if(!attached) {
      sl_status_t sc;
      sc = sl_usbd_msc_scsi_lun_attach(lun);
      app_assert_status(sc);
      attached = true;
  }
}

void sl_usbd_msc_scsi_msc_scsi_on_disable_event(void) {
  app_log("sl_usbd_msc_scsi_msc_scsi_on_disable_event()\r\n");
}

void sl_usbd_msc_scsi_msc_scsi_on_host_eject_event(uint8_t lu_nbr) {
  app_log("sl_usbd_msc_scsi_msc_scsi_on_host_eject_event(uint8_t lu_nbr:%d)\r\n",lu_nbr);
  attached = false;
}

/***************************************************************************//**
 * Initialize application.
 ******************************************************************************/
void app_init(void)
{
  sl_status_t sc;
  image = malloc(512*512);
  app_assert(image,"malloc failure\r\n");
  app_log("app_init()\r\n");
  sc = sl_usbd_msc_scsi_lun_add(sl_usbd_msc_scsi_msc_scsi_number, &info, &lun);
  app_assert_status(sc);//,"[%x] sl_usbd_msc_scsi_lun_add failed\r\n");
}
