#include "TaskInit.h"

/*开始任务句柄*/
TaskHandle_t StartTaskHandler=NULL;


void TaskStart(void *pvParameters)
{
    /*设置中断优先级分组*/
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    
    /*外设初始化*/
    CAN1_QuickInit();
		LED_Init();
		Laser_Init();
    DR16_Init();

	

    /*任务初始化*/
		/*进入临界区*/
    taskENTER_CRITICAL();
    
    /*USART任务初始化*/
    USART_TaskCreate();
	
    /*CAN任务初始化*/
    CAN_TaskCreate();
	
		/*延时启动*/
    vTaskDelay(2000);
		
    /*控制类型任务初始化*/
    Control_TaskCreate();
    


    vTaskDelete(StartTaskHandler);
    taskEXIT_CRITICAL(); 
    
}

