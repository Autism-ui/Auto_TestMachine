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

#include "button.h"

#ifdef __cplusplus
extern "C" {
#endif

/*--- Private dependencies ------------------------------------------------------------*/
#include "string.h"
#include "stdio.h"
#include "stdlib.h"
#include "gpio.h"
/*--- Public variable definitions -----------------------------------------------------*/

/*--- Private macros ------------------------------------------------------------------*/
#define Hard_Button_Num 1 /* Button个数 */
/*--- Private type definitions --------------------------------------------------------*/

/*--- Private variable definitions ----------------------------------------------------*/
BUTTON_T		 Button_Msg[Hard_Button_Num] = { 0 };
BUTTON_FIFO_T Button_FIFO;

/*--- Private function declarations ---------------------------------------------------*/
static void	   Button_FIFO_Init(void);
static uint8_t IsButtonDown(void);
static void	   Button_Detect(uint8_t i);
/*--- Private function definitions ----------------------------------------------------*/
static void Button_FIFO_Init(void) {
	// 对按键FIFO读写指针清零
	Button_FIFO.Read  = 0;
	Button_FIFO.Write = 0;

	/* 给按键结构体成员变量赋缺省值 */
	for(int i = 0; i < Hard_Button_Num; i++) {
		Button_Msg[i].LongTime = Button_Long_Time;	// 长按时间0表示不检测长按键事件
		Button_Msg[i].Count	   = Button_Filter_Time / 2;  // 计数器设置为滤波时间的一半
		Button_Msg[i].State	   = BUTTON_NONE;			  // 按键缺省状态,0为未按下
		Button_Msg[i].RepeatSpeed = 0;	// 按键连发的速度,0表示不支持连发
		Button_Msg[i].RepeatCount = 0;	// 连发计数器
	}
	// 判断按键是否被按下
	Button_Msg[0].IsButtonDownFunc = IsButtonDown;
}

static uint8_t IsButtonDown(void) {
	if(HAL_GPIO_ReadPin(Button_GPIO_Port, Button_Pin) == GPIO_PIN_SET)
		return 1;
	else
		return 0;
}

/**
 * @brief      检测一个按键,非阻塞状态,周期调用
 * @param[in]  i:IO的id,从0开始编码
 * @retval     无
 */
static void Button_Detect(uint8_t i) {
	BUTTON_T *pBtn;
	pBtn = &Button_Msg[i];	// 读取相应按键的结构体地址
	if(pBtn->IsButtonDownFunc()) {
		/* 按键处理 */
		if(pBtn->Count < Button_Filter_Time) {	// 按键滤波前给Count设置一个初值
			pBtn->Count = Button_Filter_Time;
		} else if(pBtn->Count < 2 * Button_Filter_Time) {  // 实现Filter_Time时间长度的延迟
			pBtn->Count++;
		} else {
			if(pBtn->State == 0) {
				pBtn->State = 1;  // 如果按键按下了,这里就将其设置为1
								  // 发送按钮按下的消息
				Button_FIFO_Put((uint8_t)(3 * i + 1));
			}

			if(pBtn->LongTime > 0) {  // LongTime初始值是100,单位是10ms,持续1s,就认为是长按事件
				if(pBtn->LongCount < pBtn->LongTime) {
					// 发送按钮持续按下的消息
					if(++pBtn->LongCount
					   == pBtn->LongTime) {	 // LongCount等于LongTime(100),10ms进入一次,进入了100次也就是说按下事件大于1s
						// 键值放入按键FIFO
						Button_FIFO_Put((uint8_t)(3 * i + 3));
					}
				} else {  // LongCount大于LongTime(100),也就是说按下事件大于1s
					if(pBtn->RepeatSpeed > 0) {	 // RepeatSpeed连续按键周期
						if(++pBtn->RepeatCount >= pBtn->RepeatSpeed) {
							pBtn->RepeatCount = 0;
							// 长按键后,每隔10ms发送1个按键,因为长按也是要发送键值的,10ms发送1次
							Button_FIFO_Put((uint8_t)(3 * i + 1));
						}
					}
				}
			}
		}
	} else {
		// 执行的是按键松手的处理或者按键没有按下的处理
		if(pBtn->Count > Button_Filter_Time) {
			pBtn->Count = Button_Filter_Time;
		} else if(pBtn->Count != 0) {
			pBtn->Count--;
		} else {
			if(pBtn->State == 1) {
				pBtn->State = 0;
				// 发送按钮弹起的消息
				Button_FIFO_Put((uint8_t)(3 * i + 2));
			}
		}
		pBtn->LongCount	  = 0;
		pBtn->RepeatCount = 0;
	}
}

/*--- Public function definitions -----------------------------------------------------*/

void Button_Init(void) {
	Button_FIFO_Init();
}

/**
 * @brief      将1个键值压入按键FIFO缓冲区,可用于模拟一个按键
 * @param[in]  _ButtonCode:按键代码
 * @retval     无
 */
void Button_FIFO_Put(uint8_t _ButtonCode) {
	Button_FIFO.Buf[Button_FIFO.Write] = _ButtonCode;
	if(++Button_FIFO.Write >= Button_FIFO_Size) {
		Button_FIFO.Write = 0;
	}
}

/**
 * @brief      从按键FIFO缓冲区读取一个键值
 * @param[in]  无
 * @retval     按键代码
 */
uint8_t Button_FIFO_Put_Get(void) {
	uint8_t ret;
	if(Button_FIFO.Read == Button_FIFO.Write) {
		return BUTTON_NONE;
	} else {
		ret = Button_FIFO.Buf[Button_FIFO.Read];
		if(++Button_FIFO.Read >= Button_FIFO_Size) {
			Button_FIFO.Read = 0;
		}
		return ret;
	}
}

/**
 * @brief      读取按键的状态
 * @param[in]  _ucButtonID:按键ID,从0开始
 * @retval     1 表示按下,0 表示未按下
 */
uint8_t Button_GetState(BUTTON_ID_T _ucButtonID) {
	return Button_Msg[_ucButtonID].State;
}

/**
 * @brief      设置按键参数
 * @param[in]  _ucKeyID:按键ID,从0开始
 * @param[in]  _LongTime:长按事件时间
 * @param[in]  _RepeatSpeed:连发速度
 * @retval     1 表示按下,0 表示未按下
 */
void Button_SetParam(uint8_t _ucButtonID, uint16_t _LongTime, uint8_t _RepeatSpeed) {
	Button_Msg[_ucButtonID].LongTime = _LongTime; /* 长按时间0表示不检测长按键事件 */
	Button_Msg[_ucButtonID].RepeatSpeed = _RepeatSpeed; /* 按键连发的速度,0表示不支持连发 */
	Button_Msg[_ucButtonID].RepeatCount = 0;			/* 连发计数器 */
}

/**
 * @brief      清空按键FIFO缓冲区
 * @param[in]  无
 * @retval     无
 */
void Button_FIFO_Clear(void) {
	Button_FIFO.Read = Button_FIFO.Write;
}

/**
 * @brief      扫描所有按键,非阻塞,被状态机任务周期性调用,10ms一次
 * @param[in]  无
 * @retval     无
 */
void Button_Scan(void) {
	for(int i = 0; i < Hard_Button_Num; i++) {
		Button_Detect(i);
	}
}
#ifdef __cplusplus
}
#endif
