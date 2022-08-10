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

#include "watchdog.h"

#ifdef __cplusplus
extern "C"
{
#endif

#include "iwdg.h"

    /******IWDG******/
    void FeedIndependentWDOG(void)
    {
        BSP_IWDG_Refresh();
    }

#ifdef __cplusplus
}
#endif
