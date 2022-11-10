/**
 * @file    usb_serial.c
 * @author  Cai Dingkun <caidingkun@outlook.com>
 * @brief   This file provides code for the configuration
 *          of USB serial port.
 * @version 0.1
 * @date    2022-11-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "usb_serial.h"

#include "usb_device.h"
#include "usbd_cdc_if.h"

uint8_t USB_serial_buf[64];

void usb_serial_send(char *data)
{
    CDC_Transmit_FS((uint8_t *)data, strlen(data));
}

void usb_serial_repeat(void)
{
    if (USB_serial_buf != NULL)
    {
        CDC_Transmit_FS((uint8_t *)USB_serial_buf, strlen(USB_serial_buf));
    }
}