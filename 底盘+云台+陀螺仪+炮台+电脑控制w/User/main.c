/**
  ******************************* Copyright *********************************
  *
  *                 (C) Copyright 2018,口无,China, GCU.
  *                            All Rights Reserved
  *
  *                     By(华南理工大学广州学院机器人野狼队)
  *                     https://github.com/GCUWildwolfteam
  *
  * FileName   : main.c
  * Version    : v1.0
  * Author     : 口无
  * Date       : 2018-10-14
  * Description: 主启动函数
  ******************************************************************************
 */

#include "Users.h"

int main(void)
{
    /*Fullfull_Init begin..*/
    /*开头分好中断组嘻嘻嘻*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    Begin();

    /*裁判系统USART2开启*/
    printf("Judgement system USART2 begin\r\n");
    /*全部使能完成*/
    printf("ALL Begin\r\n");
    while(1)
    {
        loop();

    }
}

