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

#ifndef __BSP_SPI_H__
#define __BSP_SPI_H__

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
} spi_sel_t_e;	// Flash用于测试SPI通信是否调通

typedef enum {
	SPI_CS_DOWN,
	SPI_CS_UP,
} spi_cs_status_e;

typedef enum {
	SPI_STOP,
	SPI_SEND,
	SPI_RECEIVE,
} spi_send_state_e;

typedef struct spi_Device_t {  // 设备对象

	// 属性
	SPI_HandleTypeDef *spix;
	spi_sel_t_e
			spi_id;	 // 设备id，在同一个spi设备上，spi1或者spi2上可以有很多设备，这里用ID来区分他们
	uint8_t cs_status;	// 片选线状态

	uint8_t is_vaild : 1;
	uint8_t send_state : 2;

	// 操作
	void (*spi_set_cs)(struct spi_Device_t *, GPIO_PinState);

} SPI_Device, *p_SPI_Device;

typedef spi_err_type_e spi_err;	 // 别称外部用这个类型进行观测，而不要直接使用spi_err_type_t

/*--- Public variable declarations ----------------------------------------------------*/
// extern SPI_Device SPI[SPI_NUM];
extern spi_err spi_err_state;  // 全局，外部可以观测spi设备状态，要观测直接在该.c文件中定义spi_err
							   // spi_err_state变量

/*--- Public function declarations ----------------------------------------------------*/
/*----------------对外的API接口----------------*/
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
