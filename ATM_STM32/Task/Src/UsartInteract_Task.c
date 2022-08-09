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

#include "UsartInteract_Task.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /*--- Private dependencies ------------------------------------------------------------*/
#include "bsp_usart.h"
    /*--- Public variable definitions -----------------------------------------------------*/
    uint8_t data[BUFF_LEN];
    /*--- Private macros ------------------------------------------------------------------*/

    /*--- Private type definitions --------------------------------------------------------*/

    /*--- Private variable definitions ----------------------------------------------------*/
    static TaskHandle_t UsartInteractTaskHandle;
    /*--- Private function declarations ---------------------------------------------------*/

    /*--- Private function definitions ----------------------------------------------------*/

    /*--- Public function definitions -----------------------------------------------------*/
    void UsartInteractTask(void *param)
    {
        portBASE_TYPE xStatus = pdFALSE;
        Queue_Receive = xQueueCreate(3, sizeof(data));
        for (;;)
        {
            xStatus = xQueueReceive(Queue_Receive, &data, portMAX_DELAY);
            if (xStatus == pdTRUE)
            {
                HAL_UART_Transmit(&huart3, "Successful\r\n", sizeof("Successful\r\n"), 100);
            }
        }
    }
    void UsartInteract_TaskCreate(osPriority_t _priority)
    {
        BaseType_t ret;
        ret = xTaskCreate(UsartInteractTask, "UsartInteract", 512, NULL, _priority, &UsartInteractTaskHandle);
        if (ret != pdTRUE)
        {
        }
    }
#ifdef __cplusplus
}
#endif
