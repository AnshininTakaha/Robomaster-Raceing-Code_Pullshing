#ifndef _SHOOT_H
#define _SHOOT_H

#include "Users.h"

extern shootGun_t Gun;
/*结构体调用*/
extern const uint16_t Shoot_HeatMax[4];
extern const uint16_t Shoot_Freq[4];
extern const uint16_t deltaHeat[3];
extern const uint16_t FricSpeed[3];


#define FricSpeedLevel_10MPS 	0
#define FricSpeedLevel_20MPS 	1
#define FricSpeedLevel_30MPS 	2

#define FRICMOTOR_SPEEDMAX		2000
#define FRICMOTOR_SPEEDMIN		1000
/*摩擦轮枪管初始化*/
void Shoot_Init(void);

/*设置电机速度*/
void fricMotor_setSpeed(uint16_t speed);

/*打开摩擦轮*/
void friction_turnOn(void);

/*关闭摩擦轮*/
void friction_turnOff(void);

/*射击过程处理*/
void Shoot_processing(void);

#endif


