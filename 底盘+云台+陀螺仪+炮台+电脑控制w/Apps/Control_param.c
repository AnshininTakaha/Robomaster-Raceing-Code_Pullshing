/**
  ******************************************************************************
  * @file    Control_param.c
  * @author  Hare
  * @version V1.0
  * @date
  * @brief   控制参数初始化函数接口
  ******************************************************************************
  */

#include "Control_param.h"


ControlStatus_t ControlStatus;

/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    ControlMode_paramInit
  * @brief   初始化车子当前模式
  * @param   None
  * @author  口无 
  * @Data    2018-10-19
 **/
/* -------------------------------- end -------------------------------- */

void ControlMode_paramInit(void)
{
	/*普通模式启动*/ 
	ControlStatus.ControlMode = 0;
}


/**
  * @brief  组合键判断处理 
  * @param  None
  * @retval None
  */
void CombinatorialKey_Process(void)
{
	/*如果一开始先按下了CTRL或者是SHIFT，那么就判断为组合键*/
	if(dr16_keyboard_isJumpKey(KEYBOARD_PRESSED_CTRL, KEY_FULL_MATCH) 
		|| dr16_keyboard_isJumpKey(KEYBOARD_PRESSED_SHIFT, KEY_FULL_MATCH))
	{
		/*组合键的标志位置为1*/
		ControlStatus.isCombineKey = 1;
	}
	/*如果没有按CTRL或者是SHIFT，那就就没有组合键位*/
	if(dr16_keyBorad.KeyStatus == KEYBOARD_PRESSED_NONE)
	{
		ControlStatus.isCombineKey = 0;
	}
}



/**
  * @brief  获取是否是组合键
  * @param  None
  * @retval None
  * @Using 	初始化整体PID信息
  */

uint8_t Control_isCombineKey(void)
{
	return ControlStatus.isCombineKey;
}


/**
  * @brief  获取当前模式是什么
  * @param  None
  * @retval None
  * @Using 	初始化整体PID信息
  */

uint8_t Control_getMode(void)
{
    return ControlStatus.ControlMode;
}
