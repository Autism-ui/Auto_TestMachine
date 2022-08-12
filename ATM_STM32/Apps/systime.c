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

#include "systime.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

#define GetTick_ms() HAL_GetTick()

uint32_t Get_systime_ms(void) {
	return GetTick_ms();
}

uint32_t Get_systime_us(void) {
	return 1000 * GetTick_ms() + TIM3->CNT;
}
#ifdef __cplusplus
}
#endif
