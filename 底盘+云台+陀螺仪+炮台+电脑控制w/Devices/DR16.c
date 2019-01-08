  /******************************************************************************
  * @file    DR16.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   DR16���ջ�Ӧ�ú����ӿڣ����ڽ����Ӧ���ܵ�����ͬʱ��ң��������PC���̽��и�ֵ
  ******************************************************************************
  */

#include "DR16.h"

/*��������λ��*/
int Data_Suppress(int16_t Data_Unsuppress);

/*����һ�����ݰ�����������ݵĴ��棬+2��һ����ֹ������ֵ���Դ���Ĳ���*/
/*ʵ����Ҳ���Բ�+2������+2���ӵľ�ȷ*/
/*DR16_DBUS_PACKSIZE = 18u,18u�ǽ��ջ����������ݵĴ�С*/
uint8_t DR16_rxBuff[18u+2]; 

/*����һ���������ݵ�ר�ŵĽṹ�壬ʹ��typedef�еĹ�����DR16_DBUS_DATA_t�ĸ�ʽ*/
DR16_DBUS_DATA_t dr16_data;

/*�������������ָˣ�ң��������ߺ��ұߵ��ָˣ�����ֵ�Ľṹ��rocker_t��������и�ֵ�ʹ���*/
rocker_t dr16_rocker_L,dr16_rocker_R;
rocker_t pcRocker;

/*����Ҽ����̵Ĵ�����*/
key_t dr16_keyBorad;
key_t dr16_mouseKeyLeft;
key_t dr16_mouseKeyRight;

/**
  * @brief  DR16��갴������(�ɰ�)
  * @param  *key �����ṹ��ָ�� @ref key_t
  * @retval None
  */
	
	/*������ʵ�ǰѰ����Ķ����ֳ��������֣�����ȥ���͵�����*/
	/*���ж����ǿ���֪������keyPressedJump = 1��ʱ��ʶ�𵽰����ɹ�����ʼ���*/
	/*������һ��ʼ����ȥ��ʱ����Ϊǰһ����û�а����ģ������ж��ж���keyReleaseJump����1*/
	/*Ȼ���key->KeyStatus��ֵ��ֵ��key->lastKeyStatus*/
	/*Ҳ����˵����һ���ж���ʱ����key->KeyStatus���0���ͻ��ٴν����ж�*/
	/*Ȼ�����if����keyPressedJump��1*/
	/*shoot = dr16_data.mouse.keyLeft.keyPressedJump���Ӷ����°���ʶ��ɹ����ӵ�����*/
//static void DR16_mouseKeyProcess(key_t *key)
//{
//	key->keyReleaseJump = 0;
//	key->keyPressedJump = 0;
//	
//	if (key->KeyStatus != key->lastKeyStatus) 
//	{
//		if(key->KeyStatus)
//			key->keyPressedJump = 1;
//		else
//			key->keyReleaseJump = 1;
//	}
//	
//	key->lastKeyStatus = key->KeyStatus;
//  
//}

/**
  * @brief  DR16���ջ���ʼ������
  * @param  None
  * @retval None
  */
void DR16_receiverInit(void)
{
	/*���ٶ���USART1*/
	USART1_QuickInit(100000);
	
	/*DR16_DBUS_PACKSIZE = 18u,18u�ǽ��ջ����������ݵĴ�С*/
	USART1_RXDMA_Config((uint32_t)DR16_rxBuff, 18u+2);	//+2��֤��ȫ
  
}

float PCKey_LpfAttFactor = 0.098f;

/**
  * @brief  DR16��������(����)
  * @param  KeyStatus  ����İ�����ֵ��״̬��  
						*key �����ṹ��ָ�� @ref key_t
  * @retval 
  */
void DR16_KeypointProcess(uint16_t KeyStatus, key_t *key)
{
	/*��¼�ı�־λ��ԭ*/
	key->keyPressedJump = 0;
	key->keyReleaseJump = 0;
	
	/*��ȡ��ǰ������ֵ*/
	key->KeyStatus = KeyStatus;
	
	/*��һ�εİ���ֵ�з��б仯*/
	if(key->lastKeyStatus != key->KeyStatus)
	{
		/*�����λ���ڵ�ֵ������ȥ�ˡ�ע�⣡�����ֵ��һ����1�������������������ֵ��*/
		if(key->KeyStatus)
		{
			key->keyPressedJump = key->KeyStatus;
		}
		else
		{
			key->keyReleaseJump = key->lastKeyStatus;
			key->longPressed = 0;
			key->timer = 0;
		}
	}	
	
	/*�ж������Ƿ�Ϊ����������ǳ����Ļ�*/
	if(key->KeyStatus)
	{
		key->timer++;
		if(key->timer++ > 50)
		{
			key->longPressed = key->KeyStatus;
			key->timer = 0;
		}
	}
		
		
		/*���ݰ�����ֵ*/
		key->lastKeyStatus = key->KeyStatus;
		
	
}


/**
  * @brief  ��������������
  * @param  KeyCode		��Ҫ���ļ�ֵ
  * 		mode		0 - ��ƥ����
  *						1 - ��ȫƥ��
  * @retval �Ƿ��������ֵ�İ�����������
  */
uint16_t dr16_keyboard_isJumpKey(uint16_t KeyCode, uint8_t mode)
{
	if(mode)
		{	//1 - ��ȫƥ��
			return dr16_keyBorad.keyPressedJump == KeyCode;
		}
	else
		{		//0 - ��ƥ����(Ҫ��⵽����ͬʱΪ��Ӧ�ļ�λ�ſ���)
			return dr16_keyBorad.keyPressedJump & KeyCode;
		}
	
}

/**
  * @brief  �������¼��
  * @param  KeyCode		��Ҫ���ļ�ֵ
  * @retval �Ƿ��������ֵ�İ�������
  */
uint16_t dr16_keyboard_isPressedKey(uint16_t KeyCode, uint8_t mode)
{
	if(mode)
	{	//1 - ��ȫƥ��
		return dr16_keyBorad.KeyStatus == KeyCode;
	}
	else
	{		//0 - ��ƥ����
		return dr16_keyBorad.KeyStatus & KeyCode;
	}
	
}







/**
  * @brief  DR16�������ݴ���
  * @param  pData			����buff����ָ��
  * @retval None
  */
void DR16_dataProcess(uint8_t *pData)
{
	
	/*���pData�����ǿյģ�ֱ�ӷ���*/
	if (pData == NULL)
	{
		return;
	}
	/*DR16��ң�������뺯�������忴ң�������û��ֲ�*/
	/*�����ǰѽ��յ��Ķ�ջ���н����Ȼ�󴢴浽һ���ṹ������*/
	/*ͨ�������Ӵ�������ֵ���ô���*/
	
	dr16_data.rc.ch0 = (pData[0] | (pData[1] << 8)) & 0x07FF;
	dr16_data.rc.ch1 = ((pData[1] >> 3) | (pData[2] << 5)) & 0x07FF;
	dr16_data.rc.ch2 = ((pData[2] >> 6) | (pData[3] << 2) | (pData[4] << 10)) & 0x07FF;
	dr16_data.rc.ch3 = ((pData[4] >> 1) | (pData[5] << 7)) & 0x07FF;
	
	dr16_data.rc.s_left = ((pData[5] >> 4) & 0x000C) >> 2;
	dr16_data.rc.s_right = ((pData[5] >> 4) & 0x0003);
	dr16_data.mouse.x = (pData[6]) | (pData[7] << 8);
	dr16_data.mouse.y = (pData[8]) | (pData[9] << 8);
	dr16_data.mouse.z = (pData[10]) | (pData[11] << 8);
	
	dr16_data.mouse.keyLeft = pData[12];
	dr16_data.mouse.keyRight = pData[13];
	
//	printf("%d,%d\r\n",pData[12],pData[13]);
	
	dr16_data.keyBoard.key_code = (pData[14] | pData[15] <<8);
//	printf("key_code = %d\r\n",pData[14]);
	//your control code ��.
	
	//֡�ʵ���
	dr16_data.infoUpdateFrame++;
	
	/*ң�����ĸ�ͨ���ĳ�ʼֵ��1024���仯��Χ0~2048*/
	/*����ֱ����Ϊ0�����ʱ��ͨ������ֵ�仯�ķ�Χ��-1024��1024*/
	dr16_data.rc.ch0 -=1024;
	dr16_data.rc.ch1 -=1024;
	dr16_data.rc.ch2 -=1024;
	dr16_data.rc.ch3 -=1024;
	
	/*����ѹ��*/
	dr16_data.rc.ch0 = Data_Suppress(dr16_data.rc.ch0);
	dr16_data.rc.ch1 = Data_Suppress(dr16_data.rc.ch1);
	dr16_data.rc.ch2 = Data_Suppress(dr16_data.rc.ch2);
	dr16_data.rc.ch3 = Data_Suppress(dr16_data.rc.ch3);
	
	/*ʹ��Rocker_getData������ң������Ӧ��ֵ��ֵ����Ӧ��ͨ������*/
	/*�����Ƿֿ���dr16_rocker_L��dr16_rocker_R����ͨ���ģ���ң������ֵ��ֵ��ȥ*/
	Rocker_getData(-dr16_data.rc.ch3, dr16_data.rc.ch2, &dr16_rocker_L);
	Rocker_getData(dr16_data.rc.ch0, dr16_data.rc.ch1, &dr16_rocker_R);
	
	/*���Լ�ֵתҡ��*/
	/*��ҡ�˵�ԭ����һ���ģ��������õ��Եļ�λ������ҡ�˶���*/
//	pcRocker.x = -dr16_data.keyBoard.press_A*600.0f + dr16_data.keyBoard.press_D*600.0f;
//	pcRocker.y = -dr16_data.keyBoard.press_S*600.0f + dr16_data.keyBoard.press_W*600.0f;
//	pcRocker.degrees = -dr16_data.keyBoard.press_Q*600.0f + dr16_data.keyBoard.press_E*600.0f;
	
	/*�ж������û�а���ȥ*/
	DR16_KeypointProcess(dr16_data.mouse.keyLeft,&dr16_mouseKeyLeft);
	DR16_KeypointProcess(dr16_data.mouse.keyRight,&dr16_mouseKeyLeft);
	
	//�ж�ģʽ(���uint8_t Control_getMode(void);��ʹ��)
	ControlStatus.ControlMode = dr16_data.rc.s_right;
	
	/*other control code��*/
	///
	
	
	
}





/**
  * @brief  DR16��������ѹ�ƣ�ʹң�������ӵ��ȶ�
  * @param 	Data_Unsuppress ��Ҫѹ�Ƶ�����
  * @retval None
  */

int Data_Suppress(int16_t Data_Unsuppress)
{
	int16_t Be_Suppress;
	
	if(Data_Unsuppress  >= 0)
	{
		
		if(Data_Unsuppress < 20)
		{
			Be_Suppress = 0;
			return Be_Suppress;
		}
		//if not
		Be_Suppress = Data_Unsuppress;
		return Be_Suppress;
	}
	else//Data_Unsuppress < 0
	{
		if(Data_Unsuppress > -20)
		{
			Be_Suppress = 0;
			return Be_Suppress;
		}
		//if not
		Be_Suppress = Data_Unsuppress;
		return Be_Suppress;
	}
}




