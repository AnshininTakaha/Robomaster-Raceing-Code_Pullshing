#ifndef __CLOUD_CONTROL
#define __CLOUD_CONTROL

#include "Users.h"

extern Cloud_t Cloud;

/*��̨�˲�ϵ��*/
#define Cloud_LpfAttFactor 0.1f

/*��ֵ��ϵ��*/
#define Cloud_Yaw_Min				2800.0f
#define Cloud_Yaw_Max				5000.0f
#define Cloud_Yaw_Center		3900.0f
#define Cloud_Yaw_delta			(Cloud_Yaw_Max - Cloud_Yaw_Min)

#define Cloud_Pitch_Min			2951.0f
#define Cloud_Pitch_Max			4600.0f
#define Cloud_Pitch_Center	4225.0f
#define Cloud_Pitch_delta		(Cloud_Pitch_Max - Cloud_Pitch_Min)

/*��̨ģʽ*/
#define Cloud_Mode_Normal		0
#define Cloud_Mode_WithIMU		1

/*M6623�Ƕ�ת����Ϊ����*/
#define M6623_AngleToDEG(ang)	ang/22.75f

/*��ȡ��̨Yaw��Pitch����ת�Ƕȣ��ֱ����м�͵���Ϊ��㣩*/
float Get_Cloud_YAWAngle_withCenter(void);
float Get_Cloud_YAWAngle_withLeft(void);
float Get_Cloud_PITCHAngle_withCenter(void);
float Get_Cloud_PITCHAngle_withDown(void);

/*ǿ������IMU����*/
void Cloud_setIMUPosForced(float posYaw, float posPitch);

/*ǿ��������̨��е����*/
void Cloud_setAbsPosForced(float posYaw, float posPitch);

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

/*����̨������ͨģʽ��*/
void Cloud_processing_Normal(float delta_yaw, float delta_pitch, uint8_t mode);

/*����̨����ģʽ��IMUģʽ��*/
void Cloud_processing_WithIMU(float delta_yaw,float delta_pitch, uint8_t mode);
#endif