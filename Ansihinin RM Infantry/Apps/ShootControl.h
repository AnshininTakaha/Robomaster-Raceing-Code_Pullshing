#ifndef _SHOOTCONTROL_H
#define _SHOOTCONTROL_H

#include "stm32f4xx.h"
#include "Analysis.h"
#include "TIM.h"


#define frictionSpeedMax 2000
#define frictionSpeedMin 1000

/*射击限制*/
#define Parting_Speed 100

/*拨弹一圈速度*/
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


/*射击初始化*/
void Shoot_Init(void);

/*摩擦轮速度设定*/
void firction_speedSetting(uint16_t speed);

/*打开摩擦轮*/
void firction_ON(void);

/*关闭摩擦轮*/
void firction_OFF(void);

/*射击处理*/
void Shoot_process(void);



#endif
