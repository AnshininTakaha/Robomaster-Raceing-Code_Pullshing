/**
  ******************************************************************************
  * @file    LED.c
  * @author  Hare
  * @version V1.0
  * @date
  * @brief   LED灯应用函数接口
  ******************************************************************************
  */


#include "LED.h"


/**
  * @brief  LED灯初始化
  * @param  None
  * @retval None
  */


void LED_Init(void)
{
    /*GPIO结构体使能*/
    GPIO_InitTypeDef GPIO_InitStructure;

    /*开启GPIO时钟*/
    /*LED绿色 -> PE7*/
    /*LED红色 -> PF14*/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOF, ENABLE);

    /*各种对应的设置*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Low_Speed;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_Init(GPIOF, &GPIO_InitStructure);

//	LED_GREEN(1);
    /*开启灯的开关，置成高电平*/
    GPIO_WriteBit(GPIOE, GPIO_Pin_7, Bit_SET);
    GPIO_WriteBit(GPIOF, GPIO_Pin_14, Bit_SET);
}
