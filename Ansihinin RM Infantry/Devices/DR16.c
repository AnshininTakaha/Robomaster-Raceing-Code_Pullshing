#include "DR16.h"

uint8_t DR16_Buff[18u+2]; 
DR16_t DR16;
/*作为遥控器控制的时候的两个十字结构体*/
rocker_t rocket_Left,rocket_Right;

/*作为电脑控制的时候的结构体*/
rocker_t pcRocket;

/*键盘按键的判断结构体*/
Key_st keyBorad;
Key_st MouseKeyLeft;
Key_st MouseKeyRight;

/*模式*/

/**
* @name DR16_Init
* @brief 初始化DR16遥控器
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
* @brief DR16遥控器函数解码z
* @param [in]uint8_t *pData 需要解码的指针
* @retval 
*/
void DR16_Process(uint8_t *pData)
{
	/*空值返回*/
	if(pData == NULL)
	{
		return;
	}
	
	/*遥控器四个通道和两个拨动杆*/
	DR16.rc.ch0 = (pData[0] | (pData[1] << 8)) & 0x07FF;
	DR16.rc.ch1 = ((pData[1] >> 3) | (pData[2] << 5)) & 0x07FF;
	DR16.rc.ch2 = ((pData[2] >> 6) | (pData[3] << 2) | (pData[4] << 10)) & 0x07FF;
	DR16.rc.ch3 = ((pData[4] >> 1) | (pData[5] << 7)) & 0x07FF;
	DR16.rc.s_left = ((pData[5] >> 4) & 0x000C) >> 2;
	DR16.rc.s_right = ((pData[5] >> 4) & 0x0003);
	
	
	/*鼠标*/
	DR16.mouse.x = (pData[6]) | (pData[7] << 8);
	DR16.mouse.y = (pData[8]) | (pData[9] << 8);
	DR16.mouse.z = (pData[10]) | (pData[11] << 8);
	DR16.mouse.keyLeft = pData[12];
	DR16.mouse.keyRight = pData[13];
	
	/*键盘数值控制（这里使用手册是写漏的了）*/
	DR16.keyBoard.key_code = (pData[14] | pData[15] <<8);
	
	/*数据便宜校准和压制*/
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
* @brief 数据压制
* @param [in] int16_t data 需要进行压制的数目
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
* @brief 左/右遥控杆数值传递
* @param [in] float positionX     X轴数值
*        [in] float positionY     Y轴数值
*        [out] rocker_st *rocket   rocket结构体
* @retval 把遥感的值转换成为单个遥感的值
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
* @name GetSwitch系列
* @brief 获取遥控器的模式
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



















