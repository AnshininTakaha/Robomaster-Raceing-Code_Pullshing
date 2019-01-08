#ifndef __Chassis_control
#define __Chassis_control

/*总引导函数*/
#include "Users.h"

/*底盘初始化*/
void Chassis_Init(void);

/*宏定义滤波系数，但是为了理解方便代码里面的宏定义已经被改成了初始定义了*/
#define Chassis_LpfAttFactor 0.098f

/*底盘控制处理*/
void Chassis_processing(float Vx, float Vy, float VOmega, uint8_t mode);

/*麦轮速度模型解算*/
void MecanumCalculation(float Vx, float Vy, float VOmega, int16_t *Speed);

/*电流限制*/
void Chassis_powerLimit(M3508s_t *p_M3508s, float CurrentLimit);


#endif

