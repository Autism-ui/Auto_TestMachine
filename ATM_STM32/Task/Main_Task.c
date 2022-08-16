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
#include "watchdog.h"
#include "main_fsm.h"
/*--- Public variable definitions -----------------------------------------------------*/

/*--- Private macros ------------------------------------------------------------------*/

/*--- Private type definitions --------------------------------------------------------*/

/*--- Private variable definitions ----------------------------------------------------*/
static TaskHandle_t MainTaskHandle;
/*--- Private function declarations ---------------------------------------------------*/

/*--- Private function definitions ----------------------------------------------------*/
main_sta_t sta;
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
		mainfsm();
		sta = mainfsm_get_sta();
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
