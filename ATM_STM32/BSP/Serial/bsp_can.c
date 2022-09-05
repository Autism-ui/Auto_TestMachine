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

#include "sys.h"

#ifdef __cplusplus
extern "C" {
#endif

/*--- Private dependencies ------------------------------------------------------------*/
#include "bsp_can.h"
/*--- Public variable definitions -----------------------------------------------------*/
CAN_manage_obj_t can1_manage_obj = { 0 };

uint8_t can1_tx_buff[CAN1_TX_BUFFER_SIZE] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
uint8_t can1_rx_buff[CAN1_RX_BUFFER_SIZE];

uint8_t txbuf[8] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };

/*--- Private macros ------------------------------------------------------------------*/
//#define CAN2_INVAILD						//�Ƿ�ʹ��CAN2

#define CAN_TEST 1

/*--- Private type definitions --------------------------------------------------------*/

CAN_FilterTypeDef sFilterConfig;

/*--- Private variable definitions ----------------------------------------------------*/
// extern CAN_HandleTypeDef hcan1;
/*--- Private function declarations ---------------------------------------------------*/

/*--- Private function definitions ----------------------------------------------------*/

/**
 * @brief  FIFO�����ʼ��
 * @param  CANx 		CAN���
 * 		id_type ��	id���� CAN_ID_STD�� CAN_ID_EXT
 *			id			id��
 * 		data[8]		8������
 * @retval None
 */
void MX_Filter_Init(CAN_FilterTypeDef sFilterConfig) {
	sFilterConfig.FilterBank		   = 0;	 //������ 0
	sFilterConfig.FilterMode		   = CAN_FILTERMODE_IDMASK;
	sFilterConfig.FilterScale		   = CAN_FILTERSCALE_32BIT;
	sFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO1;	//������ 0 ������ FIFO0
	sFilterConfig.FilterActivation	   = ENABLE;			//�����˲��� 0
	sFilterConfig.FilterIdHigh		   = 0x0000;			// 32 λ ID
	sFilterConfig.FilterIdLow		   = 0x0000;
	sFilterConfig.FilterMaskIdHigh	   = 0x0000;  // 32 λ MASK
	sFilterConfig.FilterMaskIdLow	   = 0x0000;
	HAL_CAN_ConfigFilter(&hcan1, &sFilterConfig);
}

/**
 * @brief  CAN1�����жϳ�ʼ��
 * @param  CANx 		CAN���
 * 		id_type ��	id���� CAN_ID_STD�� CAN_ID_EXT
 *			id			id��
 * 		data[8]		8������
 * @retval None
 */
void CAN1_IT_Init(void) {
	/* ʹ���˲��� */
	MX_Filter_Init(sFilterConfig);
	/* ����CAN */
	HAL_CAN_Start(&hcan1);
	/* ʹ��CAN�ж� */
	//__HAL_CAN_ENABLE_IT(&hcan1, CAN_IT_RX_FIFO1_MSG_PENDING);

	HAL_StatusTypeDef HAL_Status;

	HAL_Status = HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO1_MSG_PENDING);
	if(HAL_Status != HAL_OK) {
		Error_Handler();
	}
}

/*--- Public function definitions -----------------------------------------------------*/
void MX_Filter_Init(CAN_FilterTypeDef sFilterConfig);
/**
 * @brief  CAN��������
 * @param  CANx 		CAN���
 * 		id_type ��	id���� CAN_ID_STD�� CAN_ID_EXT
 *			id			id��
 * 		data[8]		8������
 * @retval None
 */
void CAN_SendData(CAN_HandleTypeDef* CANx, uint8_t id_type, uint32_t id, uint8_t data[8]) {
	CAN_TxMsg_t TxMessage;

	if(id_type == CAN_ID_STD) {
		TxMessage.SendCanTxMsg.StdId = id;
	} else {
		TxMessage.SendCanTxMsg.ExtId = id;	// ID��
	}

	TxMessage.SendCanTxMsg.IDE				  = id_type;	   // ID����
	TxMessage.SendCanTxMsg.RTR				  = CAN_RTR_DATA;  //���͵�Ϊ����
	TxMessage.SendCanTxMsg.DLC				  = 0x08;		   //���ݳ���Ϊ8�ֽ�
	TxMessage.SendCanTxMsg.TransmitGlobalTime = DISABLE;

	/*����Ҫ���͵�����*/
	if(CANx == &hcan1) {
		TxMessage.CANx = 1;
	}
#ifdef CAN2_INVAILD
	else if(CANx == &hcan2) {
		TxMessage.CANx = 2;
	}

#endif

	for(int i = 0; i < 8; i++) {
		TxMessage.Data[i] = data[i];
	}
	// HAL_CAN_AddTxMessage(&hcan1,&TxMessage.SendCanTxMsg,TxMessage.Data,(uint32_t
	// *)CAN_TX_MAILBOX0);
	xQueueSend(xQueueCanSend, &TxMessage, 10);
}

/*
 *��飺����can���͵ĺ��� ����δ��Э����������������������������ڽ��н�һ���ķ�װ
 */
void CAN_Sendata_protocl(CAN_HandleTypeDef* CAN_Num,
						 int16_t			data1,
						 int16_t			data2,
						 int16_t			data3,
						 int16_t			data4) {
	uint8_t data[8];

	//���ݸ�ʽ���˵����P32
	data[0] = data1 >> 8;
	data[1] = data1;
	data[2] = data2 >> 8;
	data[3] = data2;
	data[4] = data3 >> 8;
	data[5] = data3;
	data[6] = data4 >> 8;
	data[7] = data4;

	CAN_SendData(CAN_Num, CAN_ID_STD, 0x200, data);
}

void can_manage_init(void) {
	can1_manage_obj.hcan		   = &hcan1;
	can1_manage_obj.StdId		   = 0x123;
	can1_manage_obj.rx_buffer	   = can1_rx_buff;
	can1_manage_obj.rx_buffer_szie = CAN1_RX_BUFFER_SIZE;
	can1_manage_obj.tx_buffer	   = can1_tx_buff;
	can1_manage_obj.tx_buffer_szie = CAN1_TX_BUFFER_SIZE;
	can1_manage_obj.Recevie_finish = 0;
}

/*
 *
 */
void Canbus_Recevice_Data_IT(CAN_HandleTypeDef* hcan) {
	CAN_RxMsg_t CAN_RxMessage;
	if(__HAL_CAN_GET_IT_SOURCE(&hcan1, CAN_IT_RX_FIFO1_MSG_PENDING)) {
		HAL_CAN_GetRxMessage(&hcan1,
							 CAN_RX_FIFO1,
							 &CAN_RxMessage.ReceiveCanRxMsg,
							 CAN_RxMessage.Data);
		//���CAN��
		CAN_RxMessage.CANx = 1;
		if(CAN_RxMessage.ReceiveCanRxMsg.StdId == 0x123) {
			xQueueSendToBackFromISR(xQueueCanReceive, &CAN_RxMessage, 0);
			// can1_manage_obj.Recevie_finish = 1;
			// //������ɱ�־λ
		}

		__HAL_CAN_CLEAR_FLAG(&hcan1, CAN_IT_RX_FIFO1_MSG_PENDING);
	}
}

///**
// * @brief  HAL Library CAN Recevie IT callback function redirect
// * @note
// * @param  *hcan:
// * @retval None
// */
// void HAL_CAN_RxFifo1MsgPendingCallback(CAN_HandleTypeDef *hcan){

//	if(hcan == &hcan1){

//		if(can1_manage_obj.){

//		}

//		Canbus_Recevice_Data_IT();
//	}
//	// else if(hcan == &hcan2){
//	// }
//}

#ifdef CAN_TEST

// can
CAN_TxHeaderTypeDef Can_Tx;

//	Can_Tx.StdId = 0x123;
//	Can_Tx.ExtId = 0x123;
//	Can_Tx.IDE = CAN_ID_STD;
//	Can_Tx.RTR = 0;
//	Can_Tx.DLC = 8;

void can_test(void) {
	//		HAL_CAN_AddTxMessage(&hcan1,&Can_Tx,txbuf,(uint32_t*)CAN_TX_MAILBOX0);
	//		HAL_Delay(500);

	CAN_SendData(&hcan1, CAN_ID_STD, 0x123, txbuf);
	HAL_Delay(500);
}

#endif

#ifdef __cplusplus
}
#endif
