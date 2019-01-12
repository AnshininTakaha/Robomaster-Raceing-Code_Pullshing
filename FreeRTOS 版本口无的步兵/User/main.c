#include "Users.h"


extern int cv_x,cv_y;
int main(void)
{
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	/*启动自瞄*/
	USART2_QuickInit(115200);
	//USART2_RXDMA_Config((uint32_t)CV_RXBUFF, 20);
	
	delay_ms(2000);
	
	PC_MODE_Init();
	
	
	Laser_Init();
	LED_Init();
	
	
	
//	IRTOS_Begin();
	/*系统测试（如果启动了系统测试的话下面的代码是跑不到的，这个大可以放心）*/
	
	GY_IMU_Init();
	CAN1_QuickInit();
	
	DR16_Init();
	
	TIM7_CounterMode(89, 9999);
	delay_ms(2000);
	
	
	
	Chassis_Init();
	Cloud_Init();
	#if New_RM
	//
	#else
	Shoot_Init();
	#endif
	
	
	TIM6_CounterMode(89, 9999);
	
	while(1)
	{

	}
}

