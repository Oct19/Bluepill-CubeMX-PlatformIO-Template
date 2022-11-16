/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usb_serial.h"
#include "usbd_cdc_if.h"
#include "rtc.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
int counter01, counter02, counter03, counter04 = 0;

/* USER CODE END Variables */
/* Definitions for blink01 */
osThreadId_t blink01Handle;
const osThreadAttr_t blink01_attributes = {
    .name = "blink01",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityLow,
};
/* Definitions for blink02 */
osThreadId_t blink02Handle;
const osThreadAttr_t blink02_attributes = {
    .name = "blink02",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityLow1,
};
/* Definitions for USB_Serial */
osThreadId_t USB_SerialHandle;
const osThreadAttr_t USB_Serial_attributes = {
    .name = "USB_Serial",
    .stack_size = 256 * 4,
    .priority = (osPriority_t)osPriorityHigh,
};
/* Definitions for OLED */
osThreadId_t OLEDHandle;
const osThreadAttr_t OLED_attributes = {
    .name = "OLED",
    .stack_size = 256 * 4,
    .priority = (osPriority_t)osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartBlink01(void *argument);
void StartBlink02(void *argument);
void StartUSB_Serial(void *argument);
void StartOLED(void *argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
 * @brief  FreeRTOS initialization
 * @param  None
 * @retval None
 */
void MX_FREERTOS_Init(void)
{
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of blink01 */
  blink01Handle = osThreadNew(StartBlink01, NULL, &blink01_attributes);

  /* creation of blink02 */
  blink02Handle = osThreadNew(StartBlink02, NULL, &blink02_attributes);

  /* creation of USB_Serial */
  USB_SerialHandle = osThreadNew(StartUSB_Serial, NULL, &USB_Serial_attributes);

  /* creation of OLED */
  OLEDHandle = osThreadNew(StartOLED, NULL, &OLED_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */
}

/* USER CODE BEGIN Header_StartBlink01 */
/**
 * @brief  Function implementing the blink01 thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartBlink01 */
void StartBlink01(void *argument)
{
  /* init code for USB_DEVICE */
  MX_USB_DEVICE_Init();
  /* USER CODE BEGIN StartBlink01 */
  /* Infinite loop */
  for (;;)
  {
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    osDelay(100);
  }
  /* USER CODE END StartBlink01 */
}

/* USER CODE BEGIN Header_StartBlink02 */
/**
 * @brief Function implementing the blink02 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartBlink02 */
void StartBlink02(void *argument)
{
  /* USER CODE BEGIN StartBlink02 */
  /* Infinite loop */
  for (;;)
  {
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
    osDelay(110);
  }
  /* USER CODE END StartBlink02 */
}

/* USER CODE BEGIN Header_StartUSB_Serial */
/**
 * @brief Function implementing the USB_Serial thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartUSB_Serial */
void StartUSB_Serial(void *argument)
{
  /* USER CODE BEGIN StartUSB_Serial */
  /* Infinite loop */
  for (;;)
  {
    char timestamp[30];
    RTC_datetime(timestamp);
    CDC_Transmit_FS((uint8_t *)timestamp, strlen(timestamp));
    osDelay(USB_serial_wait_time);
    const char *message = "Hello\n\r";
    CDC_Transmit_FS((uint8_t *)message, strlen(message));
    osDelay(500 - USB_serial_wait_time);

    usb_serial_echo();
    osDelay(500);
  }
  /* USER CODE END StartUSB_Serial */
}

/* USER CODE BEGIN Header_StartOLED */
/**
 * @brief Function implementing the OLED thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartOLED */
void StartOLED(void *argument)
{
  /* USER CODE BEGIN StartOLED */
  /* Infinite loop */
  for (;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartOLED */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
