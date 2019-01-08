#ifndef __USERS_H_
#define __USERS_H_



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
#include "PID.h"
#include "Coordinate.h"
#include "CurrentSetting.h"
/*User*/
#include "stm32f4xx_it.h"

/*Devices*/
#include "DeviceFlash.h"
#include "DR16.h"
/*IMU*/
#include "GY_IMU.h"

/*Drivers*/
#include "LED.h"
#include "CAN.h"
#include "TIM.h"
#include "NVIC.h"
#include "USART.h"
#include "delay.h"
#endif
