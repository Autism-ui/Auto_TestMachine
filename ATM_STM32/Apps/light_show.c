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

#include "light_show.h"

#ifdef __cplusplus
extern "C" {
#endif

void WS2812_Detect(CHANNEL_STU CHANNEL, ADC_DETECT_STU Result) {
	if(Result == FAIL) {
		bsp_WS2812_LED_Write(CHANNEL, 10, 0, 0);
	} else {
		bsp_WS2812_LED_Write(CHANNEL, 0, 10, 0);
	}
}

void WS2812_SHOW(uint8_t r, uint8_t g, uint8_t b) {
	bsp_WS2812_Show(r, g, b);
}

void WS2812_LIGHTOFF() {
	bsp_WS2812_LED_Off();
}

void WS2812_CheckSelf(void) {
	vTaskDelay(pdMS_TO_TICKS(200));
	WS2812_SHOW(200, 0, 0);
	vTaskDelay(pdMS_TO_TICKS(200));
	WS2812_SHOW(0, 200, 0);
	vTaskDelay(pdMS_TO_TICKS(200));
	WS2812_SHOW(0, 0, 200);
	vTaskDelay(pdMS_TO_TICKS(200));
}

#ifdef __cplusplus
}
#endif
