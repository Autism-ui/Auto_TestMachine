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

#ifndef __BSP_USART_H__
#define __BSP_USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/*--- Public dependencies -------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "usart.h"
#include "queue.h"
/*--- Public macros -------------------------------------------------------------------*/
#ifndef DOUBLE_BUFFER
#define UART_RX_DMA_SIZE (1024)
#define BUFF_MAX_LEN	 (50)
#define BUFF_LEN		 (18)
#endif

#ifdef DOUBLE_BUFFER
#define UART_BUFF_SIZE 25
#endif
/*--- Public type definitions ---------------------------------------------------------*/
#ifdef DOUBLE_BUFFER
#pragma pack(4)
typedef struct {
	uint16_t len;
	uint8_t	 data[UART_BUFF_SIZE];
} USART_DATA_t;
#pragma pack()
/*--- Public variable declarations ----------------------------------------------------*/
extern uint8_t		INTERACT_BUFF[BUFF_LEN];
extern xQueueHandle Queue_Receive;
#endif
/*--- Public function declarations ----------------------------------------------------*/
#ifndef DOUBLE_BUFFER
void USART3_Receive_Handler(UART_HandleTypeDef *huart, uint16_t MAX_LEN, uint16_t LEN);
void USART3_DMA_Init(void);
extern xQueueHandle Queue_Receive;
#endif

#ifdef DOUBLE_BUFFER
void DMA_M0_RC_Callback(DMA_HandleTypeDef *hdma);
void DMA_M1_RC_Callback(DMA_HandleTypeDef *hdma);
void DMA_Error_Callback(DMA_HandleTypeDef *hdma);
void Enable_Uart3(void);
#endif

#ifdef __cplusplus
}
#endif

#endif	// __BSP_USART_H__
