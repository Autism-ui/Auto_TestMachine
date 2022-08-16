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

#ifndef __ADC_COLLECT_H__
#define __ADC_COLLECT_H__

#include "stdbool.h"
#include "bsp_adcdetect.h"
#ifdef __cplusplus
extern "C" {
#endif

/*CH0-PC0*/
#define CHANNEL0_MIN 0.1f
#define CHANNEL0_MAX 1.0f
/*CH1-PC1*/
#define CHANNEL1_MIN 0.1f
#define CHANNEL1_MAX 2.0f
/*CH2-PC2*/
#define CHANNEL2_MIN 0.1f
#define CHANNEL2_MAX 3.3f
/*CH3-PC3*/
#define CHANNEL3_MIN 0.1f
#define CHANNEL3_MAX 3.3f

typedef enum {
	FAIL,
	PASS,
	NONE,
} ADC_DETECT_STU;

typedef struct {
	ADC_DETECT_STU ADC_DETECT[ADC_CHANNEL_NUM];
} ADC_COLLECT_t;

extern ADC_COLLECT_t ADC_COLLECT;

void ADC_Detect(void);

void ADC_Reset(void);

bool ADC_CHANNEL_Result(void);

#ifdef __cplusplus
}
#endif

#endif	// __ADC_COLLECT_H__
