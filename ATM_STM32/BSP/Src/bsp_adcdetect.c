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

#ifdef __cplusplus
extern "C" {
#endif

/*--- Private dependencies ------------------------------------------------------------*/
#include "bsp_adcdetect.h"

/*--- Public variable definitions -----------------------------------------------------*/
	
uint16_t ADC_Select[ADC_CHANNEL_NUM]={0};
float Cur_Value[ADC_CHANNEL_NUM];

/*--- Private macros ------------------------------------------------------------------*/
#define Avg_Num 10
/*--- Private type definitions --------------------------------------------------------*/

/* 暂定4通道，后期更改enum内的定义 */
typedef enum{
	CHANNEL0 = 0, // PC0
	CHANNEL1,			// PC1
	CHANNEL2,			// PC2
	CHANNEL3,			// PC3
}CHANNEL_STU;
/*--- Private variable definitions ----------------------------------------------------*/
float Update_Common(uint16_t detect)
{
	uint16_t sum = 0;
	for(int i = 0;i < Avg_Num;i++)
	{
		sum += detect;
	}
	uint16_t avg = sum/Avg_Num;
	return (float)avg/4096.0*3.3;
}

void Update_Channel0_ADC()
{
//	uint16_t buf[Avg_Num];
//	sum = 0;
//	for(int i = 0;i < Avg_Num;i++)
//	{
//		sum += ADC_Select[CHANNEL0];
//	}
//	int avg = sum/Avg_Num;
	Cur_Value[CHANNEL0] = Update_Common(ADC_Select[CHANNEL0]);
}
/*--- Private function declarations ---------------------------------------------------*/
void Update_Channel1_ADC()
{
	Cur_Value[CHANNEL1] = Update_Common(ADC_Select[CHANNEL1]);
}
/*--- Private function definitions ----------------------------------------------------*/
void Update_Channel2_ADC()
{
	Cur_Value[CHANNEL2] = Update_Common(ADC_Select[CHANNEL2]);
}
void Update_Channel3_ADC()
{
	Cur_Value[CHANNEL3] = Update_Common(ADC_Select[CHANNEL3]);
}
/*--- Private function definitions ----------------------------------------------------*/
void start_select_adc()
{
	HAL_ADC_Start_DMA(&hadc1,(uint32_t *)ADC_Select,ADC_CHANNEL_NUM);// 启动DMA
}

void end_select_adc()
{
	HAL_ADC_Stop_DMA(&hadc1);// 关闭DMA
}

/*--- Public function definitions -----------------------------------------------------*/

void bsp_ADC_Update()
{
	start_select_adc();
	int adc = 20;
	while(adc--)
	{
		Update_Channel0_ADC();
		Update_Channel1_ADC();
		Update_Channel2_ADC();
		Update_Channel3_ADC();
	}
	end_select_adc();
	
}

#ifdef __cplusplus
}
#endif
