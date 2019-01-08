#include "PC_control.h"

pc_st pc;

/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    PC_MODE_Init
  * @brief
  * @param   None
  * @author  口无
  * @Data    2018-11-13
 **/
/* -------------------------------- end -------------------------------- */

void PC_MODE_Init(void)
{
    /*默认启动为云台跟随模式*/
    pc.PCMode = Mode_Cloud_PlatformFollowing;
    pc.NowStatus = 1;
}

/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    Whether_Ctrl_ChangeMode
	* @brief   判断Ctrl和Shift两个键位是否按下去
  * @param   None 
  * @author  口无 
  * @Data    2018-11-18
 **/
/* -------------------------------- end -------------------------------- */

void Whether_CtrlANDShift_ChangeMode(void)
{
	/*根据键位改变模式*/
		if(Keyboard_WhetherPressedKey(KEYBOARD_PRESSED_SHIFT,HAVE_MATCH))
		{
			pc.Shift_Open = 1;
		}
		else
		{
			pc.Shift_Open = 0;
		}
		
		if(Keyboard_WhetherPressedKey(KEYBOARD_PRESSED_CTRL,HAVE_MATCH))
		{
			pc.Ctrl_Open = 1;
		}
		else
		{
			pc.Ctrl_Open = 0;
		}
		
		/*没有值*/
		if(DR16.keyBoard.key_code == KEYBOARD_PRESSED_NONE)
		{
			pc.Ctrl_Open = 0;
			pc.Shift_Open = 0;
		}
}


//void Whether_CombineMode()
//{
//	if(Keyboard_WhetherJumpKey(KEYBOARD_PRESSED_SHIFT,FULL_MATCH) || Keyboard_WhetherJumpKey(KEYBOARD_PRESSED_CTRL,FULL_MATCH))
//	{
//		pc.Combine_Open = 1;
//	}
//	else
//	{
//		pc.Combine_Open = 0;
//	}
//}


float speedNow = 0;
void Direction_Dealing(rocker_st *rocker)
{
	
	/*速度大小(之后可以加速度判断调节)*/
	
	if(pc.Ctrl_Open == 1 || MouseKeyRight.key_Status == 1)
	{
		speedNow = Speed_S;
	}
	
	if(pc.Shift_Open == 1)
	{
		speedNow = Speed_F;
	}
	
	if(pc.Shift_Open == 0 && pc.Ctrl_Open == 0)
	{
		speedNow = Speed_N;
	}
	
	/*可以增加速度判断机制(接近可判断的机制)*/
	/*WS方向判断*/
	if(Keyboard_WhetherPressedKey(KEYBOARD_PRESSED_W,HAVE_MATCH))
	{
		rocker->x = speedNow * slope_calculation(&fb_slope);
	}
	else if(Keyboard_WhetherPressedKey(KEYBOARD_PRESSED_S,HAVE_MATCH))
	{
		rocker->x = -speedNow * slope_calculation(&fb_slope);
	}
	else
	{
		rocker->x = 0;
		slope_init(&fb_slope,Slope_ACCTime/10);
	}
	
	/*AD方向判断*/
	if(Keyboard_WhetherPressedKey(KEYBOARD_PRESSED_A,HAVE_MATCH))
	{
		rocker->y = speedNow *slope_calculation(&lr_slope);
	}
	else if(Keyboard_WhetherPressedKey(KEYBOARD_PRESSED_D,HAVE_MATCH))
	{
		rocker->y = -speedNow * slope_calculation(&lr_slope);
	}
	else
	{
		rocker->y = 0;
		slope_init(&lr_slope,Slope_ACCTime/10);
	}
	
	/*QE侧旋判断*/
	float Q_Speed,E_Speed;
	if(Keyboard_WhetherPressedKey(KEYBOARD_PRESSED_Q,HAVE_MATCH))
	{
		Q_Speed= -speedNow;
	}
	if(Keyboard_WhetherPressedKey(KEYBOARD_PRESSED_E,HAVE_MATCH))
	{
		E_Speed = speedNow;
	}
	
	rocker->degrees = Q_Speed + E_Speed;
	
	
	
	
}
