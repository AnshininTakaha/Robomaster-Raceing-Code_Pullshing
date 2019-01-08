/**
  ******************************************************************************
  * @file    Galvanometer.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   电流计信息接收函数接口
  ******************************************************************************
  */
#include "Galvanometer.h"

/*电流计储存函数*/
GalvanometerData_t GalvanometerData;

void Galvanometer_Dealing(void)
{   
   if(GalvanometerData.data.chassisPowerBuffer < 30)
    {
		Chassis.Power_OverflowFlag = 1;
	} 

    if(Chassis.Power_OverflowFlag)
    {
		//功率缓冲到50才解除限速
		if(GalvanometerData.data.chassisPowerBuffer > 50)
        {
			Chassis.Power_OverflowFlag = 0;
			
		}
	}
 
}

/*这个函数的目的是为了读取到裁判系统的函数，所以先不加*/
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