#include "Users.h"





int main(void)
{
	/*Fullfull_Init begin..*/
	/*开头分好中断组嘻嘻嘻*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	/*GY_IMU初始化*/
	GY_IMU_Init();
	
	/*CAN1接受各个轮子的报文初始化*/
	CAN1_QuickInit();
	
	/*裁判系统(或者DSP系统初始化)*/
	USART2_QuickInit(115200);
	
	/*遥控器初始化（包含USART1的初始化）*/
	DR16_receiverInit();
  /*	JudgeSystem_Init();*/
	
	/*遥控器的初始化会和运动模型的初始化有冲突
	，以及前面模型读取的部分数值会和后面底盘和云台的初始化有关系
	所以这里要延时200ms*/
	delay_ms(2000);
	/*运动模型初始化*/
	Chassis_Init();
	Cloud_Init();
	
	/*日常刷新初始化*/
	TIM6_CounterMode(89, 9999);

  /*裁判系统USART2开启*/
	printf("Judgement system USART2 begin");
	/*全部使能完成*/
	printf("ALL Begin");
	while(1)
	{
		loop();

	}
}

