#ifndef __SHOOT_CONTROL_H_
#define __SHOOT_CONTROL_H_

#include "Users.h"

extern Fire_st Fire;
extern firction_st Firction;
#define frictionSpeedMax 2000
#define frictionSpeedMin 1000
#define DA_ZE		36864
/***************************funtions*************************/
/*���������־λ������M2006������Ħ���֣�*/
void Shoot_Init(void);
/*Ħ�����ٶ�����*/
void firction_speedSetting(uint16_t speed);
/*����Ħ����*/
void firction_ON(void);
/*�ر�Ħ����*/
void firction_OFF(void);
/*�����ʼ��*/
void Shoot_process(void);
	
#endif
