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
#include "gpio.h"
#include <assert.h>
#include "bsp_flash.h"
#include "bsp_spi.h"
/*--- Public variable definitions -----------------------------------------------------*/

/*--- Private macros ------------------------------------------------------------------*/
#define HAL_LIB     (1)
#define STANDER_LIB (0)

#define ACTIVE   (GPIO_PIN_RESET)
#define INACTIVE (GPIO_PIN_SET)

#define SPI_TIMEOUT_US	 (1000)							//最长通信等待时间
#define GET_SYSTEME_US() get_time_ms()				//获取开机以来系统的时间

#define CS_FLASH(x) HAL_GPIO_WritePin(SPI1_CS_FLASH_GPIO_Port,SPI1_CS_FLASH_Pin,x)
#define CS_LCD(x)		HAL_GPIO_WritePin(SPI2_CS_LCD_GPIO_Port,SPI2_CS_LCD_Pin,x)

/*--- Private function declarations --------------------------------------------------------*/
static void bsp_spi_set_gpio(spi_sel_t_e sel,GPIO_PinState op);

void spi_set_cs(SPI_Device *p_Dev,GPIO_PinState op);

SPI_Device* get_spi_handle(spi_sel_t_e sel);

//static bool __BSP_SPI_GET_FLAG(struct spi_Device_t *p_Dev,uint8_t send_state);

spi_err_type_e set_spi_err_state(spi_err_type_e type);
spi_send_state_e set_spi_send_state(spi_send_state_e state);
/*--- Private variable definitions ----------------------------------------------------*/
SPI_Device SPI[]={
    /* /hspi /spi_id /cs_status/send_state /bsp_spi_set_cs */
    {&hspi1, SPI_SEL_Flash, 0, 0, 0,spi_set_cs},		//FLASH or other 
    {&hspi2, SPI_SEL_LCD, 0, 0, 0,spi_set_cs},		//LCD

};

spi_err_type_e spi_state_err;
spi_send_state_e spi_send_state;
/*--- Private type definitions ---------------------------------------------------*/

/*--- Private function definitions ----------------------------------------------------*/
spi_err_type_e set_spi_err_state(spi_err_type_e type){

    spi_err_type_e err = type;
    
    return err;
}

spi_send_state_e set_spi_send_state(spi_send_state_e state){

    spi_send_state_e ret = state;

    return ret;

}

/*--- Public function definitions -----------------------------------------------------*/

/* ---------------- Private func ---------------- */
static void bsp_spi_set_gpio(spi_sel_t_e sel,GPIO_PinState op)
{
    
    switch(sel){

#if defined(HAL_LIB)
    case SPI_SEL_Flash:
        CS_FLASH(op);
        break;
    
    case SPI_SEL_LCD:
        CS_LCD(op);
        break;
    
    default:
        CS_FLASH(GPIO_PIN_SET);
        CS_LCD(GPIO_PIN_SET);
        break;

#elif STANDER_LIB

#endif	/* LIB_TYPE */

    }

}

/* cs setting func */
void spi_set_cs(SPI_Device *p_Dev,GPIO_PinState op){
	
		spi_sel_t_e sel = p_Dev->spi_id;	
    bsp_spi_set_gpio(sel,op);   //设置GPIO的函数
}




SPI_Device* get_spi_handle(spi_sel_t_e sel){

    return &SPI[sel-1];                       //根据id返回相应的设备对象
}

//static bool __BSP_SPI_GET_FLAG(struct spi_Device_t *p_Dev,uint8_t send_state){

//	bool state = 0;
//#if defined(HAL_LIB)
//    if(send_state == SPI_SEND){
//        state = __HAL_SPI_GET_FLAG(p_Dev->spix,SPI_FLAG_TXE);
//    }else if(send_state == SPI_RECEIVE){
//        state = __HAL_SPI_GET_FLAG(p_Dev->spix,SPI_FLAG_RXNE);
//    }

//#elif STANDER_LIB

//    if(send_state == SPI_SEND){
//         state = SPI_I2S_GetFlagStatus(p_Dev->spix->Instance, SPI_I2S_FLAG_TXE);
//    }else if(send_state == SPI_RECEIVE){
//         state = SPI_I2S_GetFlagStatus(p_Dev->spix->Instance, SPI_I2S_FLAG_RXE);
//    }

//#endif
//    return state;
//}

/* ----------------------- Public API ----------------------- */

HAL_StatusTypeDef haha;

//spi_err bsp_spi_init(void){
//	
//	for(uint8_t idx = 1;idx <= SPI_NUM ; ++idx){
//		SPI[idx].spi_id = idx;
//	}

//    return (spi_state_err = set_spi_err_state(SPI_ERR_NONE));
//	
//}

spi_err bsp_spi_write(spi_sel_t_e sel,uint8_t* pTxData,uint16_t Size){

    SPI_Device *spi;
    
    spi = get_spi_handle(sel); 
	
    spi->spi_set_cs(spi,ACTIVE);

#if defined(HAL_LIB)
	
    HAL_StatusTypeDef state;

    state = HAL_SPI_Transmit(spi->spix,pTxData,Size,SPI_TIMEOUT_US);
	

    if(state != HAL_OK){
        spi_state_err = set_spi_err_state(SPI_ERR_TRANSMIT);
        goto T_ERR;
    }else{
        spi_state_err = set_spi_err_state(SPI_ERR_NONE);
    }
		

#elif STANDER_LIB
    //... 标准库
    SPI_I2S_SendData(p_Dev->spix->Instance,*(tx));

#endif  /* LIB_TYPE */

    spi->spi_set_cs(spi,INACTIVE);
		
    return SPI_ERR_NONE;

		T_ERR:
		/* error process 
		 *	... add func
		 */
    printf("Transmit fail");
		return spi_state_err;

}



spi_err bsp_spi_read(spi_sel_t_e sel,uint8_t *pRxData,uint16_t Size){

    SPI_Device *spi;
    
    spi = get_spi_handle(sel); 

    spi->spi_set_cs(spi,ACTIVE);


#if defined(HAL_LIB)

   HAL_StatusTypeDef state;

   state = HAL_SPI_Receive(spi->spix,pRxData,Size,SPI_TIMEOUT_US); //接收
	
	
   if(state != HAL_OK){
        spi_state_err = set_spi_err_state(SPI_ERR_RECEIVE);
		goto R_ERR;

   }else{
        spi_state_err = set_spi_err_state(SPI_ERR_NONE);

   }


#elif STANDER_LIB

#endif      /* LIB_TYPE */

    spi->spi_set_cs(spi,INACTIVE);

    return spi_state_err;

	 R_ERR:
		/* error process 
		 *	... add func
		 */
	 printf("spi Recive Error");
	 return  spi_state_err;
	 
}

spi_err bsp_spi_write_read(spi_sel_t_e sel,uint8_t* pTxData,uint8_t *pRxData,uint16_t Size){

    SPI_Device *spi;
    
    spi = get_spi_handle(sel); 

    spi->spi_set_cs(spi,ACTIVE);


    #if defined(HAL_LIB)

        HAL_StatusTypeDef state;

        state = HAL_SPI_TransmitReceive(spi->spix,pTxData,pRxData,Size,SPI_TIMEOUT_US); //接收

        if(state != HAL_OK){
            spi_state_err = set_spi_err_state(SPI_ERR_RECEIVE);
		    goto R_ERR;

        }else{
            spi_state_err = set_spi_err_state(SPI_ERR_NONE);

        }

    #endif      /* LIB_TYPE */

    spi->spi_set_cs(spi,INACTIVE);

    return spi_state_err;

	 R_ERR:
		/* error process 
		 *	... add func
		 */
	 printf("spi Transmit and Recive Error");
	 return  spi_state_err;
}

/*
 返回值大于0说明发送或接收错误
*/
//连续发送多个字节，并且连续接收多个字节
spi_err bsp_spi_Transfer(spi_sel_t_e sel,uint8_t* pTxData,uint8_t *pRxData,uint16_t tSize,uint16_t rSize){

	  SPI_Device *spi;
    
    spi = get_spi_handle(sel); 

    spi->spi_set_cs(spi,ACTIVE);
	
	  #if defined(HAL_LIB)
		
		HAL_StatusTypeDef state_tx;
		HAL_StatusTypeDef state_rx;
	
		//连续发送
		while(tSize--){
			state_tx = HAL_SPI_Transmit(spi->spix,pTxData,tSize,SPI_TIMEOUT_US);
			
			//haha = state_tx;
			
			if(state_tx != HAL_OK){
				spi_state_err = set_spi_err_state(SPI_ERR_TRANSMIT);		//Transmit maybe error,but it can also beuse for flash get id.
				//goto T_ERR;
			}else{
				spi_state_err = set_spi_err_state(SPI_ERR_NONE);
			}
		}
		
			state_rx = HAL_SPI_Receive(spi->spix,pRxData,rSize,SPI_TIMEOUT_US);
			if(state_rx != HAL_OK){
				spi_state_err = set_spi_err_state(SPI_ERR_RECEIVE);
				goto R_ERR;
			}else{
				spi_state_err = set_spi_err_state(SPI_ERR_NONE);
			}
			
		#endif /* LIB_TYPE */
		
		spi->spi_set_cs(spi,INACTIVE);
		
			return spi_state_err;
			
//			T_ERR:
//			printf("Transmit Error!!!");
//			return spi_state_err;
			
			
			R_ERR:
			printf("Transmit Error!!!");
			return spi_state_err;
}



/* ------------------------------------- NO CS ------------------------------------- */
/**
 * @brief  发现很多设备都不希望我们自行拉低cs，因为在拉低CS的时候后面可能会想要跟上一些东西，调用这些函数需要自行拉低拉高CS
 * @note   
 */

spi_err bsp_spi_write_NO_CS(spi_sel_t_e sel,uint8_t* pTxData,uint16_t Size){

    SPI_Device *spi;
    
    spi = get_spi_handle(sel); 
	

#if defined(HAL_LIB)
	
    HAL_StatusTypeDef state;

    state = HAL_SPI_Transmit(spi->spix,pTxData,Size,SPI_TIMEOUT_US);
	

    if(state != HAL_OK){
        spi_state_err = set_spi_err_state(SPI_ERR_TRANSMIT);
        goto T_ERR;
    }else{
        spi_state_err = set_spi_err_state(SPI_ERR_NONE);
    }
		

#elif STANDER_LIB
    //... 标准库
    SPI_I2S_SendData(p_Dev->spix->Instance,*(tx));

#endif  /* LIB_TYPE */

		
    return SPI_ERR_NONE;

		T_ERR:
		/* error process 
		 *	... add func
		 */
    printf("Transmit fail");
		return spi_state_err;

}



spi_err bsp_spi_read_NO_CS(spi_sel_t_e sel,uint8_t *pRxData,uint16_t Size){

    SPI_Device *spi;
    
    spi = get_spi_handle(sel); 


#if defined(HAL_LIB)

   HAL_StatusTypeDef state;

   state = HAL_SPI_Receive(spi->spix,pRxData,Size,SPI_TIMEOUT_US); //接收
	
	
   if(state != HAL_OK){
        spi_state_err = set_spi_err_state(SPI_ERR_RECEIVE);
		goto R_ERR;

   }else{
        spi_state_err = set_spi_err_state(SPI_ERR_NONE);

   }


#elif STANDER_LIB

#endif      /* LIB_TYPE */

    return spi_state_err;

	 R_ERR:
		/* error process 
		 *	... add func
		 */
	 printf("spi Recive Error");
	 return  spi_state_err;
	 
}

spi_err bsp_spi_write_read_NO_CS(spi_sel_t_e sel,uint8_t* pTxData,uint8_t *pRxData,uint16_t Size){

    SPI_Device *spi;
    
    spi = get_spi_handle(sel); 


    #if defined(HAL_LIB)

        HAL_StatusTypeDef state;

        state = HAL_SPI_TransmitReceive(spi->spix,pTxData,pRxData,Size,SPI_TIMEOUT_US); //接收

        if(state != HAL_OK){
            spi_state_err = set_spi_err_state(SPI_ERR_RECEIVE);
		    goto R_ERR;

        }else{
            spi_state_err = set_spi_err_state(SPI_ERR_NONE);

        }

    #endif      /* LIB_TYPE */


    return spi_state_err;

	 R_ERR:
		/* error process 
		 *	... add func
		 */
	 printf("spi Transmit and Recive Error");
	 return  spi_state_err;


}




#ifdef __cplusplus
}
#endif
