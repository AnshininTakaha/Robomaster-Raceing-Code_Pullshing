/**
  ******************************************************************************
  * @file    Galvanometer.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   ��������Ϣ���պ����ӿ�
  ******************************************************************************
  */
#include "Galvanometer.h"

/*�����ƴ��溯��*/
GalvanometerData_t GalvanometerData;

void Galvanometer_Dealing(void)
{   
   if(GalvanometerData.data.chassisPowerBuffer < 30)
    {
		Chassis.Power_OverflowFlag = 1;
	} 

    if(Chassis.Power_OverflowFlag)
    {
		//���ʻ��嵽50�Ž������
		if(GalvanometerData.data.chassisPowerBuffer > 50)
        {
			Chassis.Power_OverflowFlag = 0;
			
		}
	}
 
}

/*���������Ŀ����Ϊ�˶�ȡ������ϵͳ�ĺ����������Ȳ���*/
// void Galvanometer_DataSend()
// {
//     uint8_t databuff[8];
	
// 	databuff[0] = (uint16_t)(Judge_PowerHeatData.data.chassisVolt *100);
// 	databuff[1] = (uint16_t)(Judge_PowerHeatData.data.chassisVolt *100)>>8;
// 	databuff[2] = (uint16_t)(Judge_PowerHeatData.data.chassisCurrent *100);
// 	databuff[3] = (uint16_t)(Judge_PowerHeatData.data.chassisCurrent *100)>>8;
// 	databuff[4] = (uint16_t)(Judge_PowerHeatData.data.chassisPower *100);
// 	databuff[5] = (uint16_t)(Judge_PowerHeatData.data.chassisPower *100)>>8;
// 	databuff[6] = (uint16_t)(Judge_PowerHeatData.data.chassisPowerBuffer *100);
// 	databuff[7] = (uint16_t)(Judge_PowerHeatData.data.chassisPowerBuffer *100)>>8;
	
// 	CAN_SendData(CAN1, CAN_ID_STD, 0x402, databuff);
// }