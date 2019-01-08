#include "Users.h"


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
	#if !Judgement_funtion_ON
	delay_ms(1000);
	DataScope();
	#endif
	
	
}