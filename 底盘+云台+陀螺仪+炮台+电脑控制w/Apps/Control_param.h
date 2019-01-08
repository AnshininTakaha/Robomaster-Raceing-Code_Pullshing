#ifndef __CONTROL_PARAM_H
#define __CONTROL_PARAM_H

#include "Users.h"

extern ControlStatus_t ControlStatus;

/*初始化模式*/
void ControlMode_paramInit(void);

/*组合键判定*/
void CombinatorialKey_Process(void);

/*获取当前的模式是什么*/
uint8_t Control_getMode(void);

/*获取是否是组合键*/
uint8_t Control_isCombineKey(void);

#endif
