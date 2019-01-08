#ifndef __Chassis_control
#define __Chassis_control

/*����������*/
#include "Users.h"

/*���̳�ʼ��*/
void Chassis_Init(void);

/*�궨���˲�ϵ��������Ϊ����ⷽ���������ĺ궨���Ѿ����ĳ��˳�ʼ������*/
#define Chassis_LpfAttFactor 0.098f

/*���̿��ƴ���*/
void Chassis_processing(float Vx, float Vy, float VOmega, uint8_t mode);

/*�����ٶ�ģ�ͽ���*/
void MecanumCalculation(float Vx, float Vy, float VOmega, int16_t *Speed);

/*��������*/
void Chassis_powerLimit(M3508s_t *p_M3508s, float CurrentLimit);


#endif

