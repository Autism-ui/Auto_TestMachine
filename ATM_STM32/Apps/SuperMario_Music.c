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

#include "SuperMario_Music.h"

#ifdef __cplusplus
extern "C" {
#endif

/*--- Private dependencies ------------------------------------------------------------*/
#include "tim.h"
/*--- Public variable definitions -----------------------------------------------------*/

/*--- Private macros ------------------------------------------------------------------*/
#define L1	262
#define L1U 277
#define L2	294
#define L2U 311
#define L3	330
#define L4	349
#define L4U 370
#define L5	392
#define L5U 415
#define L6	440
#define L6U 466
#define L7	494

#define M1	523
#define M1U 554
#define M2	587
#define M2U 622
#define M3	659
#define M4	698
#define M4U 740
#define M5	784
#define M5U 831
#define M6	880
#define M6U 932
#define M7	988

#define H1	1046
#define H1U 1109
#define H2	1175
#define H2U 1245
#define H3	1318
#define H4	1397
#define H4U 1480
#define H5	1568
#define H5U 1661
#define H6	1760
#define H6U 1865
#define H7	1976
/*--- Private type definitions --------------------------------------------------------*/
typedef struct {
	uint16_t note;
	uint16_t time;
} MusicNote;

/*--- Private variable definitions ----------------------------------------------------*/
MusicNote SuperMario[] = { { M3, 100 }, { 0, 50 },	 { M3, 100 }, { 0, 50 },  { M3, 100 },
						   { 0, 50 },	{ 0, 150 },	 { M1, 100 }, { 0, 50 },  { M3, 250 },
						   { 0, 50 },	{ M5, 250 }, { 0, 50 },	  { 0, 300 }, { L5, 250 },
						   { 0, 50 },	{ 0, 300 } };
/*--- Private function declarations ---------------------------------------------------*/

/*--- Private function definitions ----------------------------------------------------*/

/*--- Public function definitions -----------------------------------------------------*/
void SuperMario_InitMusic(void) {
	HAL_TIM_PWM_Start(&htim10, TIM_CHANNEL_1);
	for(int i = 0; i < sizeof(SuperMario) / sizeof(MusicNote); i++) {
		if(SuperMario[i].note == 0) {
			__HAL_TIM_SET_AUTORELOAD(&htim10, 0);
			osDelay(SuperMario[i].time);
		} else {
			__HAL_TIM_SET_AUTORELOAD(&htim10, 1000000 / SuperMario[i].note);
			osDelay(SuperMario[i].time);
		}
	}
	HAL_TIM_PWM_Stop(&htim10, TIM_CHANNEL_1);
}

#ifdef __cplusplus
}
#endif
