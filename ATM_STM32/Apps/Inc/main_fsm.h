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

#ifndef __MAIN_FSM_H__
#define __MAIN_FSM_H__

#ifdef __cplusplus
extern "C" {
#endif

/*--- Public dependencies -------------------------------------------------------------*/
#include <stdbool.h>
/*--- Public macros -------------------------------------------------------------------*/

/*--- Public type definitions ---------------------------------------------------------*/
typedef enum main_sta {
	MAIN_STA_INIT,
	MAIN_STA_CHECKSELF,
	MAIN_STA_READY,
	MAIN_STA_RUNNING,
	MAIN_STA_STOP,
} main_sta_t;

typedef enum main_sta_fatal {
	MAIN_STA_FATALERROR_NONE,
} main_sta_fatal_t;
/*--- Public variable declarations ----------------------------------------------------*/

/*--- Public function declarations ----------------------------------------------------*/
void mainfsm(void);

void mainfsm_switch(main_sta_t);

main_sta_t mainfsm_get_sta(void);

main_sta_fatal_t mainfsm_get_fatal_sta(void);
#ifdef __cplusplus
}
#endif

#endif	// __MAIN_FSM_H__
