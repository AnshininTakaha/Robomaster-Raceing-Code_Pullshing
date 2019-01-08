#include "Users.h"





int main(void)
{
	/*Fullfull_Init begin..*/
	/*��ͷ�ֺ��ж���������*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	/*GY_IMU��ʼ��*/
	GY_IMU_Init();
	
	/*CAN1���ܸ������ӵı��ĳ�ʼ��*/
	CAN1_QuickInit();
	
	/*����ϵͳ(����DSPϵͳ��ʼ��)*/
	USART2_QuickInit(115200);
	
	/*ң������ʼ��������USART1�ĳ�ʼ����*/
	DR16_receiverInit();
  /*	JudgeSystem_Init();*/
	
	/*ң�����ĳ�ʼ������˶�ģ�͵ĳ�ʼ���г�ͻ
	���Լ�ǰ��ģ�Ͷ�ȡ�Ĳ�����ֵ��ͺ�����̺���̨�ĳ�ʼ���й�ϵ
	��������Ҫ��ʱ200ms*/
	delay_ms(2000);
	/*�˶�ģ�ͳ�ʼ��*/
	Chassis_Init();
	Cloud_Init();
	
	/*�ճ�ˢ�³�ʼ��*/
	TIM6_CounterMode(89, 9999);

  /*����ϵͳUSART2����*/
	printf("Judgement system USART2 begin");
	/*ȫ��ʹ�����*/
	printf("ALL Begin");
	while(1)
	{
		loop();

	}
}

