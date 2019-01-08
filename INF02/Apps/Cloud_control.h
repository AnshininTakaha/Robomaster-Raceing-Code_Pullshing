#ifndef __Cloud_control_H
#define __Cloud_control_H

#include "Users.h"

extern Cloud_st Cloud;
extern GY_IMU_t Cloud_IMU;
#define Cloud_LpfAttFactor 0.1f

#define Cloud_Yaw_Min				1850.0f
#define Cloud_Yaw_Max				5950.0f
#define Cloud_Yaw_Center		3895.0f
#define Cloud_Yaw_delta			(Cloud_Yaw_Max - Cloud_Yaw_Min)

#define Cloud_Pitch_Min			2951.0f
#define Cloud_Pitch_Max			4600.0f
#define Cloud_Pitch_Center	4100.0f
#define Cloud_Pitch_delta		(Cloud_Pitch_Max - Cloud_Pitch_Min)

/*M6623角度转换成为弧度*/
#define M6623_AngleToDEG(ang)	ang/22.75f
/***************************funtions*************************/
/*Cloud云台初始化*/
void Cloud_Init(void);
/*强制设置YAW轴的IMU目标值*/
void ForceSetting_YAWIMUCloudpointing(float YAW_setting,float PITCH_setting);
/*强制设置PITCH轴的ABS目标值*/
void ForceSetting_YAWABSCloudpointing(float YAW_Setting,float PITCH_Setting);
/*设定M6623电机PITCH轴的目标值*/
void M6623_setTargetAngle(int id, int32_t angle);
/*云台处理*/
void Double_Cloud_process(float Delta_YAW,float Delta_Ptich,uint8_t switchmode);


/*动态IMU极值点*/
float Get_Cloud_YAWAngle_withCenter(void);
float Get_Cloud_YAWAngle_withLeft(void);
float Get_Cloud_PITCHAngle_withCenter(void);
float Get_Cloud_PITCHAngle_withDown(void);
#endif
