#include "GY_IMU.h"

/*定义一个云台陀螺仪储存的结构体*/
uint8_t Cloud_GY_IMU_RXBUFF[30];

GY_IMU_t Cloud_IMU;
/*方便观察*/


/**
  * @brief  GY_IMU串口初始化(包含USART3和USART3DMA的初始化定义)
  * @param  None
  * @retval None
  */
void GY_IMU_Init(void)
{
	USART3_QuickInit(115200);
	USART3_RXDMA_Config((uint32_t)Cloud_GY_IMU_RXBUFF, 30);
}

/**
  * @brief  GY_IMU数据包单位校验(单位长度校验)
  * @param[in]  buff	数据包
  * @retval 	0 校验失败，1校验通过
  */
uint8_t GY_IMU_Checksum(uint8_t* buff)
{
	uint8_t sum = 0;
	
	for(uint8_t i=0; i<18-1; i++)
	{
		sum += buff[i]; 
	}
	
	if(sum == buff[18-1])
	{
		//校验通过
		return 1;
	}
	else{
		return 0;
	}
	
}



/**
  * @brief  GY_IMU数据包校验
  * @param[in]  buff	数据包
  * @retval 	0 校验失败，1校验通过
  */
void GY_IMU_getInfo(uint8_t* buff, uint16_t dataLength, GY_IMU_t* dataOut)
{
	for(uint16_t n = 0; n < dataLength; )
	{
		//匹配帧头
		if( (buff[n] == 0x5A) && (buff[n+1] == 0x5A) )
		{
			if(GY_IMU_Checksum(&buff[n]))//确认过长度，是我想要的人
			{
				int16_t DATA[6];
				DATA[0]=(buff[n+4]<<8) | buff[n+5];
				DATA[1]=(buff[n+6]<<8) | buff[n+7];
				DATA[2]=(buff[n+8]<<8) | buff[n+9];
				DATA[3]=(buff[n+10]<<8) | buff[n+11];
				DATA[4]=(buff[n+12]<<8) | buff[n+13];
				DATA[5]=(buff[n+14]<<8) | buff[n+15];
				
				/*加速度*/
				dataOut->gyro.x = (float)DATA[0]/100;
				dataOut->gyro.y = (float)DATA[1]/100;
				dataOut->gyro.z = (float)DATA[2]/100;
				
				/*绝对式欧拉角*/
				dataOut->eular.yaw = (float)((uint16_t)DATA[3])/100;
				dataOut->eular.roll = (float)DATA[4]/100;
				dataOut->eular.pitch = (float)DATA[5]/100;
				
				dataOut->devStatus = buff[n+16];
				
				
					if(dataOut->eular.yaw - dataOut->lastYaw < -300)
					{
						dataOut->turnCount++;
					}
					
					if(dataOut->lastYaw - dataOut->eular.yaw < -300)
					{
						dataOut->turnCount--;
					}

				dataOut->lastYaw =  dataOut->eular.yaw;
				
				dataOut->totalYaw = dataOut->eular.yaw + (360.0f * dataOut->turnCount);
				
				dataOut->infoUpdateFrame++;
				dataOut->infoUpdateFlag = 1;
				GY_IMUpoint = 1;
				
				return;
			}
			else
			{
				n++;
			}
			
		}
		else
		{
			n++;
		}
	}
	
}

