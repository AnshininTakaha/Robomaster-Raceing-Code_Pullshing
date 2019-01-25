#include "Devices_Flash.h"

void DevicesFlash(void)
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
	
	/*ÔÆÌ¨*/
	for(int j = 0;j<2;j++)
	{
		if(RM6623s[j].UpdateFrame < 5)
		{
			RM6623s[j].OFFLINE_SET = 1;
		}
		else
		{
			RM6623s[j].OFFLINE_SET = 0;
		}
		RM6623s[j].UpdateFrame = 0;
	}

	/*²¦µ¯µç»ú*/	
	for(int k = 0;k < 1;k++)
	{
		if(RM2006s[k].UpdateFrame < 5)
		{
			RM2006s[k].OFFLINE_SET = 1;
		}
		else
		{
			RM2006s[k].OFFLINE_SET = 0;
		}
		RM2006s[k].UpdateFrame =0;
	}

	/*ÍÓÂÝÒÇ*/
	if(Cloud_IMU.UpdateFrame < 5)
	{
		Cloud_IMU.OFFLINE_SET = 1;
	}
	else
	{
		Cloud_IMU.OFFLINE_SET = 0;
	}
	Cloud_IMU.UpdateFrame = 0;
}







