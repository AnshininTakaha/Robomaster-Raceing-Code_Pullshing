#ifndef __SHOOT_CONTROL_H_
#define __SHOOT_CONTROL_H_

#include "Users.h"

extern Fire_st Fire;
extern firction_st Firction;
#define frictionSpeedMax 2000
#define frictionSpeedMin 1000
#define DA_ZE		36864
/***************************funtions*************************/
/*射击启动标志位（包括M2006拨弹和摩擦轮）*/
void Shoot_Init(void);
/*摩擦轮速度设置*/
void firction_speedSetting(uint16_t speed);
/*启动摩擦轮*/
void firction_ON(void);
/*关闭摩擦轮*/
void firction_OFF(void);
/*射击初始化*/
void Shoot_process(void);
	
#endif
