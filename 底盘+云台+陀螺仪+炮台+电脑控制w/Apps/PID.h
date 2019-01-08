#ifndef __PID_H
#define __PID_H


#include "Users.h"

/*����ʽPID����*/
int Incremental_PID(incrementalpid_t *pid_t, float target, float measured);

/*λ��PID*/
void PositionPID_paraReset(positionpid_t *pid_t, float kp, float ki, float kd, uint32_t MaxOutput, uint32_t IntegralLimit);

/*�����޷�*/
void abs_limit(float *a, float ABS_MAX);

/*PID��ʼ��ֵ*/
void IncrementalPID_paraReset(incrementalpid_t *pid_t, float kp, float ki, float kd, uint32_t MaxOutput, uint32_t IntegralLimit);

/*λ��PID����*/
int Position_PID(positionpid_t *pid_t, float target, float measured);


#endif
