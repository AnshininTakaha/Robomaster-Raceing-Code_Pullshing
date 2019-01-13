#ifndef _TASKINIT_H
#define _TASKINIT_H


#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "TaskUSART.h"

#include "CAN.h"
#include "LED.h"
#include "NVIC.h"
#include "USART.h"
#include "TIM.h"
#include "Laser.h"


/*��ʼ������*/
extern TaskHandle_t StartTaskHandler;

/*FreeRTOS*/
/*����ʼ����*/
void TaskStart(void *pvParameters);











#endif
