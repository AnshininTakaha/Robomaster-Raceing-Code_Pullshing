/**
  ******************************* Copyright *********************************
  *
  *                 (C) Copyright 2018,����,China, GCU.
  *                            All Rights Reserved
  *
  *                     By(��������ѧ����ѧԺ������Ұ�Ƕ�)
  *                     https://github.com/GCUWildwolfteam
  *
  * FileName   : main.c
  * Version    : v1.0
  * Author     : ����
  * Date       : 2018-10-14
  * Description: ����������
  ******************************************************************************
 */

#include "Users.h"

int main(void)
{
    /*Fullfull_Init begin..*/
    /*��ͷ�ֺ��ж���������*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    Begin();

    /*����ϵͳUSART2����*/
    printf("Judgement system USART2 begin\r\n");
    /*ȫ��ʹ�����*/
    printf("ALL Begin\r\n");
    while(1)
    {
        loop();

    }
}

