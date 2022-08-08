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

#include "adc_collect.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /*--- Private dependencies ------------------------------------------------------------*/
#include "bsp_adcdetect.h"
    /*--- Public variable definitions -----------------------------------------------------*/

    /*--- Private macros ------------------------------------------------------------------*/

    /*--- Private type definitions --------------------------------------------------------*/
    typedef enum
    {
        FALSE,
        TRUE,
        NONE,
    } ADC_DETECT_STU;

    typedef struct
    {
        ADC_DETECT_STU ADC_DETECT[ADC_CHANNEL_NUM];
    } ADC_COLLECT_t;

    /*--- Private variable definitions ----------------------------------------------------*/
    ADC_COLLECT_t ADC_COLLECT;
    /*--- Private function declarations ---------------------------------------------------*/

    /*--- Private function definitions ----------------------------------------------------*/
    static ADC_DETECT_STU Judge_ADC_CHANNEL(CHANNEL_STU CHANNEL, float Current_V, float CHANNEL_ADC_MIN, float CHANNEL_ADC_MAX)
    {
        if (Current_V > CHANNEL_ADC_MIN && Current_V < CHANNEL_ADC_MAX)
        {
            ADC_COLLECT.ADC_DETECT[CHANNEL] = TRUE;
        }
        else
        {
            ADC_COLLECT.ADC_DETECT[CHANNEL] = FALSE;
        }
        return ADC_COLLECT.ADC_DETECT[CHANNEL];
    }
    /*--- Public function definitions -----------------------------------------------------*/

    void ADC_Detect()
    {
        Judge_ADC_CHANNEL(CHANNEL0, Get_CHANNEL0_ADC(), CHANNEL0_MIN, CHANNEL0_MAX);
        Judge_ADC_CHANNEL(CHANNEL1, Get_CHANNEL1_ADC(), CHANNEL1_MIN, CHANNEL1_MAX);
        Judge_ADC_CHANNEL(CHANNEL2, Get_CHANNEL2_ADC(), CHANNEL2_MIN, CHANNEL2_MAX);
        Judge_ADC_CHANNEL(CHANNEL3, Get_CHANNEL3_ADC(), CHANNEL3_MIN, CHANNEL3_MAX);
    }

#ifdef __cplusplus
}
#endif
