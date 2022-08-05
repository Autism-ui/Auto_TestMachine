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
extern "C"
{
#endif

/*--- Private dependencies ------------------------------------------------------------*/
#include "bsp_adcdetect.h"

	/*--- Public variable definitions -----------------------------------------------------*/

	uint16_t ADC_Select[ADC_CHANNEL_NUM] = {0};
	float Cur_Value[ADC_CHANNEL_NUM];

/*--- Private macros ------------------------------------------------------------------*/
#define Avg_Num 10
	/*--- Private type definitions --------------------------------------------------------*/

	/* 暂定4通道，后期更改enum内的定义 */
	typedef enum
	{
		CHANNEL0 = 0, // PC0
		CHANNEL1,	  // PC1
		CHANNEL2,	  // PC2
		CHANNEL3,	  // PC3
	} CHANNEL_STU;
	/*--- Private variable definitions ----------------------------------------------------*/

	/*--- Private function declarations ---------------------------------------------------*/
	void Update_Channel0_ADC()
	{
		uint32_t sum = 0;
		for (int i = 0; i < Avg_Num; i++)
		{
			sum += ADC_Select[CHANNEL0];
		}
		uint32_t avg = sum / Avg_Num;
		Cur_Value[CHANNEL0] = ((float)avg / 4096.0 * 3.3);
	}

	void Update_Channel1_ADC()
	{
		uint32_t sum = 0;
		for (int i = 0; i < Avg_Num; i++)
		{
			sum += ADC_Select[CHANNEL1];
		}
		uint32_t avg = sum / Avg_Num;
		Cur_Value[CHANNEL1] = ((float)avg / 4096.0 * 3.3);
	}
	/*--- Private function definitions ----------------------------------------------------*/
	void Update_Channel2_ADC()
	{
		uint32_t sum = 0;
		for (int i = 0; i < Avg_Num; i++)
		{
			sum += ADC_Select[CHANNEL2];
		}
		uint32_t avg = sum / Avg_Num;
		Cur_Value[CHANNEL2] = ((float)avg / 4096.0 * 3.3);
	}
	void Update_Channel3_ADC()
	{
		uint32_t sum = 0;
		for (int i = 0; i < Avg_Num; i++)
		{
			sum += ADC_Select[CHANNEL3];
		}
		uint32_t avg = sum / Avg_Num;
		Cur_Value[CHANNEL3] = ((float)avg / 4096.0 * 3.3);
	}
	/*--- Private function definitions ----------------------------------------------------*/
	void start_select_adc()
	{
		HAL_ADC_Start_DMA(&hadc1, (uint32_t *)ADC_Select, ADC_CHANNEL_NUM); // 启动DMA
	}

	void end_select_adc()
	{
		HAL_ADC_Stop_DMA(&hadc1); // 关闭DMA
	}

	/*--- Public function definitions -----------------------------------------------------*/

	void bsp_ADC_Update(void)
	{
		start_select_adc();
		// 延时0.5s后再处理数据，防止数据漏处理
		HAL_Delay(500);

		Update_Channel0_ADC();
		Update_Channel1_ADC();
		Update_Channel2_ADC();
		Update_Channel3_ADC();

		end_select_adc();
	}

#ifdef __cplusplus
}
#endif
