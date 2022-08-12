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
#include "watchdog.h"
#include "string.h"
#include "systime.h"
/*--- Public variable definitions -----------------------------------------------------*/

/*--- Private macros ------------------------------------------------------------------*/
#define Avg_Num				 20
#define ADC_Conversion_Ratio 4096.0f
#define ADC_Coefficient		 3.3f
#define ADC_Delay(a)		 HAL_Delay(a)
/*--- Private type definitions --------------------------------------------------------*/
// #define ADC_INIT          \
// 	{                     \
// 		CHANNEL0,         \
// 			ADC_DMA_INIT, \
// 			0.0f,         \
// 	}

typedef enum {
	ADC_DMA_INIT,
	ADC_DMA_CLOSE,
	ADC_DMA_OPEN,
} ADC_DMA_STU;

typedef struct ADC_CHANNEL {
	CHANNEL_STU CHANNEL;
	ADC_DMA_STU ADC_DMA_Statu;
	float		ADC_Voltage[ADC_CHANNEL_NUM];
} ADC_CHANNEL_t;

/*--- Private variable definitions ----------------------------------------------------*/
// ADC_CHANNEL_t ADC_CHANNEL = ADC_INIT;
ADC_CHANNEL_t ADC_CHANNEL = {
	.CHANNEL	   = CHANNEL0,
	.ADC_DMA_Statu = ADC_DMA_INIT,
	.ADC_Voltage   = 0.0f,
};
uint16_t ADC_Select[ADC_CHANNEL_NUM] = { 0 };
float	 Cur_Value[ADC_CHANNEL_NUM];
int		 flag = 0;
/*--- Private function declarations ---------------------------------------------------*/
static uint32_t Select_ADC(CHANNEL_STU CHANNEL) {
	uint32_t sum = 0;
	for(int i = 0; i < Avg_Num; i++) {
		uint32_t last_time = Get_systime_ms();
		while(Get_systime_ms() - last_time <= Avg_Num) {
		};
		sum += ADC_Select[CHANNEL];
	}
	return (sum / Avg_Num);
}
/*--- Private function definitions ----------------------------------------------------*/
static void Update_Channelx_ADC(CHANNEL_STU CHANNEL) {
	ADC_CHANNEL.CHANNEL			   = CHANNEL;
	uint32_t avg				   = Select_ADC(ADC_CHANNEL.CHANNEL);
	Cur_Value[ADC_CHANNEL.CHANNEL] = ((float)avg / ADC_Conversion_Ratio * ADC_Coefficient);
	ADC_CHANNEL.ADC_Voltage[ADC_CHANNEL.CHANNEL] = Cur_Value[ADC_CHANNEL.CHANNEL];
	FeedIndependentWDOG();
}

static void start_select_adc() {
	HAL_ADC_Start_DMA(&hadc1, (uint32_t *)ADC_Select, ADC_CHANNEL_NUM);	 // 启动DMA
	ADC_CHANNEL.ADC_DMA_Statu = ADC_DMA_OPEN;
}

static void end_select_adc() {
	HAL_ADC_Stop_DMA(&hadc1);  // 关闭DMA
	ADC_CHANNEL.ADC_DMA_Statu = ADC_DMA_CLOSE;
}

/*--- Public function definitions -----------------------------------------------------*/

void bsp_ADC_Update(void) {
	start_select_adc();
	// 延时0.5s后再处理数据，防止数据漏处理
	ADC_Delay(100);

	Update_Channelx_ADC(CHANNEL0);
	Update_Channelx_ADC(CHANNEL1);
	Update_Channelx_ADC(CHANNEL2);
	Update_Channelx_ADC(CHANNEL3);

	end_select_adc();
}

float Get_WhichChannel_Voltage(CHANNEL_STU CHANNEL) {
	return ADC_CHANNEL.ADC_Voltage[CHANNEL];
}

void bsp_ADC_Reset(void) {
	memset(ADC_Select, 0, ADC_CHANNEL_NUM);
	memset(Cur_Value, 0.0f, ADC_CHANNEL_NUM);
	memset(ADC_CHANNEL.ADC_Voltage, 0.0f, ADC_CHANNEL_NUM);
	ADC_CHANNEL.CHANNEL		  = CHANNEL0;
	ADC_CHANNEL.ADC_DMA_Statu = ADC_DMA_INIT;
}

#ifdef __cplusplus
}
#endif
