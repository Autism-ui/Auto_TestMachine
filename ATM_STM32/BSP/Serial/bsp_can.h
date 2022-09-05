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

#ifndef __BSP_CAN_H__
#define __BSP_CAN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "can.h"

// CAN数据帧为8个字节
#define CAN1_TX_BUFFER_SIZE (8)
#define CAN1_RX_BUFFER_SIZE (8)

typedef struct {
	uint8_t				CANx;
	uint8_t				Data[8];
	CAN_TxHeaderTypeDef SendCanTxMsg;
} CAN_TxMsg_t;

typedef struct {
	uint8_t				CANx;
	uint8_t				Data[8];
	CAN_RxHeaderTypeDef ReceiveCanRxMsg;
} CAN_RxMsg_t;

typedef struct {
	CAN_HandleTypeDef *hcan;
	uint32_t		   StdId;

	uint8_t *tx_buffer;
	uint16_t tx_buffer_size;

	uint8_t *rx_buffer;
	uint16_t rx_buffer_size;

	uint8_t Recevie_finish;
	uint8_t is_rx_ITvalid;

} CAN_Manage_Obj_t;

extern uint8_t			txbuf[8];
extern CAN_Manage_Obj_t CAN1_Manage;

void Canbus_Recevice_Data_IT(CAN_HandleTypeDef *hcan);

void CAN_Sendata_protocl(CAN_HandleTypeDef *CAN_Num,
						 int16_t			data1,
						 int16_t			data2,
						 int16_t			data3,
						 int16_t			data4);
void CAN_SendData(CAN_HandleTypeDef *CANx, uint8_t id_type, uint32_t id, uint8_t data[8]);
void CAN_Manage_Init(void);

void CAN1_IT_Init(void);

#ifdef __cplusplus
}
#endif

#endif	// __DRV_CAN_H__
