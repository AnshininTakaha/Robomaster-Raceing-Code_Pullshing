/*总数据函数Users.h*/
#ifndef __Users
#define __Users


/*注意，因为是按照顺序读写基本结构体的*/
/*由于typedef里面存在stdint需要用到的结构体，所以需要这样子定义*/



//F4xx基本结构体
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
//注意顺序（由于math里面的额函数和arm_math里面的函数有一定的冲突，所以这里要先定义math函数）
#include <arm_math.h>

/*禁用赋值给电流开关
						1 -> 开
						0 -> 关*/
extern int Classical_ban;
extern int Cloud_and_shooting_ban;
//extern int shooting_ban;


/*循环函数*/
void Begin(void);
void loop(void);
/*调试用的简单延时*/
void delay_100(void);

/*DataScope*/
#include "DataScope_DP.h"
//#include "show.h"

/*共用体&通用函数&Users*/
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
