#include "TaskInit.h"

/*开始任务句柄*/
TaskHandle_t StartTaskHandler=NULL;


void TaskStart(void *pvParameters)
{
    /*设置中断优先级分组*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    
    /*外设初始化*/
	LED_Init();
    DR16_Init();
    

    







    /*任务初始化*/
    taskENTER_CRITICAL();
    
    /*USART任务初始化*/
    USART_TaskCreate();
	


    vTaskDelay(1000);
    /*控制类型任务*/



    vTaskDelete(StartTaskHandler);
    taskEXIT_CRITICAL(); 
    
}

