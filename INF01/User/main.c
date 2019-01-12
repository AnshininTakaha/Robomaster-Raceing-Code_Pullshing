#include "Users.h"



int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	LED_Init();
	
	CAN1_QuickInit();
	
	
	DR16_Init();
	
	TIM7_CounterMode(89, 9999);
	delay_ms(2000);
	
	Chassis_Init();
	
	TIM6_CounterMode(89, 9999);
	while(1)
	{
		
	}
}

