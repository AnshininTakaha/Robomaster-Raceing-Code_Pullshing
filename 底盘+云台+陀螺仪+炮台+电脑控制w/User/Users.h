/*�����ݺ���Users.h*/
#ifndef __Users
#define __Users


/*ע�⣬��Ϊ�ǰ���˳���д�����ṹ���*/
/*����typedef�������stdint��Ҫ�õ��Ľṹ�壬������Ҫ�����Ӷ���*/



//F4xx�����ṹ��
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
//ע��˳������math����Ķ����arm_math����ĺ�����һ���ĳ�ͻ����������Ҫ�ȶ���math������
#include <arm_math.h>

/*���ø�ֵ����������
						1 -> ��
						0 -> ��*/
extern int Classical_ban;
extern int Cloud_and_shooting_ban;
//extern int shooting_ban;


/*ѭ������*/
void Begin(void);
void loop(void);
/*�����õļ���ʱ*/
void delay_100(void);

/*DataScope*/
#include "DataScope_DP.h"
//#include "show.h"

/*������&ͨ�ú���&Users*/
#include "binary.h"
#include "typedef.h"
#include "Users.h"
#include "core_cm4.h"

#include "delay.h"
#include "NVIC.h"
#include "USART.h"
#include "CAN.h"
#include "TIM.h"
#include "LED.h"
#include "KEY.h"
#include "Laser.h"
#include "Motor_M3508.h"
#include "Motor_M6623.h"
#include "Motor_M2006.h"
#include "frictionMotor.h"
#include "DR16.h"
#include "GY_IMU.h"
#include "Filter.h"
#include "PID.h"
#include "Control_param.h"
#include "Rocker.h"
#include "Chassis_control.h"
#include "Cloud_control.h"
#include "Devices_refresh.h"


#include "shoot.h"
#include "slope.h"
#include "PC_processing.h"


//#include "MC01_JudgeSystem.h"

//Devices
















#endif
