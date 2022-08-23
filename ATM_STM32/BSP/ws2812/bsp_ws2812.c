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

#include "bsp_ws2812.h"

#ifdef __cplusplus
extern "C" {
#endif

/*--- Private dependencies ------------------------------------------------------------*/
#include "watchdog.h"
/*--- Public variable definitions -----------------------------------------------------*/

/*--- Private macros ------------------------------------------------------------------*/
/* 位带操作PE0 */
#define RGB_LED_HIGH (WS2812_GPIO_Port->ODR |= (1 << 0))
#define RGB_LED_LOW	 (WS2812_GPIO_Port->ODR &= ~(1 << 0))

#define DISABLE_IRQ() vPortRaiseBASEPRI()
#define ENABLE_IRQ()  vPortClearBASEPRIFromISR()
/*--- Private type definitions --------------------------------------------------------*/
typedef struct {
	uint8_t R;
	uint8_t G;
	uint8_t B;
} RGB_DATA;

/*--- Private variable definitions ----------------------------------------------------*/
static volatile RGB_DATA Show_RESULT_LED[WS2812_PIXEL_NUM] = { 0 };
/*--- Private function declarations ---------------------------------------------------*/
static void WS2812_Struct_Init(void) {
	for(uint8_t i = 0; i < WS2812_PIXEL_NUM; i++) {
		Show_RESULT_LED[i].R = 0;
		Show_RESULT_LED[i].G = 0;
		Show_RESULT_LED[i].B = 0;
	}
}
static void delay_100ns(uint16_t t) {
	while(--t) {
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
		__nop();
	}
}
static inline void RGB_LED_Write0(void) {
	RGB_LED_HIGH;
	delay_100ns(1);
	RGB_LED_LOW;
	delay_100ns(11);
}
static inline void RGB_LED_Write1(void) {
	RGB_LED_HIGH;
	delay_100ns(11);
	RGB_LED_LOW;
	delay_100ns(1);
}
static inline void Send_8bits(uint8_t dat) {
	for(uint8_t i = 0; i < 8; i++) {
		if(dat & 0x80) {
			RGB_LED_Write1();
		} else {
			RGB_LED_Write0();
		}
		dat = dat << 1;
	}
}
static void Send_2812_24bits(uint8_t RData, uint8_t GData, uint8_t BData) {
	Send_8bits(GData);
	Send_8bits(RData);
	Send_8bits(BData);
}
/*--- Private function definitions ----------------------------------------------------*/

/*--- Public function definitions -----------------------------------------------------*/
void bsp_WS2812_Init(void) {
	WS2812_Struct_Init();
	delay_100ns(2000);
	bsp_WS2812_LED_Off();
}
void bsp_WS2812_SyncAll(void) {
	DISABLE_IRQ();
	for(int i = 0; i < WS2812_PIXEL_NUM; i++) {
		Send_2812_24bits(Show_RESULT_LED[i].R, Show_RESULT_LED[i].G, Show_RESULT_LED[i].B);
	}
	ENABLE_IRQ();
}
void bsp_WS2812_LED_Off(void) {
	DISABLE_IRQ();
	for(int i = 0; i < WS2812_PIXEL_NUM; i++) {
		Send_2812_24bits(0, 0, 0);
	}
	ENABLE_IRQ();
	bsp_WS2812_SyncAll();
}
void bsp_WS2812_LED_Write(uint8_t led_index, uint8_t R, uint8_t G, uint8_t B) {
	if(led_index >= WS2812_PIXEL_NUM) {
		return;
	}
	Show_RESULT_LED[led_index].R = R;
	Show_RESULT_LED[led_index].G = G;
	Show_RESULT_LED[led_index].B = B;
}
void bsp_WS2812_WriteAll(uint8_t R, uint8_t G, uint8_t B) {
	for(uint8_t i = 0; i < WS2812_PIXEL_NUM; i++) {
		Show_RESULT_LED[i].R = R;
		Show_RESULT_LED[i].G = G;
		Show_RESULT_LED[i].B = B;
	}
}

void bsp_WS2812_Show(uint8_t R, uint8_t G, uint8_t B) {
	for(uint8_t i = 0; i < WS2812_PIXEL_NUM; i++) {
		Show_RESULT_LED[i].R = R;
		Show_RESULT_LED[i].G = G;
		Show_RESULT_LED[i].B = B;
	}
	bsp_WS2812_SyncAll();
}

#ifdef __cplusplus
}
#endif
