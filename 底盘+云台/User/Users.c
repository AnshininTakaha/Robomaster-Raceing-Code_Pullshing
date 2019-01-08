#include "Users.h"

void Fullful_Init(void)
{
	/*CAN1接受各个轮子的报文初始化*/
	CAN1_QuickInit();
	
	/*裁判系统(或者DSP系统初始化)*/
	USART2_QuickInit(115200);
	
	
	
	/*遥控器初始化（包含USART1的初始化）*/
	DR16_receiverInit();
  /*	JudgeSystem_Init();*/
	
	
	
	/*底盘初始化*/
	Chassis_Init();
	
	/*云台初始化*/
	Cloud_Init();
	
	
	
	/*日常刷新初始化*/
	TIM6_CounterMode(89, 9999);
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
	
}