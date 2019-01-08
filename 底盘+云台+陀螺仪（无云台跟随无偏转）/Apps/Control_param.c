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
