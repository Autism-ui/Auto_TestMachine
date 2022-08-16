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

/*--- Private dependencies ------------------------------------------------------------*/

/*--- Public variable definitions -----------------------------------------------------*/

/*--- Private macros ------------------------------------------------------------------*/

/*--- Private type definitions --------------------------------------------------------*/

/*--- Private variable definitions ----------------------------------------------------*/

/*--- Private function declarations ---------------------------------------------------*/

/*--- Private function definitions ----------------------------------------------------*/

/*--- Public function definitions -----------------------------------------------------*/
void WS2812_Detect(CHANNEL_STU CHANNEL, ADC_DETECT_STU Result) {
	if(Result == FAIL) {
		bsp_WS2812_LED_Write(CHANNEL, 10, 0, 0);
	} else {
		bsp_WS2812_LED_Write(CHANNEL, 0, 10, 0);
	}
}
#ifdef __cplusplus
}
#endif
