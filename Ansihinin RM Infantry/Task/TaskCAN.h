#ifndef _TASK_CAN_H
#define _TASK_CAN_H

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "Analysis.h"
/*�������*/
extern TaskHandle_t CAN_ReceiveHandler;

/*�������*/
extern QueueHandle_t xCan1RxQueue ;


/*CAN���񴴽�*/
void CAN_TaskCreate();







#endif
