/*****************************************************************************
 *   Copyright(C)2009-2019 by VSF Team                                       *
 *                                                                           *
 *  Licensed under the Apache License, Version 2.0 (the "License");          *
 *  you may not use this file except in compliance with the License.         *
 *  You may obtain a copy of the License at                                  *
 *                                                                           *
 *     http://www.apache.org/licenses/LICENSE-2.0                            *
 *                                                                           *
 *  Unless required by applicable law or agreed to in writing, software      *
 *  distributed under the License is distributed on an "AS IS" BASIS,        *
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. *
 *  See the License for the specific language governing permissions and      *
 *  limitations under the License.                                           *
 *                                                                           *
 ****************************************************************************/

#ifndef __OSA_HAL_DRIVER_ESPRESSIF_ESP32S2_USB_H__
#define __OSA_HAL_DRIVER_ESPRESSIF_ESP32S2_USB_H__

/*============================ INCLUDES ======================================*/
#include "hal/vsf_hal.h"

#if VSF_USE_USB_DEVICE == ENABLED || VSF_USE_USB_HOST == ENABLED

#include "hal/interface/vsf_interface_usb.h"

// for dedicated vk_dwcotg_hw_info_t
#include "component/usb/driver/otg/dwcotg/vsf_dwcotg_hw.h"

/*============================ MACROS ========================================*/
/*============================ MACROFIED FUNCTIONS ===========================*/

#define __USB_OTG_DEF(__N, __VALUE)                                             \
    extern esp32s2_usb_t USB_OTG##__N##_IP;                                     \
    extern const i_usb_dc_ip_t VSF_USB_DC##__N##_IP;                            \
    extern const i_usb_hc_ip_t VSF_USB_HC##__N##_IP;
#define _USB_OTG_DEF(__N, __VALUE)          __USB_OTG_DEF(__N, __VALUE)
#define USB_OTG_DEF(__N, __VALUE)           _USB_OTG_DEF(__N, __VALUE)

/*============================ TYPES =========================================*/

typedef struct esp32s2_usb_const_t {
    uint8_t dc_ep_num;
    uint8_t hc_ep_num;
    periph_module_t periph_module;
    int intr_source;
    void *reg;

    implement(vk_dwcotg_hw_info_t)
} esp32s2_usb_const_t;

typedef struct esp32s2_usb_t {
    bool is_host;
    // should be intr_handle_t intr_handle, but to avoid namespace pollution
    void * intr_handle;
    struct {
        usb_ip_irq_handler_t irq_handler;
        void *param;
    } callback;
    const esp32s2_usb_const_t *param;
} esp32s2_usb_t;

/*============================ INCLUDES ======================================*/

#include "./hc/usbh.h"
#include "./dc/usbd.h"

/*============================ GLOBAL VARIABLES ==============================*/

REPEAT_MACRO(USB_OTG_COUNT, USB_OTG_DEF, NULL)

/*============================ INCLUDES ======================================*/
/*============================ PROTOTYPES ====================================*/

#endif
#endif
/* EOF */
