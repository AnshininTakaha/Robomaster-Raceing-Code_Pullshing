#ifndef _SHOOT_H
#define _SHOOT_H

#include "Users.h"

extern shootGun_t Gun;
/*�ṹ�����*/
extern const uint16_t Shoot_HeatMax[4];
extern const uint16_t Shoot_Freq[4];
extern const uint16_t deltaHeat[3];
extern const uint16_t FricSpeed[3];


#define FricSpeedLevel_10MPS 	0
#define FricSpeedLevel_20MPS 	1
#define FricSpeedLevel_30MPS 	2

#define FRICMOTOR_SPEEDMAX		2000
#define FRICMOTOR_SPEEDMIN		1000
/*Ħ����ǹ�ܳ�ʼ��*/
void Shoot_Init(void);

/*���õ���ٶ�*/
void fricMotor_setSpeed(uint16_t speed);

/*��Ħ����*/
void friction_turnOn(void);

/*�ر�Ħ����*/
void friction_turnOff(void);

/*������̴���*/
void Shoot_processing(void);

#endif


