#include "Motor_M2006.h"

M2006s_t M2006s[1] = {{.targetAngle = M2006_start_up}};

/**
  * @brief  ��CAN�����л�ȡM2006�����Ϣ
  * @param[in]  RxMessage 	CAN���Ľ��սṹ��
  * @retval None
  */
void M2006_getInfo(CanRxMsg RxMessage)
{
	if((RxMessage.StdId < M2006_READID_START) || (RxMessage.StdId > M2006_READID_END))
		return;
	uint32_t StdId;
	StdId = RxMessage.StdId - M2006_READID_START;
	
	//������ݣ����ݸ�ʽ���C610���˵����P9
	M2006s[StdId].realAngle = (uint16_t)(RxMessage.Data[0]<<8 | RxMessage.Data[1]);//��е�Ƕȸߵ�8
	M2006s[StdId].realSpeed = (int16_t)(RxMessage.Data[2]<<8 | RxMessage.Data[3]);//ת��ת�ٸߵ�8
	M2006s[StdId].realTorque = (int16_t)(RxMessage.Data[4]<<8 | RxMessage.Data[5]);//ʵ�����ת�ظߵ�8
	
	/*��ȡ�仯ֵ�����Ƿ����*/
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
	
	/*��ȡ������ɣ���־λ��Ϊ1*/
	M2006s[StdId].infoUpdateFlag = 1;
}


