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

#ifndef __BSP_WS2812_H__
#define __BSP_WS2812_H__

#ifdef __cplusplus
extern "C" {
#endif

/*--- Public dependencies -------------------------------------------------------------*/
#include "gpio.h"
/*--- Public macros -------------------------------------------------------------------*/
#define WS2812_PIXEL_NUM 15
/*--- Public type definitions ---------------------------------------------------------*/

/*--- Public variable declarations ----------------------------------------------------*/

/*--- Public function declarations ----------------------------------------------------*/
void bsp_WS2812_Init(void);
void bsp_WS2812_SyncAll(void);
void bsp_WS2812_LED_alloff(void);
void bsp_WS2812_LED_Write(uint8_t led_index, uint8_t R, uint8_t G, uint8_t B);
void bsp_WS2812_WriteAll(uint8_t R, uint8_t G, uint8_t B);

void bsp_WS2812_SHOW(uint8_t R, uint8_t G, uint8_t B);
void bsp_WS2812_CheckSelf(void);
#ifdef __cplusplus
}
#endif

#endif	// __BSP_WS2812_H__
