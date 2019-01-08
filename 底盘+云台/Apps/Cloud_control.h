#ifndef __CLOUD_CONTROL
#define __CLOUD_CONTROL

#include "Users.h"

extern Cloud_t Cloud;

/*��ֵ��ϵ��*/
#define Cloud_Yaw_Min				2800.0f
#define Cloud_Yaw_Max				5000.0f
#define Cloud_Yaw_Center		3900.0f

#define Cloud_Pitch_Min			2951.0f
#define Cloud_Pitch_Max			4600.0f
#define Cloud_Pitch_Center	4225.0f

/*����M6623��M2006�ĵ���ֵ*/
void Cloud_setCurrent(int16_t iqyaw, int16_t iqpitch, int16_t iq7, int16_t iq8);

/*��̨��ʼ��*/
void Cloud_Init(void);

/*��̨����*/
void Cloud_processing(float delta_yaw, float delta_pitch, uint8_t shoot, uint8_t mode);

/*��̨�������*/
float Cloud_getYawOverFlow(void);

/*��ȡ��̨Yaw��ת�Ƕȣ�������Ϊ0�㣩*/
float Cloud_getYawAngle(void);

/**/
#endif