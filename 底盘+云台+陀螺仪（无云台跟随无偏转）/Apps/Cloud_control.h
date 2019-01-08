#ifndef __CLOUD_CONTROL
#define __CLOUD_CONTROL

#include "Users.h"

extern Cloud_t Cloud;

/*云台滤波系数*/
#define Cloud_LpfAttFactor 0.1f

/*极值关系点*/
#define Cloud_Yaw_Min				2800.0f
#define Cloud_Yaw_Max				5000.0f
#define Cloud_Yaw_Center		3900.0f
#define Cloud_Yaw_delta			(Cloud_Yaw_Max - Cloud_Yaw_Min)

#define Cloud_Pitch_Min			2951.0f
#define Cloud_Pitch_Max			4600.0f
#define Cloud_Pitch_Center	4225.0f
#define Cloud_Pitch_delta		(Cloud_Pitch_Max - Cloud_Pitch_Min)

/*云台模式*/
#define Cloud_Mode_Normal		0
#define Cloud_Mode_WithIMU		1

/*M6623角度转换成为弧度*/
#define M6623_AngleToDEG(ang)	ang/22.75f

/*获取云台Yaw和Pitch的旋转角度（分别以中间和底下为零点）*/
float Get_Cloud_YAWAngle_withCenter(void);
float Get_Cloud_YAWAngle_withLeft(void);
float Get_Cloud_PITCHAngle_withCenter(void);
float Get_Cloud_PITCHAngle_withDown(void);

/*强制设置IMU坐标*/
void Cloud_setIMUPosForced(float posYaw, float posPitch);

/*强制设置云台机械坐标*/
void Cloud_setAbsPosForced(float posYaw, float posPitch);

/*设置M6623和M2006的电流值*/
void Cloud_setCurrent(int16_t iqyaw, int16_t iqpitch, int16_t iq7, int16_t iq8);

/*云台初始化*/
void Cloud_Init(void);

/*云台处理*/
void Cloud_processing(float delta_yaw, float delta_pitch, uint8_t shoot, uint8_t mode);

/*云台溢出计算*/
float Cloud_getYawOverFlow(void);

/*获取云台Yaw旋转角度（以中心为0点）*/
float Cloud_getYawAngle(void);

/*新云台处理（普通模式）*/
void Cloud_processing_Normal(float delta_yaw, float delta_pitch, uint8_t mode);

/*新云台处理模式（IMU模式）*/
void Cloud_processing_WithIMU(float delta_yaw,float delta_pitch, uint8_t mode);
#endif