#ifndef __PID_H
#define __PID_H

#include "Users.h"

/***************************funtions*************************/
/*abs绝对值*/
float abs_Calculation(float myabs);
/*KI限幅*/
void Ki_Limiting(float *KI_OUT,float MAXER);
/*输出限幅*/
void Output_Limting(float *Output, float MAXER);
/*增量式PID初始化*/
void IncrementalPID_Init(incrementalpid_st *pid, float kp, float ki, float kd, uint32_t MaxOutput, uint32_t IntegralLimit);
/*位置式PID初始化*/
void PositionPID_Init(positionpid_st *pid, float kp, float ki, float kd, uint32_t MaxOutput, uint32_t IntegralLimit);
/*增量式PID计算*/
int IncrementalPID_Calculation(incrementalpid_st *pid, float target, float measured);
/*位置式PID计算*/
int PositionPID_Calculation(positionpid_st *pid, float target, float measured);



#endif
