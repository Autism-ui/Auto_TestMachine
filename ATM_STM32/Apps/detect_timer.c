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

#include "detect_timer.h"

#ifdef __cplusplus
extern "C" {
#endif

/*--- Private dependencies ------------------------------------------------------------*/
#include "button.h"
#include "main.h"
/*--- Public variable definitions -----------------------------------------------------*/

/*--- Private macros ------------------------------------------------------------------*/

/*--- Private type definitions --------------------------------------------------------*/

/*--- Private variable definitions ----------------------------------------------------*/

/*--- Private function declarations ---------------------------------------------------*/

/*--- Private function definitions ----------------------------------------------------*/

/*--- Public function definitions -----------------------------------------------------*/
void Detect_Timer_Init(void) {
	osTimerStart(Detect_TimerHandle, 10);
}

void Detect_Timer_Callback(void *argument) {
	Button_Scan();
}
#ifdef __cplusplus
}
#endif
