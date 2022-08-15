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

#include "adc_collect.h"

#ifdef __cplusplus
extern "C" {
#endif

/*--- Private dependencies ------------------------------------------------------------*/
#include "string.h"
#include "stdbool.h"
/*--- Public variable definitions -----------------------------------------------------*/

/*--- Private macros ------------------------------------------------------------------*/

/*--- Private type definitions --------------------------------------------------------*/

/*--- Private variable definitions ----------------------------------------------------*/
ADC_COLLECT_t ADC_COLLECT;

/*--- Private function declarations ---------------------------------------------------*/

/*--- Private function definitions ----------------------------------------------------*/
static ADC_DETECT_STU Judge_ADC_CHANNEL(CHANNEL_STU CHANNEL,
										float		Current_V,
										float		CHANNEL_ADC_MIN,
										float		CHANNEL_ADC_MAX) {
	if(Current_V > CHANNEL_ADC_MIN && Current_V < CHANNEL_ADC_MAX) {
		ADC_COLLECT.ADC_DETECT[CHANNEL] = PASS;
	} else {
		ADC_COLLECT.ADC_DETECT[CHANNEL] = FAIL;
	}
	return ADC_COLLECT.ADC_DETECT[CHANNEL];
}
/*--- Public function definitions -----------------------------------------------------*/

void ADC_Detect(void) {
	/* 将检测状态初始化为FAIL */
	memset(ADC_COLLECT.ADC_DETECT, FAIL, ADC_CHANNEL_NUM);

	/* 测量段 */
	Judge_ADC_CHANNEL(CHANNEL0, Get_WhichChannel_Voltage(CHANNEL0), CHANNEL0_MIN, CHANNEL0_MAX);
	Judge_ADC_CHANNEL(CHANNEL1, Get_WhichChannel_Voltage(CHANNEL1), CHANNEL1_MIN, CHANNEL1_MAX);
	Judge_ADC_CHANNEL(CHANNEL2, Get_WhichChannel_Voltage(CHANNEL2), CHANNEL2_MIN, CHANNEL2_MAX);
	Judge_ADC_CHANNEL(CHANNEL3, Get_WhichChannel_Voltage(CHANNEL3), CHANNEL3_MIN, CHANNEL3_MAX);
}

void ADC_Reset(void) {
	bsp_ADC_Reset();
}

bool ADC_CHANNEL_Result(void) {
	for(int i = 0; i < ADC_CHANNEL_NUM; i++) {
		bool result = ADC_COLLECT.ADC_DETECT[i];
		if(result == FAIL)
			return result;
	}
	return true;
}

#ifdef __cplusplus
}
#endif
