/**
  ******************************* Copyright *********************************
  *
  *                 (C) Copyright 2018,口无,China, GCU.
  *                            All Rights Reserved
  *
  *                     By(华南理工大学广州学院机器人野狼队)
  *                     https://github.com/GCUWildwolfteam
  *
  * FileName   : Users.c
  * Version    : v1.0
  * Author     : 口无
  * Date       : 2018-10-14
  * Description: 执行函数
  ******************************************************************************
 */

#include "Users.h"

int Classical_ban = 0;
int Cloud_and_shooting_ban = 0;

void Begin(void)
{

    LED_Init();
//		printf("LED Begin\n");

    KEY_Init();
//		printf("KEY Begin\n");

    USART2_QuickInit(115200);
    GY_IMU_Init();
//		printf("GYIMU Begin\n");

    CAN1_QuickInit();
//		printf("CAN1 Begin\n");

    DR16_receiverInit();
//		printf("DR16 Begin\n");
    /*	JudgeSystem_Init();*/

    TIM7_CounterMode(89, 9999);
//		printf("TIM7 Begin\n");
    delay_ms(2000);


    Chassis_Init();
    Cloud_Init();

//		printf("Model Begin\n");

    TIM6_CounterMode(89, 9999);
//		printf("TIM6 Begin\n");
    printf("ALL Begin\n");
		
		delay_ms(2000);
		ControlMode_paramInit();
}

void delay_100(void)
{
    int i = 0;

    while(i<1000000)//1000ms
    {
        i++;
    }

}

void loop()
{
#if !Judgement_funtion_ON
    delay_ms(1000);
//    printf("ALL Begin\n");
//		printf("M3508s[1].offLineFlag = %d\n",M3508s[1].offLineFlag);
//    DataScope();
#endif


}

