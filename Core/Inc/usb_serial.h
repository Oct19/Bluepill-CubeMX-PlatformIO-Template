/**
 * @file    usb_serial.h
 * @author  Cai Dingkun <caidingkun@outlook.com>
 * @brief   This file contains all the function prototypes for
 *          the usb_serial.c file
 * @version 0.1
 * @date    2022-11-10
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef __USB_SERIAL_H__
#define __USB_SERIAL_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
/**
 * @brief Send to PC
 * 
 * @param data string
 */
void usb_serial_send(char *data);

void usb_serial_repeat(void);

#ifdef __cplusplus
}
#endif
#endif /*__ USB_SERIAL_H__ */
