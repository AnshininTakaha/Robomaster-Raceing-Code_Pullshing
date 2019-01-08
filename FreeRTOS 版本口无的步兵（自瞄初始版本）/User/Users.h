#ifndef __USERS_H_
#define __USERS_H_

/*支持FreeRTOS*/
#define SYSTEM_SUPPORT_OS 1

#if SYSTEM_SUPPORT_OS
#include "FreeRTOS.h"
#endif

/*是否使用新板子*/
#define New_RM 0

#define Using_Vision 0

/*IFreeRTOS*/
#include "IFreeRTOS.h"

/*F4通用结构体*/
#include "Users.h"
#include "binary.h"
#include "stm32f4xx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <arm_math.h>
#include "core_cm4.h"
#include "structural.h"

/*Apps*/
#include "Filter.h"
#include "Analysis.h"
#include "Chassis_control.h"
#include "Cloud_control.h"
#include "Shoot_control.h"
#include "PID.h"
#include "Coordinate.h"
#include "CurrentSetting.h"
#include "slope.h"
/*User*/
#include "stm32f4xx_it.h"

/*Devices*/
#include "Laser.h"
#include "DeviceFlash.h"
#include "DR16.h"
#include "ControlVision.h"
/*IMU*/
#include "GY_IMU.h"

/*PC_Control*/
#include "PC_control.h"


/*Drivers*/
#include "LED.h"
#include "CAN.h"
#include "TIM.h"
#include "NVIC.h"
#include "USART.h"
#include "delay.h"

#endif
