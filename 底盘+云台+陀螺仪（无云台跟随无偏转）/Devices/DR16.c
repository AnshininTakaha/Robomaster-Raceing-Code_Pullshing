  /******************************************************************************
  * @file    DR16.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   DR16接收机应用函数接口，用于解码对应接受的数据同时对遥控器或者PC键盘进行赋值
  ******************************************************************************
  */

#include "DR16.h"

/*调整函数位置*/
int Data_Suppress(int16_t Data_Unsuppress);

/*定义一个数据包方便进行数据的储存，+2是一个防止接受数值忽略错误的操作*/
/*实际上也可以不+2，不过+2更加的精确*/
/*DR16_DBUS_PACKSIZE = 18u,18u是接收机的整包数据的大小*/
uint8_t DR16_rxBuff[18u+2]; 

/*定义一个接受数据的专门的结构体，使用typedef中的共用体DR16_DBUS_DATA_t的格式*/
DR16_DBUS_DATA_t dr16_data;

/*定义两个储存手杆（遥控器的左边和右边的手杆）返回值的结构体rocker_t，方便进行赋值和储存*/
rocker_t dr16_rocker_L,dr16_rocker_R;

/*定义一个储存电脑控制返回值的结构体，方便进行赋值和储存*/
/*在正式的比赛中由于是通过通过电脑来控制的，所以有必要写这个PC的操控方式*/
/*使用的是和遥控手柄一样的结构体*/
rocker_t pcRocker;


/**
  * @brief  DR16鼠标按键处理
  * @param  *key 按键结构体指针 @ref key_t
  * @retval None
  */
	
	/*这里其实是把按键的动作分成两个部分，按下去，和弹起来*/
	/*从中断我们可以知道，当keyPressedJump = 1的时候，识别到按键成功并开始射击*/
	/*当我们一开始按下去的时候，因为前一刻是没有按键的，按照中断判定，keyReleaseJump会置1*/
	/*然后把key->KeyStatus的值赋值给key->lastKeyStatus*/
	/*也就是说在下一次判定的时候，若key->KeyStatus变成0，就会再次进入中断*/
	/*然后进入if，把keyPressedJump置1*/
	/*shoot = dr16_data.mouse.keyLeft.keyPressedJump，从而导致按键识别成功，子弹发射*/
static void DR16_mouseKeyProcess(key_t *key)
{
	key->keyReleaseJump = 0;
	key->keyPressedJump = 0;
	
	if (key->KeyStatus != key->lastKeyStatus) 
	{
		if(key->KeyStatus)
			key->keyPressedJump = 1;
		else
			key->keyReleaseJump = 1;
	}
	
	key->lastKeyStatus = key->KeyStatus;
  
}

/**
  * @brief  DR16接收机初始化函数
  * @param  None
  * @retval None
  */
void DR16_receiverInit(void)
{
	/*快速定义USART1*/
	USART1_QuickInit(100000);
	
	/*DR16_DBUS_PACKSIZE = 18u,18u是接收机的整包数据的大小*/
	USART1_RXDMA_Config((uint32_t)DR16_rxBuff, 18u+2);	//+2保证安全
  
}

float PCKey_LpfAttFactor = 0.098f;





/**
  * @brief  DR16接收数据处理
  * @param  pData			接收buff数据指针
  * @retval None
  */
void DR16_dataProcess(uint8_t *pData)
{
	
	/*如果pData里面是空的，直接返回*/
	if (pData == NULL)
	{
		return;
	}
	/*DR16大疆遥控器解码函数，具体看遥控器的用户手册*/
	/*这里是把接收到的堆栈进行解读，然后储存到一个结构体里面*/
	/*通过这样子处理让数值更好处理*/
	
	dr16_data.rc.ch0 = (pData[0] | (pData[1] << 8)) & 0x07FF;
	dr16_data.rc.ch1 = ((pData[1] >> 3) | (pData[2] << 5)) & 0x07FF;
	dr16_data.rc.ch2 = ((pData[2] >> 6) | (pData[3] << 2) | (pData[4] << 10)) & 0x07FF;
	dr16_data.rc.ch3 = ((pData[4] >> 1) | (pData[5] << 7)) & 0x07FF;
	
	dr16_data.rc.s_left = ((pData[5] >> 4) & 0x000C) >> 2;
	dr16_data.rc.s_right = ((pData[5] >> 4) & 0x0003);
	dr16_data.mouse.x = (pData[6]) | (pData[7] << 8);
	dr16_data.mouse.y = (pData[8]) | (pData[9] << 8);
	dr16_data.mouse.z = (pData[10]) | (pData[11] << 8);
	dr16_data.mouse.keyLeft.KeyStatus = pData[12];
	dr16_data.mouse.keyRight.KeyStatus = pData[13];
	dr16_data.keyBoard.key_code = pData[14];
	//your control code ….
	
	//帧率叠加
	dr16_data.infoUpdateFrame++;
	
	/*遥控器四个通道的初始值是1024，变化范围0~2048*/
	/*这里直接置为0，这个时候通道的数值变化的范围是-1024到1024*/
	dr16_data.rc.ch0 -=1024;
	dr16_data.rc.ch1 -=1024;
	dr16_data.rc.ch2 -=1024;
	dr16_data.rc.ch3 -=1024;
	
	/*数据压制*/
	dr16_data.rc.ch0 = Data_Suppress(dr16_data.rc.ch0);
	dr16_data.rc.ch1 = Data_Suppress(dr16_data.rc.ch1);
	dr16_data.rc.ch2 = Data_Suppress(dr16_data.rc.ch2);
	dr16_data.rc.ch3 = Data_Suppress(dr16_data.rc.ch3);
	
	/*使用Rocker_getData函数把遥控器对应的值赋值到对应的通道里面*/
	/*这里是分开了dr16_rocker_L和dr16_rocker_R两个通道的，把遥控器的值赋值进去*/
	Rocker_getData(-dr16_data.rc.ch3, dr16_data.rc.ch2, &dr16_rocker_L);
	Rocker_getData(dr16_data.rc.ch0, dr16_data.rc.ch1, &dr16_rocker_R);
	
	/*电脑键值转摇杆*/
	/*和摇杆的原理是一样的，不过是用电脑的键位来代替摇杆而已*/
	pcRocker.x = -dr16_data.keyBoard.press_A*600.0f + dr16_data.keyBoard.press_D*600.0f;
	pcRocker.y = -dr16_data.keyBoard.press_S*600.0f + dr16_data.keyBoard.press_W*600.0f;
	pcRocker.degrees = -dr16_data.keyBoard.press_Q*600.0f + dr16_data.keyBoard.press_E*600.0f;
	
	/*判定鼠标有没有按下去*/
	DR16_mouseKeyProcess(&dr16_data.mouse.keyLeft);
	DR16_mouseKeyProcess(&dr16_data.mouse.keyRight);
	
	//判断模式(结合uint8_t Control_getMode(void);来使用)
	ControlStatus.ControlMode = dr16_data.rc.s_right;
	
	/*other control code…*/
	
	
	
	
}


/**
  * @brief  DR16接收数据压制，使遥控器更加的稳定
  * @param 	Data_Unsuppress 将要压制的数据
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
