#include "GY_IMU.h"

uint8_t Cloud_GY_IMU_RXBUFF[GY_IMU_BUFFSIZE];

void GY_IMU_Init(void)
{
	USART3_QuickInit(115200);
	USART3_RXDMA_Config((uint32_t)Cloud_GY_IMU_RXBUFF, GY_IMU_BUFFSIZE);
}

/**
  * @brief  GY_IMU���ݰ�У��
  * @param[in]  buff	���ݰ�
  * @retval 	0 У��ʧ�ܣ�1У��ͨ��
  */
uint8_t GY_IMU_Checksum(uint8_t* buff)
{
	uint8_t sum = 0;
	
	for(uint8_t i=0; i<GY_IMU_PACKAGE_LENGTH-1; i++){
		sum += buff[i]; 
	}
	
	if(sum == buff[GY_IMU_PACKAGE_LENGTH-1]){
		//У��ͨ��
		return 1;
	}
	else{
		return 0;
	}
	
}


/**
  * @brief  GY_IMU���ݰ�У��
  * @param[in]  buff	���ݰ�
  * @retval 	0 У��ʧ�ܣ�1У��ͨ��
  */
void GY_IMU_getInfo(uint8_t* buff, uint16_t dataLength, GY_IMU_t* dataOut)
	{
	
	for(uint16_t n = 0; n < dataLength; ){
		//ƥ��֡ͷ
		if( (buff[n] == 0x5A) && (buff[n+1] == 0x5A) )
		{
			if(GY_IMU_Checksum(&buff[n]))
			{
				int16_t DATA[6];
				DATA[0]=(buff[n+4]<<8) | buff[n+5];
				DATA[1]=(buff[n+6]<<8) | buff[n+7];
				DATA[2]=(buff[n+8]<<8) | buff[n+9];
				DATA[3]=(buff[n+10]<<8) | buff[n+11];
				DATA[4]=(buff[n+12]<<8) | buff[n+13];
				DATA[5]=(buff[n+14]<<8) | buff[n+15];
				
				dataOut->gyro.x = (float)DATA[0]/100;
				dataOut->gyro.y = (float)DATA[1]/100;
				dataOut->gyro.z = (float)DATA[2]/100;
				
				
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
				
				dataOut->UpdateFrame++;
				dataOut->UpdateFlag = 1;
				
				return;
			}
			else{
				n++;
			}
			
		}
		else{
			n++;
		}
	}
	
}