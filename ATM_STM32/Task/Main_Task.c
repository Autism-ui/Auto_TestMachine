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

#include "Main_Task.h"

#ifdef __cplusplus
extern "C" {
#endif

/*--- Private dependencies ------------------------------------------------------------*/
#include "main_fsm.h"
#include "button.h"
#include "watchdog.h"
/*--- Public variable definitions -----------------------------------------------------*/

/*--- Private macros ------------------------------------------------------------------*/

/*--- Private type definitions --------------------------------------------------------*/

/*--- Private variable definitions ----------------------------------------------------*/
static TaskHandle_t MainTaskHandle;
/*--- Private function declarations ---------------------------------------------------*/

/*--- Private function definitions ----------------------------------------------------*/

/*--- Public function definitions -----------------------------------------------------*/
void Main_Task(void *param) {
	TickType_t xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	int count	  = 0;
	for(;;) {
		count++;
		if(count >= 40) {
			FeedIndependentWDOG();
			count = 0;
		}
		Button_Switch();
		vTaskDelayUntil(&xLastWakeTime, 10 / portTICK_RATE_MS);
	}
}

void Main_TaskCreate(osPriority_t _priority) {
	BaseType_t ret;
	ret = xTaskCreate(Main_Task, "MainTask", 512, NULL, _priority, &MainTaskHandle);
	if(ret != pdTRUE) {
	}
}

#ifdef __cplusplus
}
#endif
