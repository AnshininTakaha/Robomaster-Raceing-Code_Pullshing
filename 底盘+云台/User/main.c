#include "Users.h"





int main(void)
{
	
	/*开头分好中断组嘻嘻嘻*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	/*全部的初始化定义代码*/
	Fullful_Init();
//	DataScope_OutPut_Buffer[0] = '$';
	printf("USART2 begin");
	while(1)
	{
	
		delay_100();
		DataScope();
	}
}

