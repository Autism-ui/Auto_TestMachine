/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * File Name          : freertos.c
 * Description        : Code for freertos applications
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
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
#include "adc.h"
#include "usart.h"
#include "button.h"
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

/* USER CODE END Variables */
/* Definitions for Init_Task */
osThreadId_t Init_TaskHandle;
const osThreadAttr_t Init_Task_attributes = {
  .name = "Init_Task",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 512 * 4
};
/* Definitions for Detect_Timer */
osTimerId_t Detect_TimerHandle;
const osTimerAttr_t Detect_Timer_attributes = {
  .name = "Detect_Timer"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void Init_taskFunction(void *argument);
void Detect_Timer_Callback(void *argument);

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

  /* Create the timer(s) */
  /* creation of Detect_Timer */
  Detect_TimerHandle = osTimerNew(Detect_Timer_Callback, osTimerPeriodic, NULL, &Detect_Timer_attributes);

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of Init_Task */
  Init_TaskHandle = osThreadNew(Init_taskFunction, NULL, &Init_Task_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_Init_taskFunction */
/**
 * @brief  Function implementing the Init_Task thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_Init_taskFunction */
__weak void Init_taskFunction(void *argument)
{
  /* USER CODE BEGIN Init_taskFunction */
  TickType_t xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();

  /* Infinite loop */
  for (;;)
  {
    vTaskDelayUntil(&xLastWakeTime, 1000 / portTICK_RATE_MS);
  }
  //	vTaskDelete(NULL);
  /* USER CODE END Init_taskFunction */
}

/* Detect_Timer_Callback function */
__weak void Detect_Timer_Callback(void *argument)
{
  /* USER CODE BEGIN Detect_Timer_Callback */
	
  /* USER CODE END Detect_Timer_Callback */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
