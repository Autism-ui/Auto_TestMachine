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

#ifndef __DRV_SPI_H__
#define __DRV_SPI_H__

#ifdef __cplusplus
extern "C" {
#endif

/*-------------------------- Readme first when you use this file --------------------------*/
/**
 * Method of use:
 *  when you want to use this function, you can just put 'bsp_spi_init' into the BSP init
 function,then the spi will be useful
 *
 *
 * instructions:
 *  Call the 'bsp_spi_Transfer' function when you want to use the SPI bus for communication.
   Of course, you need to populate the function with parameters,
   in which case you need to provide an object that specifies the device that the SPI needs to
 transmit (the first argument), followed by the sent buffer, received buffer, and number of bytes.
 *
 *
 * API to use:
 * 1. bsp_spi_init
 * 2. bsp_spi_Transfer
 *
 *
 * * * * * * * * * * * * *
 */

/*--- Public dependencies -------------------------------------------------------------*/
#include "spi.h"

/*--- Public macros -------------------------------------------------------------------*/
#define SPI_NUM 1
/*--- Public type definitions ---------------------------------------------------------*/
typedef enum {
	SPI_ERR_NONE,
	SPI_ERR_RECEIVE,
	SPI_ERR_TRANSMIT,
	SPI_ERR_WR,
	SPI_ERR_TIMEOUT,
} spi_err_type_e;

typedef enum {
	SPI_SEL_NONE,
	SPI_SEL_Flash,
	SPI_SEL_LCD,
} spi_sel_t_e;	// Flash���ڲ���SPIͨ���Ƿ��ͨ

typedef enum {
	SPI_CS_DOWN,
	SPI_CS_UP,
} spi_cs_status_e;

typedef enum {
	SPI_STOP,
	SPI_SEND,
	SPI_RECEIVE,
} spi_send_state_e;

typedef struct spi_Device_t {  // spi�豸����

	//����
	SPI_HandleTypeDef *spix;
	spi_sel_t_e		   spi_id;	//�豸id,��ͬһ��SPI�豸�ϣ�SPI1����SPI2�Ͽ����кܶ��豸��������ID���������ǣ�
	uint8_t			   cs_status;  //Ƭѡ�ߵ�״̬

	uint8_t is_vaild : 1;
	uint8_t send_state : 2;

	//����
	void (*spi_set_cs)(struct spi_Device_t *, GPIO_PinState);

} SPI_Device, *p_SPI_Device;

typedef spi_err_type_e spi_err;	 //����ⲿ��������ͽ��й۲⣬����Ҫֱ��ʹ��spi_err_type_e

/*--- Public variable declarations ----------------------------------------------------*/
// extern SPI_Device SPI[SPI_NUM];
extern spi_err spi_err_state;  //ȫ�֣��ⲿ���Թ۲�spi�豸״̬,Ҫ�۲�ֱ���ڸ�.c�ļ��ж���spi_err spi_err_state����

/*--- Public function declarations ----------------------------------------------------*/
/*---------------- �����API�ӿ� ----------------*/
spi_err bsp_spi_write(spi_sel_t_e sel, uint8_t *pTxData, uint16_t Size);
spi_err bsp_spi_read(spi_sel_t_e sel, uint8_t *pRxData, uint16_t Size);
spi_err bsp_spi_write_read(spi_sel_t_e sel, uint8_t *pTxData, uint8_t *pRxData, uint16_t Size);

spi_err bsp_spi_Transfer(spi_sel_t_e sel,
						 uint8_t	 *pTxData,
						 uint8_t	 *pRxData,
						 uint16_t	 tSize,
						 uint16_t	 rSize);

spi_err bsp_spi_write_NO_CS(spi_sel_t_e sel, uint8_t *pTxData, uint16_t Size);
spi_err bsp_spi_read_NO_CS(spi_sel_t_e sel, uint8_t *pRxData, uint16_t Size);
spi_err bsp_spi_write_read_NO_CS(spi_sel_t_e sel,
								 uint8_t	 *pTxData,
								 uint8_t	 *pRxData,
								 uint16_t	 Size);

#ifdef __cplusplus
}
#endif

#endif	// __DRV_SPI_H__
