#include "NVIC.h"


/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    NVIC_Config
  * @brief   中断设置
  * @param   IRQChannel: 通道
**					 MainPriority: 抢占优先级
**			 	   SubPriority: 比较优先级
  * @author  口无 
  * @Data    2018-10-26
 **/
/* -------------------------------- end -------------------------------- */

void NVIC_Config(uint16_t IRQChannel, uint16_t MainPriority, uint16_t SubPriority)
{
    /*中断结构体*/
    NVIC_InitTypeDef NVIC_InitStructure;

    /*中断来源通道的设置*/
    NVIC_InitStructure.NVIC_IRQChannel = IRQChannel;

    /*主要的优先级*/
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = MainPriority;

    /*设置抢占的的优先级*/
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;

    /*通道使能*/
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    /*NVIC中断函数封装*/
    NVIC_Init(&NVIC_InitStructure);
}
