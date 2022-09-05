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

/*--- Private dependencies ------------------------------------------------------------*/
#include "bsp_spi.h"
#include "gpio.h"
#include "bsp_flash.h"
#include "systime.h"
/*--- Public variable definitions -----------------------------------------------------*/
uint8_t flash_status[4] = { 0 };
/*--- Private macros ------------------------------------------------------------------*/
#define GET_SYSTEME_US() Get_systime_ms()  // Get the time when the system has been running

/*--- Private type definitions --------------------------------------------------------*/
typedef struct {
	spi_sel_t_e sel;

	uint32_t comm_error;
} flash_t;

flash_t flash = { .sel = SPI_SEL_Flash };

uint8_t BSP_W25Qx_Read(uint8_t* pData, uint32_t ReadAddr, uint32_t Size) {
	return 0;
}

//��ȡ״̬�Ĵ���1�����ݣ������ȡ�ɹ�˵��SPIͨ�ſ���ʹ��
void BSP_W25Qx_Read_Status_Register_1_2(uint8_t* pData) {
}

void BSP_W25Qx_Read_ID(uint8_t* pData) {
}

/*     Test code     */
uint8_t buffer[30];
uint8_t buffer_SPI_Receive[30] = { 0 };

uint8_t buffer_SPI_Receive[30];

uint8_t buffer_address[] = { 0x00, 0x00, 0x00 };

void SPI_flash_sent_byte(uint8_t data) {
	HAL_SPI_Transmit(&hspi1, &data, 1, 1000);
}

void SPI_flash_sent_address(uint8_t* Sent) {
	HAL_SPI_Transmit(&hspi1, Sent, 3, 1000);
}

void SPI_flash_TransmitReceive(uint8_t* data, uint16_t size) {
	HAL_SPI_TransmitReceive(&hspi1, data, data, size, 1000);
}

void SPI_flash_get_device_ID(uint8_t* address) {
}

void spi_flash_test_read_id(uint8_t* address) {
}

#ifdef __cplusplus
}
#endif
