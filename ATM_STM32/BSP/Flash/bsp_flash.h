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

#ifndef __BSP_FLASH_H__
#define __BSP_FLASH_H__

#ifdef __cplusplus
extern "C" {
#endif

/*--- Public dependencies -------------------------------------------------------------*/
#include "sys.h"
/*--- Public macros -------------------------------------------------------------------*/
// W25Qxx INSTRUCTIONS (The Flash model in use is WX25Q16)
// 10.2.2 Instruction Set Table 1
#define WRITE_ENABLE						0X06  // 开启Flash芯片的写入
#define WRITE_DISABLE						0X04  // 禁止Flash芯片的写入
#define READ_STATUS_REGISTER_1				0X05  // 判断Flash读取工作的状态(S7-S0)
#define READ_STATUS_REGISTER_2				0X35  // 判断Flash读取工作的状态(S15-S8)
#define WRITE_STATUS_REGISTER				0X01  // 判断Flash写入工作的状态
#define PAGE_PROGRAM						0X02  // 一次最多写入256个字节（页编程）
#define QUAD_PAGE_PROGRAM					0X32  // 四倍页编程
#define BLOCK_ERASE_64						0xD8  // 64KB（块擦除）
#define BLOCK_ERASE_32						0X52  // 32KB（块擦除）
#define SECTOR_ERASE_4						0X20  // 4KB（扇区擦除）
#define CHIP_ERASE							0XC7  // 全片擦除
#define ERASE_SUSPEND						0X75  // 暂停擦除
#define ERASE_RESUNME						0X7A  // 恢复擦除
#define POWER_DOWN							0XB9  // 掉电模式
#define HIGH_PERFORMANCE_MODE				0XA3  // 高性能模式
#define MODE_BIT_RESET						0XFF  // 状态位复位
#define RELEASE_POWER_DOWN_OR_HPM_DEVICE_ID 0XAB  // 解除低功耗或者高性能模式
#define MANUFACTURER_DEVICE_ID				0X90  // 读取制造商/芯片ID
#define READ_UNIQUE_ID						0X4B  // 读取唯一ID
#define JEDEC_ID							0X9F  // JEDEC ID

/* Read — Command */
#define READ_DATA			  0X03	// 读数据
#define FAST_READ			  0X0B	// 快速读
#define FAST_READ_DUAL_OUTPUT 0X3B	// 快速读双输出
#define FAST_READ_DUAL_IO	  0XBB	// 快速读双路
#define FAST_READ_QUAD_OUTPUT 0X6B	// 快速读四路输出
#define FAST_READ_QUAD_IO	  0XEB	// 快速读四路

#define SPI_Flash_CS_LOW(x)	 HAL_GPIO_WritePin(SPI1_CS_FLASH_GPIO_Port, SPI1_CS_FLASH_Pin, x)
#define SPI_Flash_CS_HIGH(x) HAL_GPIO_WritePin(SPI1_CS_FLASH_GPIO_Port, SPI1_CS_FLASH_Pin, x)

/*--- Public type definitions ---------------------------------------------------------*/
/*--- Public variable declarations ----------------------------------------------------*/
extern uint8_t flash_status[4];
extern uint8_t buffer[30];

/*--- Public function declarations ----------------------------------------------------*/
extern uint16_t SPI_W25X_ReadID(void);
uint8_t			SPI_W25X_ReadSR(void);
void			SPI_W25X_Write_SR(unsigned char sr);
void			SPI_W25X_Write_Enable(void);
void			SPI_W25X_Write_Disable(void);
void			SPI_W25X_Read(unsigned char *pBuffer, uint32_t ReadAddr, uint16_t NumByteToRead);
void			SPI_W25X_Write(unsigned char *pBuffer, uint32_t WriteAddr, uint16_t NumByteToWrite);
void			SPI_W25X_Erase_Chip(void);
void			SPI_W25X_Erase_Sector(uint32_t Dst_Addr);
void			SPI_W25X_Wait_Busy(void);
void			SPI_W25X_PowerDown(void);
void			SPI_W25X_WAKEUP(void);

uint8_t SPI_W25X_Read_onebyte(unsigned int ReadAddr);
void	SPI_W25X_Write_onebyte(uint16_t WriteAddr, uint8_t data);

/* ------- test api ------- */
void BSP_W25Qx_Read_Status_Register_1_2(uint8_t *pData);
void BSP_W25Qx_Read_ID(uint8_t *pData);

// HAL_tester
void SPI_flash_get_device_ID(uint8_t *address);

// my tester
void spi_flash_test_read_id(uint8_t *address);

#ifdef __cplusplus
}
#endif

#endif	// __DRV_FLASH_H__
