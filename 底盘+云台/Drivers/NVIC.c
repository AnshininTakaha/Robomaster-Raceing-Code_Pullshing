/**
  ******************************************************************************
  * @file    NVIC.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   NVIC中断优先级应用函数接口，为了方便初始化所以弄成一个带参函数
  ******************************************************************************
  */
	
#include "NVIC.h"

/**
  * @brief  NVIC中断优先级配置
  * @param  IRQChannel 	  		中断源，参考"stm32f4xx.h", 196行、（中断服务函数名在.s文件里）
  *			MainPriority		主优先级
  *			SubPriority			抢占式优先级
  * @retval None
  */


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
	
	/*打个比方，如果是使用了这个带参数的函数的话，就可以这样子定义*/
	/*NVIC_Config(CAN1_RX0_IRQn, 1, 1);*/
}
