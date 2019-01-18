#include "DR16.h"

uint8_t DR16_Buff[18u+2]; 
DR16_t DR16;
/*��Ϊң�������Ƶ�ʱ�������ʮ�ֽṹ��*/
rocker_t rocket_Left,rocket_Right;

/*��Ϊ���Կ��Ƶ�ʱ��Ľṹ��*/
rocker_t pcRocket;

/*���̰������жϽṹ��*/
Key_st keyBorad;
Key_st MouseKeyLeft;
Key_st MouseKeyRight;

/*ģʽ*/

/**
* @name DR16_Init
* @brief ��ʼ��DR16ң����
* @param None
* @retval 
*/
void DR16_Init(void)
{
	USART1_QuickInit(100000);
	USART1_RXDMA_Config((uint32_t)DR16_Buff, 18u+2);
}
/**
* @name DR16_Process
* @brief DR16ң������������z
* @param [in]uint8_t *pData ��Ҫ�����ָ��
* @retval 
*/
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
	
	/*������ֵ���ƣ�����ʹ���ֲ���д©���ˣ�*/
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

	Rocker_Stander(DR16.rc.ch3,-DR16.rc.ch2,&rocket_Left);
	Rocker_Stander(DR16.rc.ch0,DR16.rc.ch1,&rocket_Right);

	DR16_Key_Whether_Process(DR16.mouse.keyLeft,&MouseKeyLeft);
	DR16_Key_Whether_Process(DR16.mouse.keyRight,&MouseKeyRight);
	DR16_Key_Whether_Process(DR16.keyBoard.key_code,&keyBorad);

	DR16.UpdateFrame++;
	Chassis.modeswitch = DR16.rc.s_right;
	Cloud.modeswitch = DR16.rc.s_right;
}
/**
* @name Data_Suppres
* @brief ����ѹ��
* @param [in] int16_t data ��Ҫ����ѹ�Ƶ���Ŀ
* @retval 
*/
int Data_Suppres(int16_t data)
{
	if(abs_Calculation(data) < 20)
	{
		data = 0;
	}
	return data;
}

/**
* @name Rocker_Stander
* @brief ��/��ң�ظ���ֵ����
* @param [in] float positionX     X����ֵ
*        [in] float positionY     Y����ֵ
*        [out] rocker_st *rocket   rocket�ṹ��
* @retval ��ң�е�ֵת����Ϊ����ң�е�ֵ
*/
void Rocker_Stander(float positionX, float positionY, rocker_t *rocket)
{
    rocket->x = positionX;
    rocket->y = positionY;
    rocket->radian = atan2(rocket->y,rocket->x);
    rocket->degrees = rocket->radian * 180.0f / PI;//using the PI of arm_...
    rocket->distance = __sqrtf(pow(rocket->x,2) + pow(rocket->y,2));
    if(rocket -> degrees > 180)
    {
        rocket -> distance = -rocket -> distance;
    }
}

/**
* @name GetSwitchϵ��
* @brief ��ȡң������ģʽ
* @param None
* @retval 
*/
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



















