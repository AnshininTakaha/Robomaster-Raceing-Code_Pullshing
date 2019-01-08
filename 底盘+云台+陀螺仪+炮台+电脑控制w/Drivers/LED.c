/**
  ******************************************************************************
  * @file    LED.c
  * @author  Hare
  * @version V1.0
  * @date
  * @brief   LED��Ӧ�ú����ӿ�
  ******************************************************************************
  */


#include "LED.h"


/**
  * @brief  LED�Ƴ�ʼ��
  * @param  None
  * @retval None
  */


void LED_Init(void)
{
    /*GPIO�ṹ��ʹ��*/
    GPIO_InitTypeDef GPIO_InitStructure;

    /*����GPIOʱ��*/
    /*LED��ɫ -> PE7*/
    /*LED��ɫ -> PF14*/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOF, ENABLE);

    /*���ֶ�Ӧ������*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Low_Speed;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIOE, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_Init(GPIOF, &GPIO_InitStructure);

//	LED_GREEN(1);
    /*�����ƵĿ��أ��óɸߵ�ƽ*/
    GPIO_WriteBit(GPIOE, GPIO_Pin_7, Bit_SET);
    GPIO_WriteBit(GPIOF, GPIO_Pin_14, Bit_SET);
}
