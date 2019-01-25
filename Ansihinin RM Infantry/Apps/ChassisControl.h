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

#define Fif_Factor 0.04f              //�˲�ϵ��

#define Chassis_MaxSpeed_Y	6600.0f		//����ǰ������ٶ�
#define Chassis_MaxSpeed_X	6600.0f		//����ƽ������ٶ�
#define Chassis_MaxSpeed_W	6600.0f		//������������ٶ�

/*���̴���ṹ��*/
typedef struct
{
	/*ң��ģʽ����ң����ң��*/
	uint8_t modeswitch;
	
	/*PC�Ŀ���ģʽ*/
//	uint8_t pc_control_ChassisMode;

	float Filter_LPFfactor;
	float xLPF;
	float yLPF;
	float zLPF;
	
	positionpid_t Fowllow_Attitude_pid;
	float FollowYawRaw;
	float FollowYawLPF;
	
	/*��־λ*/
	uint8_t Power_OverflowFlag;//�����ʱ�־λ,������ڲ���ϵͳ�����ȡ��������ʱ����
	
}Chassis_t;

extern Chassis_t Chassis;

/*���̳�ʼ��*/
void Chassis_Init(void);
/*���̸�ֵ*/
void Chassis_Judgement(void);
/*���̴���*/
void Chassis_Process(float Vx,float Vy,float VOmega,uint8_t switchmode);
/*���ֽ���*/
void MecanumCalculation(float Vx, float Vy, float VOmega, int16_t *Speed);


#endif
