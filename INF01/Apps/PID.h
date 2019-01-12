#ifndef __PID_H
#define __PID_H

#include "Users.h"

/***************************funtions*************************/
/*abs����ֵ*/
float abs_Calculation(float myabs);
/*KI�޷�*/
void Ki_Limiting(float *KI_OUT,float MAXER);
/*����޷�*/
void Output_Limting(float *Output, float MAXER);
/*����ʽPID��ʼ��*/
void IncrementalPID_Init(incrementalpid_st *pid, float kp, float ki, float kd, uint32_t MaxOutput, uint32_t IntegralLimit);
/*λ��ʽPID��ʼ��*/
void PositionPID_Init(positionpid_st *pid, float kp, float ki, float kd, uint32_t MaxOutput, uint32_t IntegralLimit);
/*����ʽPID����*/
int IncrementalPID_Calculation(incrementalpid_st *pid, float target, float measured);
/*λ��ʽPID����*/
int PositionPID_Calculation(positionpid_st *pid, float target, float measured);



#endif
