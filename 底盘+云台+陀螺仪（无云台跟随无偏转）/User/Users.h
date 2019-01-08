/*�����ݺ���Users.h*/
#ifndef __Users
#define __Users


/*ע�⣬��Ϊ�ǰ���˳���д�����ṹ���*/
/*����typedef�������stdint��Ҫ�õ��Ľṹ�壬������Ҫ�����Ӷ���*/

/*���أ�
1�������ɶ���
0�������¶���*/
#define old_control_proment 0

//F4xx�����ṹ��
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
//ע��˳��
#include <arm_math.h>

#include "binary.h"
/*ѭ������*/
void loop(void);
/*�����õļ���ʱ*/
void delay_100(void);

/*DataScope*/
#include "DataScope_DP.h"
//#include "show.h"

/*������&ͨ�ú���&Users*/
#include "typedef.h"
#include "Users.h"
#include "core_cm4.h"


//Apps
#include "Rocker.h"
#include "Chassis_control.h"
#include "Filter.h"
#include "PID.h"
#include "Control_param.h"
#include "Cloud_control.h"

/*����ϵͳ*/
//#include "MC01_JudgeSystem.h"

//Devices
#include "Motor_M3508.h"
#include "DR16.h"
#include "Motor_M6623.h"
#include "frictionMotor.h"
#include "GY_IMU.h"


//Drivers
#include "LED.h"
#include "CAN.h"
#include "NVIC.h"
#include "USART.h"
#include "TIM.h"
#include "delay.h"
#include "KEY.h"

#endif
