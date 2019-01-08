#include "Users.h"



int main(void)
{
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	PC_MODE_Init();
	
	Laser_Init();
	LED_Init();
	
	USART2_QuickInit(115200);
	GY_IMU_Init();
	CAN1_QuickInit();
	
	DR16_Init();
	
	TIM7_CounterMode(89, 9999);
	delay_ms(2000);
	
	
	
	Chassis_Init();
	Cloud_Init();
	Shoot_Init();
	
	
	TIM6_CounterMode(89, 9999);
	
	while(1)
	{
		
	}
}

