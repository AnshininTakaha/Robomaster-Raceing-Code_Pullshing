#ifndef _TASKINIT_H
#define _TASKINIT_H


#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "TaskUSART.h"
#include "TaskCAN.h"
#include "TaskControl.h"

#include "PCControl.h"
#include "ChassisControl.h"
#include "CloudControl.h"

#include "CAN.h"
#include "LED.h"
#include "NVIC.h"
#include "USART.h"
#include "TIM.h"
#include "Laser.h"


/*开始任务句柄*/
extern TaskHandle_t StartTaskHandler;

/*FreeRTOS*/
/*任务开始函数*/
void TaskStart(void *pvParameters);











#endif
