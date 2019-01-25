#ifndef _CLOUDCONTROL_H
#define _CLOUDCONTROL_H

#include "Analysis.h"
#include "PCControl.h"
#include "DR16.h"
#include "IMU.h"

#define Cloud_LpfAttFactor 0.1f

#define Cloud_Yaw_Min				1850.0f
#define Cloud_Yaw_Max				5950.0f
#define Cloud_Yaw_Center		3895.0f
#define Cloud_Yaw_delta			(Cloud_Yaw_Max - Cloud_Yaw_Min)

#define Cloud_Pitch_Min			3900.0f
#define Cloud_Pitch_Max			4650.0f
#define Cloud_Pitch_Center	4100.0f
#define Cloud_Pitch_delta		(Cloud_Pitch_Max - Cloud_Pitch_Min)

#define M6623_AngleToDEG(ang)	ang/22.75f
typedef struct
{
	/*ң��ģʽ����ң����ң��*/
	uint8_t modeswitch;
	
	/*PC�Ŀ���ģʽ*/
//	uint8_t pc_control_CloudMode;
	
	float Filter_LPFfactor;
	float Yaw_Raw;
	float Yaw_LPF;
	
	float Pitch_Raw;
	float Pitch_LPF;
	
	float IMUYaw_Raw;
	float IMUYaw_LPF;
	float IMUPitch_Raw;
	float IMUPitch_LPF;
	
	float IMUYawAngleMax;		//��̨IMU���Ƕ�(��)
	float IMUYawAngleMin;		//��̨IMU��С�Ƕ�(��)
	float IMUPitchAngleMax;		//��̨IMU���Ƕ�(��)
	float IMUPitchAngleMin;		//��̨IMU��С�Ƕ�(��)
	
	positionpid_t YAW_Attitude_pid;
	positionpid_t YAW_Speed_pid;
	
	positionpid_t Roll_Attitude_pid;
	positionpid_t Roll_Speed_pid;
	
	
}Cloud_t;



extern Cloud_t Cloud;


/*��̨��ʼ��*/
void Cloud_Init(void);

/*��̨��ֵ����*/
void Cloud_Judgement(void);

/*��̨����*/
void Double_Cloud_process(float Delta_YAW,float Delta_Ptich,uint8_t switchmode);

/*ǿ��������̨�Ƕ�*/
void ForceSetting_YAWIMUCloudpointing(float YAW_setting,float PITCH_setting);

/*��̨�ǶȻ�ȡ��IMUֵ���㣩*/
float Get_Cloud_YAWAngle_withCenter(void);
float Get_Cloud_YAWAngle_withLeft(void);
float Get_Cloud_PITCHAngle_withCenter(void);
float Get_Cloud_PITCHAngle_withDown(void);

/*����M6623��ֵ*/
void M6623_setTargetAngle(int id, int32_t angle);


#endif

