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

#include "bsp_adcdetect.h"
#include "adc_collect.h"
#include "bsp_ws2812.h"

void WS2812_Detect(CHANNEL_STU CHANNEL, ADC_DETECT_STU Result);
void WS2812_SHOW(uint8_t r, uint8_t g, uint8_t b);
void WS2812_LIGHTOFF(void);
void WS2812_CheckSelf(void);

#ifdef __cplusplus
}
#endif

#endif	// __LIGHT_SHOW_H__
