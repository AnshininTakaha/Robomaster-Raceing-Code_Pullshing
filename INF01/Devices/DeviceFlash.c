#include "DeviceFlash.h"

void DeviceFlash_Process(void)
{
	/*Ò£¿ØÆ÷*/
	if(DR16.UpdateFrame < 5)
	{
		DR16.OFFLINE_SET = 1;
	}
	else
	{
		DR16.OFFLINE_SET = 0;
	}
	DR16.UpdateFrame = 0;
	
	
	/*µ×ÅÌ*/
	for(int i =0;i<4;i++)
	{
		if(RM3508s[i].UpdateFrame < 5)
		{
			RM3508s[i].OFFLINE_SET = 1;
		}
		else
		{
			RM3508s[i].OFFLINE_SET = 0;
		}
		RM3508s[i].UpdateFrame = 0;
	}
	
	
}