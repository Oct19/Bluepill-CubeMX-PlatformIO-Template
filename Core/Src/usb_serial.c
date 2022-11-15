/**
 * @file    usb_serial.c
 * @author  Cai Dingkun <caidingkun@outlook.com>
 * @brief   This file provides code for the configuration
 *          of USB serial port. Default Baud rate: 9600, Line ending: CRLF
 * @version 0.1
 * @date    2022-11-10
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "usb_serial.h"

#include "usb_device.h"
#include "usbd_cdc_if.h"

/**
 * @brief externally defined in usbd_cdc_if.c
 *
 * In usbd_cdc_if.c, the function int8_t CDC_Receive_FS() has been modified
 * to store received data into USB_serial_buf.
 *
 */
uint8_t USB_serial_buf[64];

/**
 * @brief Repeat message that sent to STM32 through USB serial port. Line ending: CRLF
 *
 */
void usb_serial_echo(void)
{
    if (USB_serial_buf != NULL)
    {
        CDC_Transmit_FS(USB_serial_buf, strlen((const char *)USB_serial_buf));
    }
}