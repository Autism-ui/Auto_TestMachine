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

#ifndef __DRV_TIM_H__
#define __DRV_TIM_H__

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file drv_tim.h
 * @author Hans (316383560@qq.com)
 * @brief This file is the driver header file for the Tim peripheral
 * @version 0.1
 * @date 2022-08-16
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/*-------------------------- Readme first when you use this file --------------------------/
 *  Method of use:
 *	If you want to use this function, just call 'Captor_init' in the BSP initialization function.
 * 
 *  instructions:
 *	In terms of configuration, four PWM channels (TIM1) need to be turned on, with two channels capturing one PWM input. 
 	If it is also a HAL library, it needs to turn on the input capture interrupt (note: do not delete the callback function); 
 	In the case of the standard library, the two Captor object callbacks can be used by putting them into the library's interrupt service function.	

	In addition,LEDDevice obj is only use when author testing the function.please don't be confuse of it.You can just ignore it when you use this file.
 *     
 *	API to use:
 *	1.Captor_init()
 *  2.tim_debug_raw_printf()
*/


/*--- Public dependencies -------------------------------------------------------------*/
#include "sys.h"
/*--- Public macros -------------------------------------------------------------------*/
#define TIM_PWM_TEST 					(0)		//Whether to enable the PWM test for TIM
#define LED_NUM 	 						(2)		//LED Devcie num

#define CAPTOR_NUM 		 				(2)		//TIM Captor number
#define CAPTURE_CHANNEL_NUM		(CAPTOR_NUM  * 2)
/*--- Public type definitions ---------------------------------------------------------*/

/**
 * @brief  Only by test
 * @note   LED_DEVCIE
 * @retval None
 */
typedef struct LEDDevice{
	
	TIM_HandleTypeDef *htimx;
	
	int type;						//LED type
	
	uint16_t Val;					//LED gpio level
	uint32_t CHx;					//PWM channel
	
	void (* LED_Init)(void);
	void (* LED_Control)(struct LEDDevice * p_Dev);	//led control function
	
}LEDDevice, *p_LEDDevice;

/* ----------------------- private typedef ----------------------- */
/**
 * @brief  captor id enum
 * @note   
 * @retval None
 */
typedef enum{
	captor_1 = 0,
	captor_2,
	captor_num

}Captor_id_e;


/**
  * @brief  Active channel structures definition
  */
typedef enum
{
  TIM_ACTIVE_CHANNEL_1        = 0x01U,    /*!< The active channel is 1     */
  TIM_ACTIVE_CHANNEL_2        = 0x02U,    /*!< The active channel is 2     */
  TIM_ACTIVE_CHANNEL_3        = 0x04U,    /*!< The active channel is 3     */
  TIM_ACTIVE_CHANNEL_4        = 0x08U,    /*!< The active channel is 4     */
  TIM_ACTIVE_CHANNEL_CLEARED  = 0x00U     /*!< All active channels cleared */
} TIM_ActiveChannel;


/**
 * @brief  TIM_Capture_object
 * @note   
 * @retval None
 */
typedef struct TIM_Captor{
	
	TIM_HandleTypeDef *htimx;												/*! < TIM Time Base Handle Structure definition,This property is used for compatibility with the HAL library.
									  											  If you are using the standard library or another library, this item can be assigned a value of 0	>*/
	
	uint32_t Cap_val1;														/* !< The value of CCRx captured by Tim .
									  											  This parameter can be acquired by function 'HAL_TIM_ReadCapturedValue' if you use HAL library  > */
	uint32_t Cap_val2;														/* !< The value of CCRx captured by Tim .
									  											  This parameter can be acquired by function 'HAL_TIM_ReadCapturedValue' if you use HAL library  > */
	
	float Duty;																/* !< The duty captured by Captor obj > */		
	float Frequency;														/* !< The frequency captured by Captor obj > */
	float Pulse;															/* !< The frequency captured by Captor obj > */

	uint32_t Channel_UP;													/* !< The rising edge of the PWM waveform captures the channel > */
	uint32_t Channel_DN;													/* !< The falling edge of the PWM waveform captures the channel > */

	
	uint8_t is_valid:1;														/* !< Whether the initialization is successful > */

	void (* Captor_init)(uint16_t);											/* !< Initialization of the input catcher > */
	uint32_t (* TIM_Capture)(struct TIM_Captor * ,uint8_t Level);			/* !< Obtain the CCR value of PWM input > */
	void (* Duty_cal)(struct TIM_Captor * p_Dev,TIM_ActiveChannel);			/* !< Duty cycle calculation of PWM waveform > */
	void (* Frequency_cal)(struct TIM_Captor * p_Dev,TIM_ActiveChannel);	/* !< Frequency calculation of PWM waveform > */
	void (* Pulse_cal)(struct TIM_Captor * p_Dev);							/* !< Pulse width calculation of PWM waveform > */
	
}TIM_Captor_t, *p_TIM_Captor;


/* ----------------------- public typedef ----------------------- */
typedef	TIM_Captor_t Captor_viewer;											//Use this code to externally initialize and view the structure object
/*--- Public variable declarations ----------------------------------------------------*/
extern struct LEDDevice LED[LED_NUM];
extern struct TIM_Captor Captor[CAPTOR_NUM];								//Input capture object global declaration
/*--- Public function declarations ----------------------------------------------------*/
void PWM_Breath(struct LEDDevice * p_Dev);
void LED_Init(void);



/*	TIM1 Two input capture API  */
void Captor_init(void);														//You simply initialize directly in the BSP initialization function
void tim_debug_raw_printf(Captor_viewer* p_Dev);		

	
#ifdef __cplusplus
}
#endif

#endif  // __DRV_TIM_H__
