#include "Users.h"


extern int cv_x,cv_y;
int main(void)
{
	/*抢占0到15，比较0*/
	/*由于使用FreeRTOS系统，最高的优先级只能到5，所以范围是5到15*/
	/*目前已经更改了中断优先级调整，请务必不要随便的乱改！*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	/*启动自瞄*/
	
	USART2_QuickInit(115200);
	USART2_RXDMA_Config((uint32_t)CV_RXBUFF, 20);
	

	delay_ms(2000);
	
	PC_MODE_Init();
	
	
	Laser_Init();
	LED_Init();
	
	

	//IRTOS_Begin();

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
		//ANO_Send_Data_V1(GPIO_ReadInputDataBits(GPIOE,GPIO_Pin_10),0,0,0);
	}
}

