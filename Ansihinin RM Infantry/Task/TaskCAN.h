#ifndef _TASK_CAN_H
#define _TASK_CAN_H

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "Analysis.h"
/*任务相关*/
extern TaskHandle_t CAN_ReceiveHandler;

/*队列相关*/
extern QueueHandle_t xCan1RxQueue ;


/*CAN任务创建*/
void CAN_TaskCreate();







#endif
