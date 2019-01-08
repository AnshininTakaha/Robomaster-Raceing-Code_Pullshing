#include "Devices_refresh.h"



/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    Devices_Rush
  * @brief   帧率刷新
  * @param   无 
  * @author  口无 
  * @Data    2018-10-19
 **/
/* -------------------------------- end -------------------------------- */

void Devices_Rush(void)
{
			
	/*云台IMU*/
	if(Cloud_IMU.infoUpdateFrame < 5)
	{
		Cloud_IMU.offLineFlag = 1;
//		printf("Cloud_IMU.offLineFlag = %d\n",Cloud_IMU.offLineFlag);
	}
	else
	{
		Cloud_IMU.offLineFlag = 0;
//		printf("Cloud_IMU.offLineFlag = %d\n",Cloud_IMU.offLineFlag);
	}
	Cloud_IMU.infoUpdateFrame = 0;
	
	/*云台*/
	for(int i = 0; i<2; i++)
	{
		if(M6623s[i].infoUpdateFrame < 5)
			{
				M6623s[i].offLineFlag = 1;
			}
		else
			{
				M6623s[i].offLineFlag = 0;
			}
		M6623s[i].infoUpdateFrame = 0;
//		printf("infoUpdateFrame = %d\n",M6623s[i].infoUpdateFrame);
	}
	
	
	
	/*底盘*/
	for(int i= 0;i < 4; i++)
	{
		if(M3508s[i].infoUpdateFrame < 5)
			{
				M3508s[i].offLineFlag = 1;
				
			}
		else
			{
				M3508s[i].offLineFlag = 0;
			}
		
		M3508s[i].infoUpdateFrame = 0;
	}
//	printf("M3508s[1].offLineFlag = %d\n",M3508s[1].offLineFlag);
	
	

	
//	
	/*拨弹电机*/
	if(M2006s[0].infoUpdateFrame < 5)
		{
			M2006s[0].offLineFlag = 1;
		}
	else
		{
			M2006s[0].offLineFlag =0;
		}
		
		M2006s[0].infoUpdateFrame = 0;
		
		

	/*遥控器*/
	if(dr16_data.infoUpdateFrame < 5)
	{
		dr16_data.offLineFlag = 1;
		
	}
	else
	{
		dr16_data.offLineFlag = 0;
	}
	dr16_data.infoUpdateFrame = 0;
	
	
	
	
}
