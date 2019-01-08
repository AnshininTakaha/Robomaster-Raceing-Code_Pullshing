#ifndef _Chassis_Control_H
#define _Chassis_Control_H

#include "Users.h"

extern Chassis_st Chassis;

#define Fif_Factor 0.04f              //滤波系数

#define Chassis_MaxSpeed_Y	6600.0f		//底盘前后最快速度
#define Chassis_MaxSpeed_X	6600.0f		//底盘平移最快速度
#define Chassis_MaxSpeed_W	6600.0f		//底盘自旋最快速度
/***************************funtions*************************/
/*底盘基本初始化*/
void Chassis_Init(void);
/*底盘处理*/
void Chassis_Process(float Vx,float Vy,float VOmega,uint8_t mode);
/*麦轮解算*/
void MecanumCalculation(float Vx, float Vy, float VOmega, int16_t *Speed);
/*功率限制*/
void Chassis_powerLimit(RM3508_st *p_M3508s, float CurrentLimit);


#endif
