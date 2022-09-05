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

#ifndef __DRV_CAN_H__
#define __DRV_CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

/*--- Public dependencies -------------------------------------------------------------*/
#include "can.h"
/*--- Public macros -------------------------------------------------------------------*/
#define CAN1_TX_BUFFER_SIZE (8)	 // CAN数据帧为8个字节
#define CAN1_RX_BUFFER_SIZE (8)	 // CAN数据帧为8个字节
/*--- Public type definitions ---------------------------------------------------------*/

/**
 * @brief
 * @note
 * @retval None
 */
typedef struct {
	uint8_t				CANx;  // can编号
	uint8_t				Data[8];
	CAN_TxHeaderTypeDef SendCanTxMsg;
} CAN_TxMsg_t;

/**
 * @brief
 * @note
 * @retval None
 */
typedef struct {
	uint8_t				CANx;  // can编号
	uint8_t				Data[8];
	CAN_RxHeaderTypeDef ReceiveCanRxMsg;
} CAN_RxMsg_t;

/**
 * @brief
 * @note
 * @retval None
 */
typedef struct {
	CAN_HandleTypeDef *hcan;
	uint32_t		   StdId;

	uint8_t *tx_buffer;
	uint16_t tx_buffer_szie;

	uint8_t *rx_buffer;
	uint16_t rx_buffer_szie;

	uint8_t Recevie_finish;
	uint8_t is_rx_ITvalid;

} CAN_manage_obj_t;

/*--- Public variable declarations ----------------------------------------------------*/
extern uint8_t			txbuf[8];
extern CAN_manage_obj_t can1_manage_obj;

/*--- Public function declarations ----------------------------------------------------*/
void Canbus_Recevice_Data_IT(CAN_HandleTypeDef *hcan);

void CAN_Sendata_protocl(CAN_HandleTypeDef *CAN_Num,
						 int16_t			data1,
						 int16_t			data2,
						 int16_t			data3,
						 int16_t			data4);
void CAN_SendData(CAN_HandleTypeDef *CANx, uint8_t id_type, uint32_t id, uint8_t data[8]);
void can_manage_init(void);
void CAN1_IT_Init(void);

#ifdef __cplusplus
}
#endif

#endif	// __DRV_CAN_H__
