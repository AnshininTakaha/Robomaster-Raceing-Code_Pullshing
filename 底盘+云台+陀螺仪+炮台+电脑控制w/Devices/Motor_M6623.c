#include "Motor_M6623.h"

M6623s_t M6623s[2];

/**
  * @brief  ��CAN�����л�ȡM6623�����Ϣ
  * @param  *RxMessage 	CAN���Ľ��սṹ��ָ��
  *			**info		M6623s_t�������ָ��
  * @retval None
  */
void M6623_getInfo(CanRxMsg RxMessage)
{
	//����idȷ��
	if((RxMessage.StdId < M6623_READID_START) || (RxMessage.StdId > M6623_READID_END))
	{
		return;
	}
	
	
		
	uint32_t StdId;
	StdId = RxMessage.StdId - M6623_READID_START;
	
	//������ݣ����ݸ�ʽ���6623���˵����P8
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
	
	/*Ȧ���ۻ�*/
	M6623s[StdId].totalAngle = M6623s[StdId].realAngle + (8192*M6623s[StdId].turnCount);
	
	/*��ȡ�ɹ���ˢ����1*/
	M6623s[StdId].infoUpdateFlag = 1;
	
	/**/
	M6623s[StdId].infoUpdateFrame++;
	
}	


/**
  * @brief  �趨M6623�����Ŀ��Ƕ�
  * @param  motorName 	������� @ref M6623Name_e
  *			angle		����ֵ����Χ 0~8191 ��������0��8191�ᵼ�µ���񵴣�Ҫ�����޷�
  * @retval None
  */
void M6623_setTargetAngle(M6623Name_e motorName, int32_t angle)
{
	M6623s[motorName].targetAngle = angle;
}
