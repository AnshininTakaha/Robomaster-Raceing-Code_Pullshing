#include "TaskCAN.h"


/*任务相关*/
static TaskHandle_t CAN_ReceiveHandler = NULL;/*底盘控制任务句柄*/

/*队列相关*/
QueueHandle_t xCan1RxQueue = NULL;

/*任务相关*/
void CAN1_ReceiveTask(void *pvParameters);

void CAN_TaskCreate()
{
    /*队列创建*/
    xCan1RxQueue = xQueueCreate(20,sizeof(CanRxMsg));

    /*任务创建*/
    xTaskCreate(CAN1_ReceiveTask,           /* 任务函数  */        
				"CAN_ReceiveTask",         /* 任务名    */      
				128,       			      /* 任务栈大小*/  
				NULL,                 /* 任务参数  */    
			    4,       			        /* 任务优先级*/
				&CAN_ReceiveHandler);   /* 任务句柄  */


}

void CAN1_ReceiveTask(void *pvParameters)
{
    CanRxMsg RxMessage;
    while(1)
    {
        xQueueReceive(xCan1RxQueue,&RxMessage,portMAX_DELAY);
        Analysis_getinfo(RxMessage);
        
    }
}


