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
#define CHANNEL0_MIN 2.35f
#define CHANNEL0_MAX 2.41f
/*CH1-PC1*/
#define CHANNEL1_MIN 0.45f
#define CHANNEL1_MAX 0.52f
/*CH2-PC2*/
#define CHANNEL2_MIN 0.39f
#define CHANNEL2_MAX 0.43f
/*CH3-PC3*/
#define CHANNEL3_MIN 0.29f
#define CHANNEL3_MAX 0.34

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
