#include "Motor_M6623.h"

M6623s_t M6623s[2];

/**
  * @brief  从CAN报文中获取M6623电机信息
  * @param  *RxMessage 	CAN报文接收结构体指针
  *			**info		M6623s_t电机数组指针
  * @retval None
  */
void M6623_getInfo(CanRxMsg RxMessage)
{
	//报文id确认
	if((RxMessage.StdId < M6623_READID_START) || (RxMessage.StdId > M6623_READID_END))
	{
		return;
	}
	
	
		
	uint32_t StdId;
	StdId = RxMessage.StdId - M6623_READID_START;
	
	//解包数据，数据格式详见6623电调说明书P8
	M6623s[StdId].realAngle = (uint16_t)(RxMessage.Data[0]<<8 | RxMessage.Data[1]);
	M6623s[StdId].realCurrent = (int16_t)(RxMessage.Data[2]<<8 | RxMessage.Data[3]);
	//info[StdId]->setCurrent = (int16_t)(RxMessage->Data[4]<<8 | RxMessage->Data[5]);
	
	
	
	if(M6623s[StdId].realAngle - M6623s[StdId].lastAngle < -6000)
	{
		M6623s[StdId].turnCount++;
	}
	
	if(M6623s[StdId].lastAngle - M6623s[StdId].realAngle < -6000)
	{
		M6623s[StdId].turnCount--;
	}
	
	M6623s[StdId].lastAngle =  M6623s[StdId].realAngle;
	
	/*圈数累积*/
	M6623s[StdId].totalAngle = M6623s[StdId].realAngle + (8192*M6623s[StdId].turnCount);
	
	/*读取成功，刷新置1*/
	M6623s[StdId].infoUpdateFlag = 1;
	
	/**/
	M6623s[StdId].infoUpdateFrame++;
	
}	


/**
  * @brief  设定M6623电机的目标角度
  * @param  motorName 	电机名字 @ref M6623Name_e
  *			angle		电流值，范围 0~8191 由于设置0和8191会导致电机振荡，要做个限幅
  * @retval None
  */
void M6623_setTargetAngle(M6623Name_e motorName, int32_t angle)
{
	M6623s[motorName].targetAngle = angle;
}
