#include "Users.h"





int main(void)
{
	
	/*��ͷ�ֺ��ж���������*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	/*ȫ���ĳ�ʼ���������*/
	Fullful_Init();
//	DataScope_OutPut_Buffer[0] = '$';
	printf("USART2 begin");
	while(1)
	{
	
		delay_100();
		DataScope();
	}
}

