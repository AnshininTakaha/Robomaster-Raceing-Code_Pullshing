#ifndef _PID_H
#define _PID_H

#include "stm32f4xx.h"
#include "mathing.h"

/*增量PID*/
typedef struct
{
	float Target_speed;       
	float Measured_speed;
	float error;
	float last_error;
	float beforelast_error;
	float Kp,Ki,Kd;
	float PWM;
	
	float data_u;
	float data_out;
	float data_lastout;
	
	uint32_t MaxOutput;
	uint32_t IntegralLimit;
	
}incrementalpid_t;

/*位置PID*/
typedef struct
{
	float Target;
	float Measured;
	float error;
	float last_error;
	float Add_error;
	float Kp,Ki,Kd;
	float PWM;

	uint32_t MaxOutput;
	uint32_t IntegralLimit;
}positionpid_t;

/*增量式PID初始化*/
void IncrementalPID_Init(incrementalpid_t *pid, float kp, float ki, float kd, uint32_t MaxOutput, uint32_t IntegralLimit);

/*位置式PID初始化*/
void PositionPID_Init(positionpid_t *pid, float kp, float ki, float kd, uint32_t MaxOutput, uint32_t IntegralLimit);

/*增量式PID计算*/
int IncrementalPID_Calculation(incrementalpid_t *pid, float target, float measured);

/*位置式PID计算*/
int PositionPID_Calculation(positionpid_t *pid, float target, float measured);

#endif

