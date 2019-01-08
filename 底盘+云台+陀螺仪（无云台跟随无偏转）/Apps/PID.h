#ifndef __PID_H
#define __PID_H


#include "Users.h"

/*增量式PID计算*/
int Incremental_PID(incrementalpid_t *pid_t, float target, float measured);

/*位置PID*/
void PositionPID_paraReset(positionpid_t *pid_t, float kp, float ki, float kd, uint32_t MaxOutput, uint32_t IntegralLimit);

/*积分限幅*/
void abs_limit(float *a, float ABS_MAX);

/*PID初始赋值*/
void IncrementalPID_paraReset(incrementalpid_t *pid_t, float kp, float ki, float kd, uint32_t MaxOutput, uint32_t IntegralLimit);

/*位置PID计算*/
int Position_PID(positionpid_t *pid_t, float target, float measured);


#endif
