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

#ifndef __BUTTON_H__
#define __BUTTON_H__

#ifdef __cplusplus
extern "C" {
#endif

/*
	测试版:F407 按键分配
	K1 键:  PA0   (高电平表示按下)
*/
/* 根据功能定义按键宏 */
#define Button_Down_B1 BUTTON_1_DOWN
#define Button_Up_B1   BUTTON_1_UP
#define Button_Long_B1 BUTTON_1_LONG

/*--- Public dependencies -------------------------------------------------------------*/
#include "stdint.h"
/*--- Public macros -------------------------------------------------------------------*/
/*
	按键滤波时间50ms,单位10ms
	只有连续检测到50ms状态不变才认为有效,包括弹起和按下两种事件
	即使按键电路不做硬件滤波,该滤波机制也可以保证可靠地检测到按键事件
 */
#define Button_Filter_Time 5
#define Button_Long_Time   100 /* 单位10ms,持续1s,认为长按事件 */

/* 按键FIFO大小 */
#define Button_FIFO_Size 10
/*--- Public type definitions ---------------------------------------------------------*/
/* 按键ID,用于Button_GetState()函数的入口参数 */
typedef enum {
	BUTTON_B1 = 0,
} BUTTON_ID_T;

/* 按键对应的结构体变量 */
typedef struct {
	/* 函数指针,指向判断按键是否按下的函数 */
	uint8_t (*IsButtonDownFunc)(void); /* 按键按下的判断函数,1表示按下 */
	uint8_t	 Count;					   /* 滤波器计数器 */
	uint16_t LongCount;				   /* 长按计数器 */
	uint16_t LongTime;				   /* 按键按下持续的时间,0表示不检测长按 */
	uint8_t	 State;					   /* 按键当前的状态 */
	uint8_t	 RepeatSpeed;			   /* 连续按键周期 */
	uint8_t	 RepeatCount;			   /* 连续按键计数器 */
} BUTTON_T;

/*
	定义键值代码,必须按如下次序定时每个键的事件(按下,弹起,长按)
 */
typedef enum {
	BUTTON_NONE = 0,

	BUTTON_1_DOWN,	// 按下
	BUTTON_1_UP,	// 弹起
	BUTTON_1_LONG,	// 长按

} BUTTON_EVENT_T;

/* FIFO结构体 */
typedef struct {
	uint8_t Buf[Button_FIFO_Size]; /* 键值缓冲区 */
	uint8_t Read;				   /* 缓冲区读指针 */
	uint8_t Write;				   /* 缓冲区写指针 */
} BUTTON_FIFO_T;

/*--- Public variable declarations ----------------------------------------------------*/

/*--- Public function declarations ----------------------------------------------------*/
void Button_Init(void);
void Button_Scan(void);
void Button_FIFO_Put(uint8_t _ButtonCode);

void Button_SetParam(uint8_t _ucButtonID, uint16_t _LongTime, uint8_t _RepeatSpeed);

uint8_t Button_FIFO_Put_Get(void);
uint8_t Button_GetState(BUTTON_ID_T _ucButtonID);

#ifdef __cplusplus
}
#endif

#endif	// __BUTTON_H__
