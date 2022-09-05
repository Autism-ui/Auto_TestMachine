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

/**
 *
 * @file drv_tim.c
 * @author Heyihan (316383560@qq.com)
 * @brief This file is the driver source file for the Tim peripheral
 * @version 0.1
 * @date 2022-08-16
 *
 * @copyright Copyright (c) 2022
 *
 */

/*--- Private dependencies ------------------------------------------------------------*/
#include "tim.h"
#include "bsp_tim.h"
#include <assert.h>
/*--- Public variable definitions -----------------------------------------------------*/

/*--- Private macros ------------------------------------------------------------------*/
#define CHPI_TYPE (Chip_type)

// Chip Type - Select master frequency
#if CHPI_TYPE == STM32F407XX

#define CHIP_APB1_FRE (168000000)
#define DIV			  (CHIP_APB1_FRE / 1000000)

#elif STM32F427XX

#define CHIP_APB1_FRE 180000000
#define DIV			  CHIP_APB1_FRE / 1000000

#endif

#define HAL_LIB 1

/*--- Private type definitions --------------------------------------------------------*/

/**
 * @brief  chip type to set the val of APB1
 * @note
 * @retval None
 */
typedef enum {

	STM32F407XX = 0,
	STM32F427XX = 1

} Chip_type_e;

/**
 * @brief  Capture Level
 * @note
 * @retval None
 */
typedef enum {

	Level_DN = 0,
	Level_UP,

} Capture_level_e;

Chip_type_e Chip_type;
Captor_id_e Captor_id;
/*--- Private variable definitions ----------------------------------------------------*/

/*--- Private function declarations ---------------------------------------------------*/
void TIM_Capture_IC_callback(TIM_ActiveChannel Chx, Captor_id_e Captor_id);

uint32_t TIM_getCaptureVal(struct TIM_Captor *p_Dev, uint8_t Level);
void	 TIM_GetVal(struct TIM_Captor *p_Dev);

void CaptureStart_IT(uint8_t idx);
void TIM1_captor1_obj_Init(uint16_t idx);
void TIM4_captor2_obj_Init(uint16_t idx);

void Duty_calculate(struct TIM_Captor *p_Dev, TIM_ActiveChannel chx);
void Frequency_calculate(struct TIM_Captor *p_Dev, TIM_ActiveChannel chx);
void Pulse_calculate(struct TIM_Captor *p_Dev);

void Captor_data_process(Captor_id_e idx, TIM_ActiveChannel chx);
void tim_data_cal(struct TIM_Captor *p_Dev, TIM_ActiveChannel chx, Captor_id_e id_sel);

p_TIM_Captor Get_Tim_Devcie(Captor_id_e id);

Captor_id_e set_Captor_id(Captor_id_e id);
/* ------------- PWM_capture ------------- */
struct TIM_Captor Captor[] = {
	/* /htimx /Cap_val1 /Cap_val2 /Duty /Frequency /Pulse /Channel_UP /Channel_DN /MSB_OR_LSB
	/is_valid /Captor_init / TIM_Capture/Duty_cal /Frequency_cal /TIM_CapureCallBack_f  */
	{ &htim1,
	  0,
	  0,
	  0,
	  0,
	  0,
	  TIM_CHANNEL_1,
	  TIM_CHANNEL_2,
	  0,
	  TIM1_captor1_obj_Init,
	  TIM_getCaptureVal,
	  Duty_calculate,
	  Frequency_calculate,
	  Pulse_calculate },
	{ &htim4,
	  0,
	  0,
	  0,
	  0,
	  0,
	  TIM_CHANNEL_1,
	  TIM_CHANNEL_2,
	  0,
	  TIM4_captor2_obj_Init,
	  TIM_getCaptureVal,
	  Duty_calculate,
	  Frequency_calculate,
	  Pulse_calculate },

};

/*--- Public function definitions -----------------------------------------------------*/
/* ------------------------- public API ------------------------- */
/**
 * @brief  API functions provided externally for TIM captor initialize
 * @note
 * @retval None
 */
/* TIM caputre device  *************************/
void Captor_init(void) {
	// Enable TIMx
	__HAL_TIM_ENABLE(&htim1);
	__HAL_TIM_ENABLE(&htim4);

	// Init capture obj
	for(int i = 0; i < CAPTOR_NUM; ++i) {
		Captor[i].Captor_init(i);
	}
}

/**
 * @brief  printf for TIM param debug
 * @note   Based on this function you can see the related properties of the input PWM
 * @param  p_Dev:
 * @retval None
 */
void tim_debug_raw_printf(Captor_viewer *p_Dev) {
	uint32_t Cap_val1 = p_Dev->Cap_val1;
	uint32_t Cap_val2 = p_Dev->Cap_val2;

	float Duty		= p_Dev->Duty;
	float Frequency = p_Dev->Frequency;

	printf("Cap_val1 is %d Cap_val2 is %d	\n Duty is %f, Frequency is %f\n ",
		   Cap_val1,
		   Cap_val2,
		   Duty,
		   Frequency);
}

/*--- Private function definitions ----------------------------------------------------*/
/* ------------------------- Private function ------------------------- */

/* -------------------------  global enum variable set val ------------------------- */
/**
 * @brief  set captor id for enum:	Captor_id_e
 * @note
 * @param  id:
 * @retval
 */
Captor_id_e set_Captor_id(Captor_id_e id) {
	Captor_id_e ret = id;
	return ret;
}

/* -------------------------  function register ------------------------- */
/**
 * @brief  TIM1 captor obj1 IC callback function
 * @note
 * @param  Chx:
 * @retval None
 */
void TIM_Capture_IC_callback(TIM_ActiveChannel Chx, Captor_id_e Captor_id) {
	TIM_Captor_t *timx_Dev;

	timx_Dev = Get_Tim_Devcie(Captor_id);

	tim_data_cal(timx_Dev, Chx, Captor_id);
}

/**
 * @brief  HAL Enable TIM capture Interrupt
 * @note
 * @param  idx:
 * @retval None
 */
void CaptureStart_IT(uint8_t idx) {
	HAL_StatusTypeDef err1;
	HAL_StatusTypeDef err2;

	err1 = HAL_TIM_IC_Start_IT(Captor[idx].htimx, Captor[idx].Channel_UP);
	err2 = HAL_TIM_IC_Start_IT(Captor[idx].htimx, Captor[idx].Channel_DN);

	if(err1 != HAL_OK || err2 != HAL_OK) {
		goto ERR;
	}

	Captor[idx].is_valid = 1;  // capture it is available

	return;

ERR:
	/*
	 * err process
	 * */
	printf("HAL_TIM_IC_Start_IT Fail!!");
	assert(0);

	return;
}

/* ----------------- Captor object init ----------------- */

/**
 * @brief  Class for catcher 1
 * @note
 * @retval None
 */
void TIM1_captor1_obj_Init(uint16_t idx) {
	Captor[idx].TIM_Capture = TIM_getCaptureVal;

#if defined(HAL_LIB)

	CaptureStart_IT(idx);

#endif /* USE WHITCH LIB TO CONTROL THE REGESITER */
}

/**
 * @brief  Class for catcher 2
 * @note
 * @retval None
 */
void TIM4_captor2_obj_Init(uint16_t idx) {
	Captor[idx].TIM_Capture = TIM_getCaptureVal;

#if defined(HAL_LIB)

	CaptureStart_IT(idx);

#endif /* USE WHITCH LIB TO CONTROL THE REGESITER */
}

/* USER OBJ INIT BEGIN */
/* add your new object init function, ... */
/* USER OBJ INIT END */

/* -------------------------  Pwm captor data process ------------------------- */

/**
 * @brief
 * @note   Level == 1 indicates the previous time, and Level == 0 indicates the later time
 * @param  p_Dev:
 * @param  Level:
 * @retval
 */
uint32_t TIM_getCaptureVal(struct TIM_Captor *p_Dev, uint8_t Level) {
#if defined(HAL_LIB)

	if(Level == Level_UP) {
		return HAL_TIM_ReadCapturedValue(p_Dev->htimx, p_Dev->Channel_UP);
	} else if(Level == Level_DN) {
		return HAL_TIM_ReadCapturedValue(p_Dev->htimx, p_Dev->Channel_DN);
	}

#else
	//... The standard library stuff
#endif /* USE WHITCH LIB TO CONTROL THE REGESITER */

	return 0;
}

/**
 * @brief  Get TIM capture val1 val2
 * @note
 * @param  p_Dev:
 * @param  Dev_id:
 * @retval None
 */
void TIM_GetVal(struct TIM_Captor *p_Dev) {
	p_Dev->Cap_val1 = p_Dev->TIM_Capture(p_Dev, Level_UP);
	p_Dev->Cap_val2 = p_Dev->TIM_Capture(p_Dev, Level_DN);
}

/**
 * @brief  Duty cycle calculation
 * @note   Duty: The proportion of time that high levels occupy in a cycle
 * 		   High level first and low level first will have two different calculation formulas.
 * @param  p_Dev:
 * @retval None
 */
void Duty_calculate(struct TIM_Captor *p_Dev, TIM_ActiveChannel chx) {
	/* Duty cycle is the ratio at which high levels persist.I multiplied Duty by a hundred just to
	 * make it a percentage */
	p_Dev->Duty = (float)(p_Dev->Cap_val2 + 1) * 100 / (p_Dev->Cap_val1 + 1);
}

/**
 * @brief  Frequency calculation
 * @note   High level first and low level first will have two different calculation formulas.
 * @param  p_Dev:
 * @retval None
 */
void Frequency_calculate(struct TIM_Captor *p_Dev, TIM_ActiveChannel chx) {
	/* Frequency = clock line frequency/frequency division factor /CCRx */
	p_Dev->Frequency = CHIP_APB1_FRE / DIV / (float)(p_Dev->Cap_val1 + 1);
}

/**
 * @brief  Pulse calculate(it means that time occupied by the high level )
 * @note
 * @param  p_Dev:
 * @retval None
 */
void Pulse_calculate(struct TIM_Captor *p_Dev) {
	/* fomular: (1/Frequency) * Duty . I'm dividing by 100 just to get the duty cycle back to its
	 * original value. */
	p_Dev->Pulse = (1 / p_Dev->Frequency) * p_Dev->Duty / 100;
}

/**
 * @brief Gets the corresponding Tim object by ID
 * @note
 * @param  id:
 * @retval
 */
p_TIM_Captor Get_Tim_Devcie(Captor_id_e id) {
	return &Captor[id];
}

/**
 * @brief  HAL library input capture timer interrupt callback function
 * @note  If the trigger source is TI1FP1 then CH1 have to be Rising + Direct.
 * 		* If the trigger source is TI2FP2 then CH2 have to be Rising + Direct.
 * @param  *htim:
 * @retval None
 */
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim) {
	/*
	 *	Odd is high first, even is low first
	 * */
	if(htim == &htim1) {
		/* If the trigger source is TI1FP1 then it will enter this judgment */
		/* Check whether channel 1 enables OR activation */
		if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
			TIM_Capture_IC_callback(TIM_ACTIVE_CHANNEL_1, captor_1);
		}
		/* If the trigger source is TI2FP2 then it will enter this judgment and CH2 have to be
		 * Rising + Direct */
		//			else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2){
		//				TIM_Capture_IC_callback(TIM_ACTIVE_CHANNEL_2,captor_1);
		//			}
	} else if(htim == &htim4) {
		/* If the trigger source is TI1FP1 then it will enter this judgment */
		/* Check whether channel 1 enables OR activation */

		if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1) {
			TIM_Capture_IC_callback(TIM_ACTIVE_CHANNEL_1, captor_2);
		}
		/* If the trigger source is TI2FP2 then it will enter this judgment and CH2 have to be
		 * Rising + Direct */
		//			else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2){
		//				TIM_Capture_IC_callback(TIM_ACTIVE_CHANNEL_2,captor_2);
		//			}
	} else if(0) {
		/*
		 *	Odd is high first, even is low first
		 * */

		/* user code begin */
		// add your new tim device,...

	}

	/* user code end */
	else {
	}
}

/**
 * @brief
 * @note
 * @param  idx:
 * @retval None
 */
void Captor_data_process(Captor_id_e idx, TIM_ActiveChannel chx) {
	TIM_Captor_t *Captor_Dev;

	Captor_Dev = Get_Tim_Devcie(idx);

	TIM_GetVal(Captor_Dev);

	/* Calculate duty cycle and frequency */
	if(Captor_Dev->Cap_val1 != 0) {
		Captor_Dev->Duty_cal(Captor_Dev, chx);
		Captor_Dev->Frequency_cal(Captor_Dev, chx);
		Captor_Dev->Pulse_cal(Captor_Dev);
	} else {
		Captor_Dev->Duty	  = 0;
		Captor_Dev->Frequency = 0;
		Captor_Dev->Pulse	  = 0;
	}
}

/**
 * @brief  The input captures the relevant data to compute
 * @note
 * @param  p_Dev:
 * @param  chx:
 * @param  id_sel:
 * @retval None
 */
void tim_data_cal(struct TIM_Captor *p_Dev, TIM_ActiveChannel chx, Captor_id_e id_sel) {
	switch(id_sel) {
	case captor_1: Captor_data_process(captor_1, chx); break;

	case captor_2: Captor_data_process(captor_2, chx); break;
	/* USER CODE BEGIN */
	/**
	 * add more Device,...
	 *
	 */
	/* USER CODE END */
	default: break;
	}
}

/**
 * @brief  tim debug raw data printf function
 * @note
 * @param  p_Dev:
 * @retval None
 */
void tim_debug_raw_printf_my(struct TIM_Captor *p_Dev) {
	uint32_t Cap_val1 = p_Dev->Cap_val1;
	uint32_t Cap_val2 = p_Dev->Cap_val2;

	float Duty		= p_Dev->Duty;
	float Frequency = p_Dev->Frequency;

	printf("Cap_val1 is %d Cap_val2 is %d	\n Duty is %f, Frequency is %f\n ",
		   Cap_val1,
		   Cap_val2,
		   Duty,
		   Frequency);
}

/* ------------- PWM_test ------------- */
/*  */
/* ������ֲ֮ǰ�Ĳ��ԣ�������ֲ��ʱ���TIM_TEST ���ó�0���� */
#if TIM_PWM_TEST == 1

/*--- Private macros ------------------------------------------------------------------*/
#define PWM_UP	 1
#define PWM_DOWM -1

/*--- Private type definitions --------------------------------------------------------*/
typedef enum {

	CH1 = 0,
	CH2,
	CH3,
	CH4,
	CH_NUM,
	CH_ALL

} TIM_channel_e;

TIM_channel_e TIM_channel;

/*--- Private variable definitions ----------------------------------------------------*/
uint16_t pwmVal = 0;

static int8_t dir = 1;

/*--- Private function declarations ---------------------------------------------------*/
void TIM2_INIT(void);

/*--- Public variable definitions -----------------------------------------------------*/
struct LEDDevice LED[] = {
	/*/htimx /type / Val / CHx /	LED_Init	/ LED_Control */

	{ &htim2, 0, 0, TIM_CHANNEL_3, TIM2_INIT, PWM_Breath },
	{ &htim2, 0, 0, TIM_CHANNEL_4, TIM2_INIT, PWM_Breath },
};

/*--- Public function definitions -----------------------------------------------------*/

static int8_t Pwm_dir_set(int8_t dir) {
	int8_t Pwm_dir = dir;

	return Pwm_dir;
}

int	 test_val = 200;
int	 j		  = 0;
void TIM2_INIT(void) {
	__HAL_TIM_ENABLE(&htim2);  //ʹ�ܶ�ʱ��2

	// HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);	//����PWMģʽ��TIM2_CH1		�������PWM�������벶�����
	// HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);	//����PWMģʽ��TIM2_CH2
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);  //����PWMģʽ��TIM2_CH2
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);  //����PWMģʽ��TIM2_CH2

	//__HAL_TIM_SetCompare(&htim2,TIM_CHANNEL_1,test_val);
	// j++;
}

void LED_Init(void) {
	for(int i = 0; i < LED_NUM; ++i) {
		LED[i].LED_Init();	// LED�����ʼ����PWM�����
	}
}

/* ------------------------ API ------------------------ */

void PWM_Breath(struct LEDDevice *p_Dev) {
	for(int i = 0; i < LED_NUM; ++i) {
		if(p_Dev[i].Val < 500 && dir == PWM_UP) {
			p_Dev[i].Val++;
		} else {
			dir = Pwm_dir_set(PWM_DOWM);
			p_Dev[i].Val--;

			if(p_Dev[i].Val <= 0) {
				dir = Pwm_dir_set(PWM_UP);
			}
		}

		__HAL_TIM_SetCompare(p_Dev[i].htimx, p_Dev[i].CHx, p_Dev[i].Val);
	}
}

#endif /* End of TIM_PWM_TEST */

#ifdef __cplusplus
}
#endif
