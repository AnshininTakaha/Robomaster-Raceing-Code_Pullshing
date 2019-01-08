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
rocker_t pcRocker;

/*左键右键键盘的储存体*/
key_t dr16_keyBorad;
key_t dr16_mouseKeyLeft;
key_t dr16_mouseKeyRight;

/**
  * @brief  DR16鼠标按键处理(旧版)
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
  * @brief  DR16按键处理(键盘)
  * @param  KeyStatus  输入的按键的值（状态）  
						*key 按键结构体指针 @ref key_t
  * @retval 
  */
void DR16_KeypointProcess(uint16_t KeyStatus, key_t *key)
{
	/*记录的标志位复原*/
	key->keyPressedJump = 0;
	key->keyReleaseJump = 0;
	
	/*获取当前按键的值*/
	key->KeyStatus = KeyStatus;
	
	/*这一次的按键值有否有变化*/
	if(key->lastKeyStatus != key->KeyStatus)
	{
		/*如果键位现在的值代表按下去了【注意！这里的值不一定是1！！而是两个键的组合值】*/
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
	
	/*判定按键是否为长按，如果是长按的话*/
	if(key->KeyStatus)
	{
		key->timer++;
		if(key->timer++ > 50)
		{
			key->longPressed = key->KeyStatus;
			key->timer = 0;
		}
	}
		
		
		/*传递按键的值*/
		key->lastKeyStatus = key->KeyStatus;
		
	
}


/**
  * @brief  按键按下跳变检测
  * @param  KeyCode		需要检测的键值
  * 		mode		0 - 有匹配项
  *						1 - 完全匹配
  * @retval 是否有这个键值的按键按下跳变
  */
uint16_t dr16_keyboard_isJumpKey(uint16_t KeyCode, uint8_t mode)
{
	if(mode)
		{	//1 - 完全匹配
			return dr16_keyBorad.keyPressedJump == KeyCode;
		}
	else
		{		//0 - 有匹配项(要检测到按下同时为对应的键位才可以)
			return dr16_keyBorad.keyPressedJump & KeyCode;
		}
	
}

/**
  * @brief  按键按下检测
  * @param  KeyCode		需要检测的键值
  * @retval 是否有这个键值的按键按下
  */
uint16_t dr16_keyboard_isPressedKey(uint16_t KeyCode, uint8_t mode)
{
	if(mode)
	{	//1 - 完全匹配
		return dr16_keyBorad.KeyStatus == KeyCode;
	}
	else
	{		//0 - 有匹配项
		return dr16_keyBorad.KeyStatus & KeyCode;
	}
	
}







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
	
	dr16_data.mouse.keyLeft = pData[12];
	dr16_data.mouse.keyRight = pData[13];
	
//	printf("%d,%d\r\n",pData[12],pData[13]);
	
	dr16_data.keyBoard.key_code = (pData[14] | pData[15] <<8);
//	printf("key_code = %d\r\n",pData[14]);
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
//	pcRocker.x = -dr16_data.keyBoard.press_A*600.0f + dr16_data.keyBoard.press_D*600.0f;
//	pcRocker.y = -dr16_data.keyBoard.press_S*600.0f + dr16_data.keyBoard.press_W*600.0f;
//	pcRocker.degrees = -dr16_data.keyBoard.press_Q*600.0f + dr16_data.keyBoard.press_E*600.0f;
	
	/*判定鼠标有没有按下去*/
	DR16_KeypointProcess(dr16_data.mouse.keyLeft,&dr16_mouseKeyLeft);
	DR16_KeypointProcess(dr16_data.mouse.keyRight,&dr16_mouseKeyLeft);
	
	//判断模式(结合uint8_t Control_getMode(void);来使用)
	ControlStatus.ControlMode = dr16_data.rc.s_right;
	
	/*other control code…*/
	///
	
	
	
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




