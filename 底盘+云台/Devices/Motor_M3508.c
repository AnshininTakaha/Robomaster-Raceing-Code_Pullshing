/**
  ******************************************************************************
  * @file    M3508_Motor.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   M3508��ˢ���������C620�������Ӧ�ú����ӿ�
  ******************************************************************************
  */

#include "Motor_M3508.h"

/*����һ������Ĺ�����*/
M3508s_t M3508s[4];

/**
  * @brief  ��CAN�����л�ȡM3508�����Ϣ
  * @param  *RxMessage 	CAN���Ľ��սṹ��ָ��
  *			**info		M3508s_t�������ָ��
  * @retval None
  */
void M3508_getInfo(CanRxMsg RxMessage)
	{
	/*����IDȷ�ϣ������ǲ����ĸ��������е�һ��*/
	/*������ǵĻ�������*/
	/*ΪʲôSTDIDҪ�������渳ֵ��
	���㸳ֵ������Ҫ��ֵ�ж�֮���ٴθ�ֵ���Ƚϵķ���*/
	if((RxMessage.StdId < 0x201) || (RxMessage.StdId > 0x204))
		return;
	
	/*�ڼ���֮��Ŷ����Ӧ��Ҫ�����STDID����������ͼӿ����е��ٶ�*/
	uint32_t StdId;
	
	/*��������ڶ�Ӧ��ID��Ӧ�ı�ţ��ֱ���1��2��3��4�����������ĸ�ֵ����*/
	StdId = RxMessage.StdId - 0x201;
	
	/*������ݣ����ݸ�ʽ���C620���˵����P33*/
	M3508s[StdId].realAngle = (uint16_t)(RxMessage.Data[0]<<8 | RxMessage.Data[1]); //ת�ӻ�е�Ƕȸ�8λ�͵�8λ
	
	M3508s[StdId].realSpeed = (int16_t)(RxMessage.Data[2]<<8 | RxMessage.Data[3]);  //ת��ת�ٸ�8λ�͵�8λ
	
	M3508s[StdId].realCurrent = (int16_t)(RxMessage.Data[4]<<8 | RxMessage.Data[5]);//ʵ��ת�ظ�8λ�͵�8λ
	
	M3508s[StdId].temperture = RxMessage.Data[6];                                   //����¶�
	
	M3508s[StdId].infoUpdateFlag = 1;                                               //�Ƿ���Ը��µı�־λ
}	



/**
  * @brief  ����M3508�������ֵ��id��Ϊ1~4��
  * @param  iqx (x:1~4) ��Ӧid�ŵ���ĵ���ֵ����Χ-16384~0~16384
  * @retval None
  */
void M3508_setCurrent(int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4)
{

	uint8_t data[8];
	
	//���ݸ�ʽ���˵����P32
	data[0] = iq1 >> 8;
	data[1] = iq1;
	data[2] = iq2 >> 8;
	data[3] = iq2;
	data[4] = iq3 >> 8;
	data[5] = iq3;
	data[6] = iq4 >> 8;
	data[7] = iq4;
	
	/*ͨ��CAN1���ĸ����ӷ��Ͷ�Ӧ�ĵ���*/
	/*��������ַ�����ݸ�ʽ�ᰴ�ո�ʽ��ʼ���ţ��ﵽ�������������Ŀ��*/
	CAN_SendData(CAN1, CAN_ID_STD, 0x200, data);
	
}	

