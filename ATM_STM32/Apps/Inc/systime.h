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

#ifndef __SYSTIME_H__
#define __SYSTIME_H__

#include "stdint.h"
#ifdef __cplusplus
extern "C" {
#endif

uint32_t Get_systime_ms(void);
uint32_t Get_systime_us(void);

#ifdef __cplusplus
}
#endif

#endif	// __SYSTIME_H__
