/**
  ******************************* Copyright *********************************
  *
  *                 (C) Copyright 2018,����,China, GCU.
  *                            All Rights Reserved
  *                              
  *                     By(��������ѧ����ѧԺ������Ұ�Ƕ�)
  *                     https://github.com/GCUWildwolfteam
  *    
  * FileName   : delay.c   
  * Version    : v1.0		
  * Author     : ����			
  * Date       : 2018-10-14         
  * Description: ��ʱ������
  ******************************************************************************
 */

#include "delay.h"




/**
  * @brief  ���뼶��ʱ
  * @param  _ms ��ʱ������
  * @retval None
  */
void delay_ms(u32 _ms)
{
	SysTick_Config(SystemCoreClock/1000);
		for(u32 i = 0; i < _ms; i++){
		while(!((SysTick->CTRL)&(1<<16)));
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

/**
  * @brief  ΢�뼶��ʱ
  * @param  _us ��ʱ΢����
  * @retval None
  */
void delay_us(u32 _us)
{
	SysTick_Config(SystemCoreClock/1000000);
	for(u32 i = 0; i < _us; i++){
		while(!((SysTick->CTRL)&(1<<16)));
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}


