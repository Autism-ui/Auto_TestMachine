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

#include "main_fsm.h"

#ifdef __cplusplus
extern "C" {
#endif

/*--- Private dependencies ------------------------------------------------------------*/
#include "bsp_usart.h"
#include "bsp_adcdetect.h"
#include "adc_collect.h"
#include "watchdog.h"
#include "systime.h"
/*--- Public variable definitions -----------------------------------------------------*/

/*--- Private macros ------------------------------------------------------------------*/

/*--- Private type definitions --------------------------------------------------------*/
static main_sta_t		sta_now				= MAIN_STA_STARTUP, sta_next, sta_previous;
static main_sta_fatal_t fatal_detail		= MAIN_STA_FATALERROR_NONE;
static int				ADC_Module_Complete = 0;
static enum {
	ENTER,
	RUNNING,
	EXIT,
} fsm_ctrl = ENTER;
/*--- Private variable definitions ----------------------------------------------------*/
// static uint32_t time_ms_enter;
/*--- Private function declarations ---------------------------------------------------*/

/*--- Private function definitions ----------------------------------------------------*/
static void fsm_enter(main_sta_t sta) {
	switch(sta) {
	case MAIN_STA_STARTUP: break;
	case MAIN_STA_CHECKSELF: break;
	case MAIN_STA_READY: break;
	case MAIN_STA_ADC_RUNNING: break;
	case MAIN_STA_ADC_STOP: break;
	}
}

static void fsm_running(main_sta_t sta) {
	switch(sta) {
	case MAIN_STA_STARTUP: mainfsm_switch(MAIN_STA_CHECKSELF); break;
	case MAIN_STA_CHECKSELF: mainfsm_switch(MAIN_STA_READY); break;
	case MAIN_STA_READY:
		ADC_Reset();
		mainfsm_switch(MAIN_STA_ADC_RUNNING);
		break;
	case MAIN_STA_ADC_RUNNING:
		if(!ADC_Module_Complete) {
			bsp_ADC_Update();
			ADC_Detect();
			ADC_Module_Complete = 1;
		}
		if(FAIL == ADC_CHANNEL_Result()) {
			mainfsm_switch(MAIN_STA_ADC_STOP);
		} else {
		}
		break;
	case MAIN_STA_ADC_STOP:
		if(0) {	 // button
			mainfsm_switch(MAIN_STA_READY);
		}
		break;
	}
}

static void fsm_exit(main_sta_t sta) {
	switch(sta) {
	case MAIN_STA_STARTUP: break;
	case MAIN_STA_CHECKSELF: break;
	case MAIN_STA_READY: break;
	case MAIN_STA_ADC_RUNNING: break;
	case MAIN_STA_ADC_STOP: break;
	}
}
/*--- Public function definitions -----------------------------------------------------*/
void mainfsm(void) {
	switch(fsm_ctrl) {
	case ENTER:
		// time_ms_enter = Get_systime_ms();
		sta_now = sta_next;
		fsm_enter(sta_next);
		fsm_ctrl = RUNNING;
		break;
	case RUNNING:
		fsm_running(sta_now);
		if(sta_next == sta_now) {
			break;
		}
		sta_previous = sta_now;
		fsm_ctrl	 = EXIT;
		break;
	case EXIT:
		fsm_exit(sta_previous);
		fsm_ctrl = ENTER;
		break;
	}
}

void mainfsm_switch(main_sta_t sta) {
	sta_next = sta;
	fsm_ctrl = ENTER;
}

bool mainfsm_is_in(main_sta_t sta) {
	if(sta == sta_now || sta == sta_next) {
		return true;
	}
	return false;
}

main_sta_t mainfsm_get_sta(void) {
	return sta_now;
}

main_sta_fatal_t mainfsm_get_fatal_sta(void) {
	return fatal_detail;
}

#ifdef __cplusplus
}
#endif
