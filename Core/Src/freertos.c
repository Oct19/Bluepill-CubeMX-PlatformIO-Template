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
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for blink02 */
osThreadId_t blink02Handle;
const osThreadAttr_t blink02_attributes = {
  .name = "blink02",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow1,
};
/* Definitions for USBSerial01 */
osThreadId_t USBSerial01Handle;
const osThreadAttr_t USBSerial01_attributes = {
  .name = "USBSerial01",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for USBSerial02 */
osThreadId_t USBSerial02Handle;
const osThreadAttr_t USBSerial02_attributes = {
  .name = "USBSerial02",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal1,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartBlink01(void *argument);
void StartBlink02(void *argument);
void StartUSBSerial01(void *argument);
void StartUSBSerial02(void *argument);

extern void MX_USB_DEVICE_Init(void);
void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
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

  /* creation of USBSerial01 */
  USBSerial01Handle = osThreadNew(StartUSBSerial01, NULL, &USBSerial01_attributes);

  /* creation of USBSerial02 */
  USBSerial02Handle = osThreadNew(StartUSBSerial02, NULL, &USBSerial02_attributes);

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
    counter01++;
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
    counter02++;
    osDelay(110);
  }
  /* USER CODE END StartBlink02 */
}

/* USER CODE BEGIN Header_StartUSBSerial01 */
/**
 * @brief Function implementing the USBSerial01 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartUSBSerial01 */
void StartUSBSerial01(void *argument)
{
  /* USER CODE BEGIN StartUSBSerial01 */
  /* Infinite loop */
  for (;;)
  {
    char *data = "Hello world\n";
    CDC_Transmit_FS((uint8_t *)data, strlen(data));
    osDelay(500);
    usb_serial_echo();
    osDelay(500);
  }
  /* USER CODE END StartUSBSerial01 */
}

/* USER CODE BEGIN Header_StartUSBSerial02 */
/**
 * @brief Function implementing the USBSerial02 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartUSBSerial02 */
void StartUSBSerial02(void *argument)
{
  /* USER CODE BEGIN StartUSBSerial02 */
  /* Infinite loop */
  for (;;)
  {
    osDelay(1000);
  }
  /* USER CODE END StartUSBSerial02 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

