#include "Users.h"

void Fullful_Init(void)
{
	/*CAN1���ܸ������ӵı��ĳ�ʼ��*/
	CAN1_QuickInit();
	
	/*����ϵͳ(����DSPϵͳ��ʼ��)*/
	USART2_QuickInit(115200);
	
	
	
	/*ң������ʼ��������USART1�ĳ�ʼ����*/
	DR16_receiverInit();
  /*	JudgeSystem_Init();*/
	
	
	
	/*���̳�ʼ��*/
	Chassis_Init();
	
	/*��̨��ʼ��*/
	Cloud_Init();
	
	
	
	/*�ճ�ˢ�³�ʼ��*/
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