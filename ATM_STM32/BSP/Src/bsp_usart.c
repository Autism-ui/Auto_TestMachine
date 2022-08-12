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

#include "bsp_usart.h"

#ifdef __cplusplus
extern "C" {
#endif

/*--- Private dependencies ------------------------------------------------------------*/
#include "stdlib.h"
#include "string.h"
/*--- Public variable definitions -----------------------------------------------------*/
#ifndef DOUBLE_BUFFER
uint8_t		 INTERACT_BUFF[BUFF_LEN];
xQueueHandle Queue_Receive;
#endif
#ifdef DOUBLE_BUFFER
xQueueHandle Queue_Receive;
USART_DATA_t Receive_Data[2];
#endif
/*--- Private macros ------------------------------------------------------------------*/

/*--- Private type definitions --------------------------------------------------------*/

/*--- Private variable definitions ----------------------------------------------------*/

/*--- Private function declarations ---------------------------------------------------*/

/*--- Private function definitions ----------------------------------------------------*/
#ifndef DOUBLE_BUFFER
/**
 * @brief      Enable global uart it and do not use DMA transfer done it
 * @param[in]  huart: uart IRQHandler id
 * @param[in]  pData: receive buff
 * @param[in]  Size:  buff size
 * @retval     set success or fail
 */
static int UART_Receive_DMA_No_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint32_t Size) {
	uint32_t tem = 0;
	tem			 = huart->RxState;
	if(tem == HAL_UART_STATE_READY) {
		if((pData == NULL) || (Size == 0)) {
			return HAL_ERROR;
		}

		huart->pRxBuffPtr = pData;
		huart->RxXferSize = Size;
		huart->ErrorCode  = HAL_UART_ERROR_NONE;

		/* Enable the DMA Stream */
		HAL_DMA_Start(huart->hdmarx, (uint32_t)&huart->Instance->DR, (uint32_t)pData, Size);

		/* Start DMA Transmit */
		SET_BIT(huart->Instance->CR3, USART_CR3_DMAR);

		return HAL_OK;
	} else
		return HAL_BUSY;
}
/**
 * @brief      returns the number of remaining data units in the current DMAy Streamx transfer.
 * @param[in]  dma_stream: where y can be 1 or 2 to select the DMA and x can be 0
 *             to 7 to select the DMA Stream.
 * @retval     The number of remaining data units in the current DMAy Streamx transfer.
 */
static uint16_t DMA_Current_data_counter(DMA_Stream_TypeDef *dma_stream) {
	return ((uint16_t)(dma_stream->NDTR));
}

/**
 * @brief       Handle received Data
 * @param[out]  data:   structure to save handled data
 * @param[in]   buff: the buff which saved raw rc data
 * @retval
 */
uint8_t		sdata[BUFF_LEN];
static void Data_Callback_Handler() {
	BaseType_t xHigherPriorityTaskWoken;
	memcpy(sdata, INTERACT_BUFF, sizeof(INTERACT_BUFF));
	xQueueSendFromISR(Queue_Receive, &INTERACT_BUFF, &xHigherPriorityTaskWoken);
	/*如果xHigherPriorityTaskWoken == pdTRUE的话，在中断服务函数执行完之后进行一次任务切换*/
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/**
 * @brief      The IDIE IT flag bit is clear after the serial port receives the frame data
 * @param[in]  huart: uart IRQHandler id
 * @param[in]  MAX_LEN:BUFF_MAX_LEN(maro)
 * @param[in]  LEN:BUFF_LEN(maro)
 * @retval     NONE
 */
static void UART_RX_IDLE_Callback(UART_HandleTypeDef *huart, uint16_t MAX_LEN, uint16_t LEN) {
	/* 清楚空闲IT标志避免空闲中断 */
	__HAL_UART_CLEAR_IDLEFLAG(huart);

	/* 在空闲中断中处理接收到的数据 */
	if(huart == &huart3) {
		__HAL_DMA_DISABLE(huart->hdmarx);
		/* 从DMA处理 */
		if((MAX_LEN - DMA_Current_data_counter(huart->hdmarx->Instance)) == LEN) {
			// 这里写一个解包处理函数
			Data_Callback_Handler();
		}
		/* 重新启动DMA */
		__HAL_DMA_SET_COUNTER(huart->hdmarx, BUFF_MAX_LEN);
		__HAL_DMA_ENABLE(huart->hdmarx);
	}
}
/*--- Public function definitions -----------------------------------------------------*/
/**
 * @brief      This function is called back when the UART interrupts
 * @param[in]  huart: uart IRQHandler id
 * @param[in]  MAX_LEN:BUFF_MAX_LEN(maro)
 * @param[in]  LEN:BUFF_LEN(maro)
 * @retval     NONE
 */
void USART3_Receive_Handler(UART_HandleTypeDef *huart, uint16_t MAX_LEN, uint16_t LEN) {
	if(__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE)
	   && __HAL_UART_GET_IT_SOURCE(huart, UART_IT_IDLE)) {
		UART_RX_IDLE_Callback(huart, MAX_LEN, LEN);
	}
}

/**
 * @brief      Initialize UART Device
 * @param      NONE
 * @retval     NONE
 */
void USART3_DMA_Init(void) {
	/* Open uart IDLE IT */
	__HAL_UART_CLEAR_IDLEFLAG(&huart3);
	__HAL_UART_ENABLE_IT(&huart3, UART_IT_IDLE);

	UART_Receive_DMA_No_IT(&huart3, INTERACT_BUFF, BUFF_MAX_LEN);
}
#endif
#ifdef DOUBLE_BUFFER
void DMA_M0_RC_Callback(DMA_HandleTypeDef *hdma) {
	BaseType_t xHigherPriorityTaskWoken;
	Receive_Data[0].len = hdma->Instance->NDTR;
	xQueueSendFromISR(Queue_Receive, &Receive_Data[0], &xHigherPriorityTaskWoken);
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void DMA_M1_RC_Callback(DMA_HandleTypeDef *hdma) {
	BaseType_t xHigherPriorityTaskWoken;
	Receive_Data[1].len = hdma->Instance->NDTR;
	xQueueSendFromISR(Queue_Receive, &Receive_Data[1], &xHigherPriorityTaskWoken);
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

// DMA 传输错误回调函数
void DMA_Error_Callback(DMA_HandleTypeDef *hdma) {
	// 异常处理
}

void Enable_Uart3(void) {
	uint32_t u32wk0;
	SET_BIT(huart3.Instance->CR3, USART_CR3_DMAR);
	HAL_DMAEx_MultiBufferStart_IT(&hdma_usart3_rx,
								  (uint32_t)(&huart3.Instance->DR),
								  (uint32_t)&Receive_Data[0].data[0],
								  (uint32_t)&Receive_Data[1].data[0],
								  UART_BUFF_SIZE);

	// 解决DMA在启动时，如果收到大量的数据会出现死机的问题
	u32wk0 = huart3.Instance->SR;
	u32wk0 = huart3.Instance->DR;
	UNUSED(u32wk0);
}
#endif

#ifdef __cplusplus
}
#endif
