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

#ifdef __cplusplus
extern "C" {
#endif

/*--- Public dependencies -------------------------------------------------------------*/

/*--- Public macros -------------------------------------------------------------------*/
/*CH0-PC0*/
#define CHANNEL0_MIN 0.0f
#define CHANNEL0_MAX 3.3f
/*CH1-PC1*/
#define CHANNEL1_MIN 0.0f
#define CHANNEL1_MAX 1.5f
/*CH2-PC2*/
#define CHANNEL2_MIN 0.0f
#define CHANNEL2_MAX 3.3f
/*CH3-PC3*/
#define CHANNEL3_MIN 0.0f
#define CHANNEL3_MAX 3.3f
/*--- Public type definitions ---------------------------------------------------------*/

/*--- Public variable declarations ----------------------------------------------------*/

/*--- Public function declarations ----------------------------------------------------*/
void ADC_Detect(void);

#ifdef __cplusplus
}
#endif

#endif	// __ADC_COLLECT_H__
