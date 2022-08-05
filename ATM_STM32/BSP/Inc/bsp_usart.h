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
extern "C"
{
#endif

    /*--- Public dependencies -------------------------------------------------------------*/
#include "usart.h"
    /*--- Public macros -------------------------------------------------------------------*/
#define UART_RX_DMA_SIZE (1024)
#define BUFF_MAX_LEN (50)
#define BUFF_LEN (18)
    /*--- Public type definitions ---------------------------------------------------------*/
		
    /*--- Public variable declarations ----------------------------------------------------*/
    extern uint8_t INTERACT_BUFF[BUFF_LEN];
/*--- Public function declarations ----------------------------------------------------*/
    void USART3_Receive_Handler(UART_HandleTypeDef *huart, uint16_t MAX_LEN, uint16_t LEN);
    void USART3_DMA_Init(void);


#ifdef __cplusplus
}
#endif

#endif // __BSP_USART_H__
