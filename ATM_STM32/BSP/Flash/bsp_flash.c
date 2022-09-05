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
 * @file drv_flash.c
 * @author Hans (316383560@qq.com)
 * @brief This file is the driver source file for the Flash peripheral.
 *        The Flash model in use is WX25Q16.
 * @version 0.1
 * @date 2022-08-15
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/*--- Private dependencies ------------------------------------------------------------*/
#include "bsp_spi.h"
#include "gpio.h"
#include "bsp_flash.h"
/*--- Public variable definitions -----------------------------------------------------*/
uint8_t flash_status[4] = {0};
/*--- Private macros ------------------------------------------------------------------*/
#define GET_SYSTEME_US() get_time_ms()          //Get the time when the system has been running


/*--- Private type definitions --------------------------------------------------------*/
typedef struct {
    spi_sel_t_e			sel;

    uint32_t			comm_error;
}flash_t;

flash_t flash = {.sel = SPI_SEL_Flash};

/*--- Private variable definitions ----------------------------------------------------*/

/*--- Private function declarations ---------------------------------------------------*/
//static void __write_flash(uint8_t REG,uint8_t TxData);
//static uint8_t __read_flash(uint8_t REG);
/*--- Private function definitions ----------------------------------------------------*/
///**
// * @brief  __write_flash
// * @note   Note that Flash is a 24-bit address
// * @param  REG: 
// * @param  TxData: 
// * @retval None
// */
//*/
//static void __write_flash(uint8_t REG,uint8_t TxData)
//{
//	uint8_t	  rxData[2] = { 0 };
//	uint8_t	  txData[2] = { addr & 0x7f, data };
//	spi_err_t err		= SPI_ERR_NONE;

//	err = bsp_spi_Transfer(current_dev->sel, txData, rxData, 2);
//	if(err != SPI_ERR_NONE) {
//		current_dev->comm_error++;
//	}
//}


//static uint8_t __read_flash(uint8_t REG )
//{
//	uint8_t	  rxData[2] = { 0 };
//	uint8_t	  txData[2] = { addr | 0x80, 0xFF };
//	spi_err_t err		= SPI_ERR_NONE;

//	err = bsp_spi_Transfer(current_dev->sel, txData, rxData, 2);
//	if(err != SPI_ERR_NONE) {
//		current_dev->comm_error++;
//	}
//	return rxData[1];
//}

///*--- Public function definitions -----------------------------------------------------*/

///*********************************************************************
//*
//*	function name  : SPI_W25X_ReadSR   
//*	function       : read W25Q16 status register
//*	input          :
//*	output         :  nonce
//*	return         :  byte
//*	revised record ：1.
//*                  2.
//*remarks         :  
//BIT:   7    6    5    4    3    2    1    0
//       SPR  RV   TB   BP2  BP1  BP0  WEL  BUSY
//SPR:默认0,状态寄存器保护位,配合WP使用
//TB,BP2,BP1,BP0:FLASH区域写保护设置
//WEL:写使能锁定
//BUSY:忙标记位(1,忙;0,空闲)
//默认:0x00
//**********************************************************************/
//uint8_t SPI_W25X_ReadSR(void)
//{
//    uint8_t byte = 0;

//    SPI_ReadWriteByte(W25X_ReadStatusReg); /*send read status register command */
//    byte = SPI_ReadWriteByte(0Xff);        /*read one byte */

//    return byte;
//}

//void SPI_W25X_Write_Enable(void){
//	
//	uint8_t cmd[] = {WRITE_ENABLE};
//	spi_err_type_e err = SPI_ERR_NONE;
//	
//	err = bsp_spi_Transfer(flash.sel,cmd,NULL,1);
//    if(err != SPI_ERR_NONE){
//        flash.comm_error++;
//    }
//}


//void SPI_W25X_Write_Disable(void){
//	
//		uint8_t cmd[] = {WRITE_DISABLE};
//		spi_err_type_e err = SPI_ERR_NONE;
//	
//		err = bsp_spi_Transfer(flash.sel,cmd,NULL,1);
//    if(err != SPI_ERR_NONE){
//        flash.comm_error++;
//    }
//}

/**
  * @brief  Reads an amount of data from the QSPI memory.
  * @param  pData: Pointer to data to be read
  * @param  ReadAddr: Read start address
  * @param  Size: Size of data to read    
  * @retval QSPI memory status
  */
uint8_t BSP_W25Qx_Read(uint8_t* pData, uint32_t ReadAddr, uint32_t Size)
{
//	uint8_t cmd[4];

//	/* Configure the command */
//	cmd[0] = READ_DATA;
//	cmd[1] = (uint8_t)(ReadAddr >> 16);
//	cmd[2] = (uint8_t)(ReadAddr >> 8);
//	cmd[3] = (uint8_t)(ReadAddr);
//	
//	spi_err err = SPI_ERR_NONE;
//	
////	err = bsp_spi_Transfer(flash.sel,cmd,pData,Size);
//	
	return 0;
}


//读取状态寄存器1的数据，如果读取成功说明SPI通信可以使用
void BSP_W25Qx_Read_Status_Register_1_2(uint8_t* pData){
//	
//	uint8_t cmd[] = {WRITE_DISABLE};
//	
//	spi_err err = SPI_ERR_NONE;
////	err = bsp_spi_Transfer(flash.sel,cmd,pData,2);
//	if(err != SPI_ERR_NONE){
//     flash.comm_error++;
//  }
	
}

void BSP_W25Qx_Read_ID(uint8_t* pData){
//	uint8_t cmd[] = {MANUFACTURER_DEVICE_ID,0x00,0x00,0x00};
//	
//	spi_err err = SPI_ERR_NONE;
////	err = bsp_spi_Transfer(flash.sel,cmd,pData,4);
//	
//	if(err != SPI_ERR_NONE){
//     flash.comm_error++;
//  }
	
}

/*     Test code     */
uint8_t buffer[30];
uint8_t buffer_SPI_Receive[30] = {0};

uint8_t buffer_SPI_Receive[30];

uint8_t buffer_address[] = {0x00,0x00,0x00};

void SPI_flash_sent_byte(uint8_t data){
	HAL_SPI_Transmit(&hspi1,&data,1,1000);
}


void SPI_flash_sent_address(uint8_t* Sent){
	HAL_SPI_Transmit(&hspi1,Sent,3,1000);
}

void SPI_flash_TransmitReceive(uint8_t *data,uint16_t size){
	HAL_SPI_TransmitReceive(&hspi1,data,data,size,1000);
}

void SPI_flash_get_device_ID(uint8_t *address){
//	SPI_flash_cs_low(0u);
//	SPI_flash_sent_byte(MANUFACTURER_DEVICE_ID);
//	SPI_flash_sent_address(buffer_address);
//	SPI_flash_TransmitReceive(address,2);
//	SPI_flash_cs_high(1u);
}

void spi_flash_test_read_id(uint8_t *address){
	
	//uint8_t cmd[] = {MANUFACTURER_DEVICE_ID,0x00,0x00,0x00};
//	
//	bsp_spi_write_read(flash.sel,cmd,address,2);
//	uint8_t cmd = MANUFACTURER_DEVICE_ID;
	


//	SPI_flash_cs_low(0u);
//	SPI_flash_sent_byte(MANUFACTURER_DEVICE_ID);
//	SPI_flash_sent_address(buffer_address);
//	SPI_flash_TransmitReceive(address,2);
//	SPI_flash_cs_high(1u);

//	SPI_flash_cs_low(0u);	
//	bsp_spi_write(flash.sel,&cmd,1);
//	bsp_spi_write(flash.sel,buffer_address,3);
//	bsp_spi_write_read(flash.sel,cmd,address,4);
//	
//	bsp_spi_read(flash.sel,address,2);
//	SPI_flash_cs_high(1u);
	
//	bsp_spi_Transfer(flash.sel,cmd,address,4,2);
	
	
}


#ifdef __cplusplus
}
#endif
