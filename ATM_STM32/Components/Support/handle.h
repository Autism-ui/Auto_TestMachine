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

#ifndef __HANDLE_H__
#define __HANDLE_H__

#ifdef __cplusplus
extern "C" {
#endif

/*--- Public dependencies -------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "queue.h"
/*--- Public macros -------------------------------------------------------------------*/
#define _HANDLE_EXT extern
/*--- Public type definitions ---------------------------------------------------------*/

/*--- Public variable declarations ----------------------------------------------------*/
//队列句柄
_HANDLE_EXT  QueueHandle_t 	xQueue ,xQueueCanSend ,xQueueCanReceive;
/*--- Public function declarations ----------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif  // __HANDLE_H__
