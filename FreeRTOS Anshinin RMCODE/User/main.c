#include "Users.h"

extern float Calulations;
extern int cv_x,cv_y;
int main(void)
{
	/*��ռ0��15���Ƚ�0*/
	/*����ʹ��FreeRTOSϵͳ����ߵ����ȼ�ֻ�ܵ�5�����Է�Χ��5��15*/
	/*Ŀǰ�Ѿ��������ж����ȼ�����������ز�Ҫ�����Ҹģ�*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	/*��������*/
	
	USART2_QuickInit(115200);
	USART2_RXDMA_Config((uint32_t)CV_RXBUFF, 10);
	
	PC_MODE_Init();
	
	Laser_Init();
	LED_Init();
	CAN1_QuickInit();
	DR16_Init();
 
	//IRTOS_Begin();

	/*ϵͳ���ԣ����������ϵͳ���ԵĻ�����Ĵ������ܲ����ģ��������Է��ģ�*/
	
	GY_IMU_Init();
	delay_ms(2000);
	
	Chassis_Init();
	Cloud_Init();
	#if New_RM
	//
	#else
	Shoot_Init();
	#endif

	// delay_ms(2000);
	TIM7_CounterMode(89, 9999);
	TIM6_CounterMode(89, 9999);
	
	while(1)
	{
		
		
//		ANO_Send_Data_V1(RM6623s[1].outCurrent,0,0,0);

	}
}

