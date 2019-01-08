#ifndef _Chassis_Control_H
#define _Chassis_Control_H

#include "Users.h"

extern Chassis_st Chassis;

#define Fif_Factor 0.04f              //�˲�ϵ��

#define Chassis_MaxSpeed_Y	6600.0f		//����ǰ������ٶ�
#define Chassis_MaxSpeed_X	6600.0f		//����ƽ������ٶ�
#define Chassis_MaxSpeed_W	6600.0f		//������������ٶ�
/***************************funtions*************************/
/*���̻�����ʼ��*/
void Chassis_Init(void);
/*���̴���*/
void Chassis_Process(float Vx,float Vy,float VOmega,uint8_t mode);
/*���ֽ���*/
void MecanumCalculation(float Vx, float Vy, float VOmega, int16_t *Speed);
/*��������*/
void Chassis_powerLimit(RM3508_st *p_M3508s, float CurrentLimit);


#endif
