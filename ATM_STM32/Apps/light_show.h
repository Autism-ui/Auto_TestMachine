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

#ifndef __LIGHT_SHOW_H__
#define __LIGHT_SHOW_H__

#ifdef __cplusplus
extern "C" {
#endif

/*--- Public dependencies -------------------------------------------------------------*/
#include "bsp_adcdetect.h"
#include "adc_collect.h"
#include "bsp_ws2812.h"
/*--- Public macros -------------------------------------------------------------------*/

/*--- Public type definitions ---------------------------------------------------------*/

/*--- Public variable declarations ----------------------------------------------------*/

/*--- Public function declarations ----------------------------------------------------*/
void WS2812_Detect(CHANNEL_STU CHANNEL, ADC_DETECT_STU Result);

#ifdef __cplusplus
}
#endif

#endif	// __LIGHT_SHOW_H__
