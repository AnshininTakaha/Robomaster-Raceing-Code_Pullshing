#include "DR16.h"

/*DR16�շ��ṹ��Ĵ�����Ϊ22u������4λ���Լ������NULLλ*/
uint8_t DR16_Buff[18u+4]; 

/*DR16ң�����ṹ��*/
DR16_DBUS_DATA_st DR16;

/*DR16ң������ң�к���ң��*/
rocker_st rocket_Left,rocket_Right;

/*���̣�������Ҽ�λ�����ݴ���*/
Key_st keyBorad;
Key_st MouseKeyLeft;
Key_st MouseKeyRight;
/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    DR16_Init
  * @brief   DR16ң������ʼ��
  * @param   None
  * @author  ���� 
  * @Data    2018-10-30
 **/
/* -------------------------------- end -------------------------------- */

void DR16_Init(void)
{
	USART1_QuickInit(100000);
	USART1_RXDMA_Config((uint32_t)DR16_Buff, 18u+4);
}




/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    DR16_Process
  * @brief   DR16���ݽ��
  * @param   pData(st):��Ӧ�����ݽṹ�� 
  * @author  ���� 
  * @Data    2018-11-02
 **/
/* -------------------------------- end -------------------------------- */

void DR16_Process(uint8_t *pData)
{
	/*��ֵ����*/
	if(pData == NULL)
	{
		return;
	}
	
	/*ң�����ĸ�ͨ��������������*/
	DR16.rc.ch0 = (pData[0] | (pData[1] << 8)) & 0x07FF;
	DR16.rc.ch1 = ((pData[1] >> 3) | (pData[2] << 5)) & 0x07FF;
	DR16.rc.ch2 = ((pData[2] >> 6) | (pData[3] << 2) | (pData[4] << 10)) & 0x07FF;
	DR16.rc.ch3 = ((pData[4] >> 1) | (pData[5] << 7)) & 0x07FF;
	DR16.rc.s_left = ((pData[5] >> 4) & 0x000C) >> 2;
	DR16.rc.s_right = ((pData[5] >> 4) & 0x0003);
	
	
	/*���*/
	DR16.mouse.x = (pData[6]) | (pData[7] << 8);
	DR16.mouse.y = (pData[8]) | (pData[9] << 8);
	DR16.mouse.z = (pData[10]) | (pData[11] << 8);
	DR16.mouse.keyLeft = pData[12];
	DR16.mouse.keyRight = pData[13];
	
	/*������ֵ����*/
	DR16.keyBoard.key_code = (pData[14] | pData[15] <<8);
	
	/*���ݱ���У׼��ѹ��*/
	DR16.rc.ch0 -= 1024;
	DR16.rc.ch1 -= 1024;
	DR16.rc.ch2 -= 1024;
	DR16.rc.ch3 -= 1024;
	
	DR16.rc.ch0 = Data_Suppres(DR16.rc.ch0);
	DR16.rc.ch1 = Data_Suppres(DR16.rc.ch1);
	DR16.rc.ch2 = Data_Suppres(DR16.rc.ch2);
	DR16.rc.ch3 = Data_Suppres(DR16.rc.ch3);
	

	/*JUDGEMENT ANG TRANSFORM..*/
	/*���Ҹ����ݴ���*/
	Rocker_Stander(-DR16.rc.ch3,DR16.rc.ch2,&rocket_Left);
	Rocker_Stander(DR16.rc.ch0,DR16.rc.ch1,&rocket_Right);
	
	/*����λֵ�ж�*/
	DR16_Key_Whether_Process(DR16.mouse.keyLeft,&MouseKeyLeft);
	DR16_Key_Whether_Process(DR16.rc.s_right,&MouseKeyRight);
	
	/***���̼�λ�ж�*/
	DR16_Key_Whether_Process(DR16.keyBoard.key_code,&keyBorad);
	
	/*����ֵdealing...*/
	DR16.UpdateFrame++;
	/*ң����ģʽѡ��*/
	Chassis.modeswitch = DR16.rc.s_right;
	Cloud.modeswitch = DR16.rc.s_right;
}






/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    DR16_Key_Whether_Process
  * @brief   ��λֵ����������ֵ������Ϳ���
  * @param   KeyStatus: ��λֵ
					   Key(st):Key����
  * @author  ���� 
  * @Data    2018-11-02
 **/
/* -------------------------------- end -------------------------------- */

void DR16_Key_Whether_Process(uint16_t KeyStatus, Key_st *key)
{
	/*��ȡ��λ��ֵ*/
	key->key_Status = KeyStatus;
	
	key->key_up_point = 0;
	key->key_dowm_point = 0;
	
	if(key->last_key_Status != key->key_Status)
	{
		if(key->key_Status)//�а�����ֵ����Ϊ0��
		{
			key->key_up_point = key->key_Status;
		}
		else
		{
			key->key_dowm_point = key->last_key_Status;
			key->key_longpress_point = 0;
			key->pointing_time = 0;
		}
	}
	
	/*��������ֵ*/
	if(key->key_Status)
	{
		key->pointing_time++;
		if(key->pointing_time > 50)
		{
			key->key_longpress_point = key->key_Status;
			key->pointing_time = 0;
		}
	}
	
	key->last_key_Status = key->key_Status;
	
}



/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    Data_Suppres
  * @brief   ����ѹ��
  * @param   data: �жϵ����� 
  * @author  ���� 
  * @Data    2018-11-02
 **/
/* -------------------------------- end -------------------------------- */

int Data_Suppres(int16_t data)
{
	if(abs_Calculation(data) < 20)
	{
		data = 0;
	}

	
	return data;
}


/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    GetSwitch_Mode
  * @brief   ��ȡң�������ұ�ҡ�˵�ֵ��ģʽ���ƣ�
  * @param   None
  * @author  ���� 
  * @Data    2018-11-05
 **/
/* -------------------------------- end -------------------------------- */

int GetSwitch_ModeChassis(void)
{
	return Chassis.modeswitch;
}

int GetSwitch_ModeCloud(void)
{
	return Cloud.modeswitch;
}

int GetSwitch_Mode(void)
{
	if(Chassis.modeswitch == Cloud.modeswitch)
	{
		return Cloud.modeswitch;
	}
}
