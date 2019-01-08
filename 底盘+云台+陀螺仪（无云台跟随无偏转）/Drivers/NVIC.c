/**
  ******************************************************************************
  * @file    NVIC.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   NVIC�ж����ȼ�Ӧ�ú����ӿڣ�Ϊ�˷����ʼ������Ū��һ�����κ���
  ******************************************************************************
  */
	
#include "NVIC.h"

/**
  * @brief  NVIC�ж����ȼ�����
  * @param  IRQChannel 	  		�ж�Դ���ο�"stm32f4xx.h", 196�С����жϷ���������.s�ļ��
  *			MainPriority		�����ȼ�
  *			SubPriority			��ռʽ���ȼ�
  * @retval None
  */


void NVIC_Config(uint16_t IRQChannel, uint16_t MainPriority, uint16_t SubPriority)
{
	/*�жϽṹ��*/
	NVIC_InitTypeDef NVIC_InitStructure;

	/*�ж���Դͨ��������*/
	NVIC_InitStructure.NVIC_IRQChannel = IRQChannel;
	
	/*��Ҫ�����ȼ�*/
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = MainPriority;
	
	/*������ռ�ĵ����ȼ�*/
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;
	
	/*ͨ��ʹ��*/
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	/*NVIC�жϺ�����װ*/
	NVIC_Init(&NVIC_InitStructure);
	
	/*����ȷ��������ʹ��������������ĺ����Ļ����Ϳ��������Ӷ���*/
	/*NVIC_Config(CAN1_RX0_IRQn, 1, 1);*/
}
