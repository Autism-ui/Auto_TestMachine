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

#ifndef __USARTINTERACT_TASK_H__
#define __USARTINTERACT_TASK_H__

#ifdef __cplusplus
extern "C" {
#endif

/*--- Public dependencies -------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "usart.h"
#include "queue.h"
#include "cmsis_os.h"
/*--- Public macros -------------------------------------------------------------------*/

/*--- Public type definitions ---------------------------------------------------------*/

/*--- Public variable declarations ----------------------------------------------------*/

/*--- Public function declarations ----------------------------------------------------*/
void UsartInteract_TaskCreate(osPriority_t _priority);

#ifdef __cplusplus
}
#endif

#endif	// __USARTINTERACT_TASK_H__
