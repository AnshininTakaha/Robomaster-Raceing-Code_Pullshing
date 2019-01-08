#ifndef __CONTROL_PARAM_H
#define __CONTROL_PARAM_H

#include "Users.h"

extern ControlStatus_t ControlStatus;

/*��ʼ��ģʽ*/
void ControlMode_paramInit(void);

/*��ϼ��ж�*/
void CombinatorialKey_Process(void);

/*��ȡ��ǰ��ģʽ��ʲô*/
uint8_t Control_getMode(void);

/*��ȡ�Ƿ�����ϼ�*/
uint8_t Control_isCombineKey(void);

#endif
