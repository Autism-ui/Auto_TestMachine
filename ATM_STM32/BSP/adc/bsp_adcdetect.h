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

#ifndef __UNIT_TEST_EXPERIMENT_H__
#define __UNIT_TEST_EXPERIMENT_H__

#ifdef __cplusplus
extern "C" {
#endif

/*--- Public dependencies -------------------------------------------------------------*/
#include "adc.h"
/*--- Public macros -------------------------------------------------------------------*/
#define ADC_CHANNEL_NUM 4
/*--- Public type definitions ---------------------------------------------------------*/
/* 暂定4通道，后期更改enum内的定义 */
typedef enum {
	CHANNEL0 = 0,  // PC0
	CHANNEL1,	   // PC1
	CHANNEL2,	   // PC2
	CHANNEL3,	   // PC3
} CHANNEL_STU;
/*--- Public variable declarations ----------------------------------------------------*/
extern int ADC_Module_Complete;
/*--- Public function declarations ----------------------------------------------------*/

/* CHANNEL0:PC0
 * CHANNEL1:PC1
 * CHANNEL2:PC2
 * CHANNEL3:PC3
 */
void bsp_ADC_Update(void);

void bsp_ADC_Reset(void);

float Get_WhichChannel_Voltage(CHANNEL_STU CHANNEL);

#ifdef __cplusplus
}
#endif

#endif	// __UNIT_TEST_EXPERIMENT_H__
