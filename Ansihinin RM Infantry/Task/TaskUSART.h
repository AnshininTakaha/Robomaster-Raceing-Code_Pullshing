#ifndef _TASK_USART_H
#define _TASK_USART_H

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "DR16.h"


extern QueueHandle_t xUsart1RxQueue;




/*USART任务建立*/
void USART_TaskCreate(void);








#endif



