/*总数据函数Users.h*/
#ifndef __Users
#define __Users


/*注意，因为是按照顺序读写基本结构体的*/
/*由于typedef里面存在stdint需要用到的结构体，所以需要这样子定义*/

/*开关：
1、开启旧定义
0、开启新定义*/
#define old_control_proment 0

//F4xx基本结构体
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
//注意顺序
#include <arm_math.h>

#include "binary.h"
/*循环函数*/
void loop(void);
/*调试用的简单延时*/
void delay_100(void);

/*DataScope*/
#include "DataScope_DP.h"
//#include "show.h"

/*共用体&通用函数&Users*/
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

/*裁判系统*/
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
