#ifndef _PID_H
#define _PID_H

#include "stm32f4xx.h"
#include "mathing.h"

/*����PID*/
typedef struct
{
	float Target_speed;       
	float Measured_speed;
	float error;
	float last_error;
	float beforelast_error;
	float ec_error; /*���仯��*/ 
	float Kp,Ki,Kd;
	float PWM;
	
	float data_u;
	float data_out;
	float data_lastout;
	
	uint32_t MaxOutput;
	uint32_t IntegralLimit;
	
}incrementalpid_t;

/*λ��PID*/
typedef struct
{
	float Target;
	float Measured;
	float error;
	float last_error;
	float Add_error;
	float ec_error; /*���仯��*/ 
	float Kp,Ki,Kd;
	float PWM;

	uint32_t MaxOutput;
	uint32_t IntegralLimit;
}positionpid_t;


/*����ʽPID��ʼ��*/
void IncrementalPID_Init(incrementalpid_t *pid, float kp, float ki, float kd, uint32_t MaxOutput, uint32_t IntegralLimit);

/*λ��ʽPID��ʼ��*/
void PositionPID_Init(positionpid_t *pid, float kp, float ki, float kd, uint32_t MaxOutput, uint32_t IntegralLimit);

/*����ʽPID����*/
int IncrementalPID_Calculation(incrementalpid_t *pid, float target, float measured);

/*λ��ʽPID����*/
int PositionPID_Calculation(positionpid_t *pid, float target, float measured);

/*ģ������ʽPID����*/
int FuzzyPID_IncCalculation(incrementalpid_t *pid,float target, float measured);

/*ģ��λ��ʽPID����*/
int FuzzyPID_PosCalculation(positionpid_t *pid,float target, float measured);


/*Kpģ��ֵ�Ƶ�*/
float fuzzy_kp(float e, float ec);

/*Kiģ��ֵ�Ƶ�*/
float fuzzy_ki(float e, float ec);

/*Kdģ��ֵ�Ƶ�*/
float fuzzy_kd(float e, float ec);

#endif

