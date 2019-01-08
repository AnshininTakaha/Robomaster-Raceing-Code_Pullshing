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

/*M6623�Ƕ�ת����Ϊ����*/
#define M6623_AngleToDEG(ang)	ang/22.75f
/***************************funtions*************************/
/*Cloud��̨��ʼ��*/
void Cloud_Init(void);
/*ǿ������YAW���IMUĿ��ֵ*/
void ForceSetting_YAWIMUCloudpointing(float YAW_setting,float PITCH_setting);
/*ǿ������PITCH���ABSĿ��ֵ*/
void ForceSetting_YAWABSCloudpointing(float YAW_Setting,float PITCH_Setting);
/*�趨M6623���PITCH���Ŀ��ֵ*/
void M6623_setTargetAngle(int id, int32_t angle);
/*��̨����*/
void Double_Cloud_process(float Delta_YAW,float Delta_Ptich,uint8_t switchmode);


/*��̬IMU��ֵ��*/
float Get_Cloud_YAWAngle_withCenter(void);
float Get_Cloud_YAWAngle_withLeft(void);
float Get_Cloud_PITCHAngle_withCenter(void);
float Get_Cloud_PITCHAngle_withDown(void);
#endif
