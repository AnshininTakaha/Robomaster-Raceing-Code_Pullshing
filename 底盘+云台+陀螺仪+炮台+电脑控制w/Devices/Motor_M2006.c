#include "Motor_M2006.h"

M2006s_t M2006s[1] = {{.targetAngle = M2006_start_up}};

/**
  * @brief  从CAN报文中获取M2006电机信息
  * @param[in]  RxMessage 	CAN报文接收结构体
  * @retval None
  */
void M2006_getInfo(CanRxMsg RxMessage)
{
	if((RxMessage.StdId < M2006_READID_START) || (RxMessage.StdId > M2006_READID_END))
		return;
	uint32_t StdId;
	StdId = RxMessage.StdId - M2006_READID_START;
	
	//解包数据，数据格式详见C610电调说明书P9
	M2006s[StdId].realAngle = (uint16_t)(RxMessage.Data[0]<<8 | RxMessage.Data[1]);//机械角度高低8
	M2006s[StdId].realSpeed = (int16_t)(RxMessage.Data[2]<<8 | RxMessage.Data[3]);//转子转速高低8
	M2006s[StdId].realTorque = (int16_t)(RxMessage.Data[4]<<8 | RxMessage.Data[5]);//实际输出转矩高低8
	
	/*读取变化值看看是否过零*/
	if(M2006s[StdId].realAngle - M2006s[StdId].lastAngle < -6000)
	{
		M2006s[StdId].turnCount++;
	}
	
	if(M2006s[StdId].lastAngle - M2006s[StdId].realAngle < -6000)
	{
		M2006s[StdId].turnCount--;
	}
	
	M2006s[StdId].lastAngle =  M2006s[StdId].realAngle;
	
	M2006s[StdId].totalAngle = M2006s[StdId].realAngle + (8192*M2006s[StdId].turnCount);
	
	M2006s[StdId].infoUpdateFrame++;
	
	/*读取数据完成，标志位置为1*/
	M2006s[StdId].infoUpdateFlag = 1;
}


