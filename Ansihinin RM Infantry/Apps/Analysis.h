#ifndef _ANALYSIS_H
#define _ANALYSIS_H

#include "stm32f4xx.h"
#include "PID.h"


#define PLATFORM_A_TURN 8192
#define UNDULATION_A_TURN 8192

/*RM3508*/
typedef	struct
{
	/*���������룩����*/
	int16_t realAngle;
	int16_t realSpeed;
	int16_t realCurrent;
	int16_t realTempeture;
	
	/*��ֵ�����������*/
	incrementalpid_t pid_wheel;
	int16_t targetSpeed;
	int16_t targetAngle;
	int16_t outCurrent;
	
	/*֡�ʿ��ƣ��ж��Ƿ����ߣ�*/
	uint8_t UpdateFlag;
	uint16_t UpdateFrame;
	uint8_t OFFLINE_SET;
	
}RM3508_t;

/*RM6623*/
typedef struct
{
	/*���������룩����*/
	int16_t realAngle;
	int16_t realCurrent;
	int16_t feedbackCurrent;
	
	/*��ֵ�����������*/
	positionpid_t pid_speed;		
  positionpid_t pid_angle;
	int32_t totalAngle;
	int16_t turnCount;
	
	int32_t targetAngle;
	int32_t lastAngle;
	int16_t outCurrent;
	
/*֡�ʿ��ƣ��ж��Ƿ����ߣ�*/
	uint8_t UpdateFlag;
	uint16_t UpdateFrame;
	uint8_t OFFLINE_SET;
}RM6623_t;

/*RM2006*/
typedef struct
{
	/*���������룩����*/
	int16_t realAngle;
	int16_t realSpeed;
	int16_t realTorque;
	
	/*��ֵ�����������*/
	positionpid_t pid_speed;		
  positionpid_t pid_angle;
	int32_t totalAngle;
	int16_t turnCount;
	
	int32_t targetSpeed;
	int32_t targetAngle;
	int32_t lastAngle;
	int16_t outCurrent;
	
//	/*֡�ʿ��ƣ��ж��Ƿ����ߣ�*/
		uint8_t UpdateFlag;
		uint16_t UpdateFrame;
		uint8_t OFFLINE_SET;
}RM2006_t;

extern RM3508_t RM3508s[4];
extern RM6623_t RM6623s[2];
extern RM2006_t RM2006s[1];

/*��������������*/
void Analysis_getinfo(CanRxMsg RxMessage);

/*M6623���㴦��*/
void M6623_ZeroDealing_platform(int8_t id);

/*M2006���㴦��*/
void M2006_ZeroDealing_platform(int8_t id);











#endif 

