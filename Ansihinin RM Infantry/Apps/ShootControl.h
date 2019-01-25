#ifndef _SHOOTCONTROL_H
#define _SHOOTCONTROL_H

#include "stm32f4xx.h"
#include "Analysis.h"
#include "TIM.h"


#define frictionSpeedMax 2000
#define frictionSpeedMin 1000

/*�������*/
#define Parting_Speed 100

/*����һȦ�ٶ�*/
#define DA_ZE		36864

typedef struct
{
	uint16_t Fire_ready;
	uint16_t Fire_shoot_Flag;
	uint16_t Fire_out_number;
	uint16_t loading_finish;
}Fire_st;

typedef struct
{
	uint16_t firction_ready;
	uint16_t firctionspeed_Raw;
	
}firction_st;


/*�����ʼ��*/
void Shoot_Init(void);

/*Ħ�����ٶ��趨*/
void firction_speedSetting(uint16_t speed);

/*��Ħ����*/
void firction_ON(void);

/*�ر�Ħ����*/
void firction_OFF(void);

/*�������*/
void Shoot_process(void);



#endif
