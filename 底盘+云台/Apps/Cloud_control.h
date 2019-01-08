#ifndef __CLOUD_CONTROL
#define __CLOUD_CONTROL

#include "Users.h"

extern Cloud_t Cloud;

/*极值关系点*/
#define Cloud_Yaw_Min				2800.0f
#define Cloud_Yaw_Max				5000.0f
#define Cloud_Yaw_Center		3900.0f

#define Cloud_Pitch_Min			2951.0f
#define Cloud_Pitch_Max			4600.0f
#define Cloud_Pitch_Center	4225.0f

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

/**/
#endif