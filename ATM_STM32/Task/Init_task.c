/*****************************************************************/
/*          _____   _            __   _                          */
/*         |  ___| | |  _   _   / _| (_)  _ __    ___            */
/*         | |_    | | | | | | | |_  | | | '__|  / _ \           */
/*         |  _|   | | | |_| | |  _| | | | |    |  __/           */
/*         |_|     |_|  \__, | |_|   |_| |_|     \___|           */
/*                      |___/                                    */
/*---------------------------------------------------------------*/
/* This file is subject to the terms and conditions defined in   */
/* file 'LICENSE.txt', which is part of this source code package.*/
/*****************************************************************/

#include "Init_task.h"

#ifdef __cplusplus
extern "C" {
#endif

/*--- Private dependencies ------------------------------------------------------------*/
#include "bsp_adcdetect.h"
#include "adc_collect.h"
#include "bsp_usart.h"
#include "watchdog.h"
#include "main_fsm.h"
#include "detect_timer.h"
#include "bsp_ws2812.h"
#include "light_show.h"
#include "systime.h"
#include "Main_Task.h"			 //主任务
#include "UsartInteract_Task.h"	 // 串口交互任务
/*--- Public variable definitions -----------------------------------------------------*/
// main_sta_t sta = MAIN_STA_STARTUP;
/*--- Private macros ------------------------------------------------------------------*/
#include "button.h"
/*--- Private type definitions --------------------------------------------------------*/

/*--- Private variable definitions ----------------------------------------------------*/

/*--- Private function declarations ---------------------------------------------------*/
static void Device_Init() {
	USART3_DMA_Init();
	Button_Init();
	bsp_WS2812_Init();
	WS2812_CheckSelf();
	FeedIndependentWDOG();
	Detect_Timer_Init();
#ifdef MAIN_FSM
	bsp_ADC_Update();
#endif

#ifdef DOUBLE_BUFFER
	Enable_Uart3();
#endif
}
/*--- Private function definitions ----------------------------------------------------*/
void Init_taskFunction(void *argument) {
	Device_Init();
#ifdef NO_FSM
	ADC_Detect();
	osDelay(100);
	FeedIndependentWDOG();
#endif

	Main_TaskCreate(osPriorityNormal);			 //主任务
	UsartInteract_TaskCreate(osPriorityNormal);	 // 串口交互任务
	WS2812_LIGHTOFF();

	vTaskDelete(NULL);
}
/*--- Public function definitions -----------------------------------------------------*/

#ifdef __cplusplus
}
#endif
