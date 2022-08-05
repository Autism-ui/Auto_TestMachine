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

#ifndef __UNIT_TEST_EXPERIMENT_H__
#define __UNIT_TEST_EXPERIMENT_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*--- Public dependencies -------------------------------------------------------------*/
#include "adc.h"
    /*--- Public macros -------------------------------------------------------------------*/

    /*--- Public type definitions ---------------------------------------------------------*/

    /*--- Public variable declarations ----------------------------------------------------*/

    /*--- Public function declarations ----------------------------------------------------*/

    /* CHANNEL0:PC0
     * CHANNEL1:PC1
     * CHANNEL2:PC2
     * CHANNEL3:PC3
     */
    void bsp_ADC_Update(void);

    float Get_CHANNEL0_ADC(void);
    float Get_CHANNEL1_ADC(void);
    float Get_CHANNEL2_ADC(void);
    float Get_CHANNEL3_ADC(void);

#ifdef __cplusplus
}
#endif

#endif // __UNIT_TEST_EXPERIMENT_H__
