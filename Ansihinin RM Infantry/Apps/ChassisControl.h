#ifndef _CHASSISCONTROL_H
#define _CHASSISCONTROL_H

#include "stm32f4xx.h"
#include "DR16.h"
#include "PID.h"
#include "Filter.h"
#include "Analysis.h"
#include "CurrentSetting.h"
#include "CloudControl.h"
#include "PCControl.h"

#define Fif_Factor 0.04f              //滤波系数

#define Chassis_MaxSpeed_Y	6600.0f		//底盘前后最快速度
#define Chassis_MaxSpeed_X	6600.0f		//底盘平移最快速度
#define Chassis_MaxSpeed_W	6600.0f		//底盘自旋最快速度

/*底盘储存结构体*/
typedef struct
{
	/*遥控模式，用遥控右遥杆*/
	uint8_t modeswitch;
	
	/*PC的控制模式*/
//	uint8_t pc_control_ChassisMode;

	float Filter_LPFfactor;
	float xLPF;
	float yLPF;
	float zLPF;
	
	positionpid_t Fowllow_Attitude_pid;
	float FollowYawRaw;
	float FollowYawLPF;
	
	/*标志位*/
	uint8_t Power_OverflowFlag;//超功率标志位,这个是在裁判系统里面获取的所以暂时不用
	
}Chassis_t;

extern Chassis_t Chassis;

/*底盘初始化*/
void Chassis_Init(void);
/*底盘赋值*/
void Chassis_Judgement(void);
/*底盘处理*/
void Chassis_Process(float Vx,float Vy,float VOmega,uint8_t switchmode);
/*麦轮解算*/
void MecanumCalculation(float Vx, float Vy, float VOmega, int16_t *Speed);


#endif
