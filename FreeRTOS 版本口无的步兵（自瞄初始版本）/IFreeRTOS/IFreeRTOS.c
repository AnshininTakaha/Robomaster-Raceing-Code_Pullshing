#include "IFreeRTOS.h"
#include "task.h"
/**********************************************************************/
/*合并阻塞和非阻塞任务*/

TaskHandle_t StartTask_Handler;
TaskHandle_t LED_RED_Handler;
TaskHandle_t LED_GREAN_Handler;
TaskHandle_t LASER_Handler;

/*configUSE_IDLE_HOOK 要置为1才可以使用*/
void vApplicationIdleHook(void)
{
	GPIO_ToggleBits(GPIOG,GPIO_Pin_2);
	printf("IN HOOK");
}

void IRTOS_Begin(void)
{
		xTaskCreate((TaskFunction_t )start_task,            //任务函数
                (const char*    )"start_task",          //任务名称
                (uint16_t       )128,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )1,       //任务优先级
                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄  
		vTaskStartScheduler();//开启任务调度 								
}

void start_task(void *pvParameters)
{
	taskENTER_CRITICAL();           //进入临界区
	xTaskCreate((TaskFunction_t )LED_RED,            //任务函数
              (const char*    )"LED_RED",          //任务名称
              (uint16_t       )128,        //任务堆栈大小
              (void*          )NULL,                  //传递给任务函数的参数
              (UBaseType_t    )2,       //任务优先级
              (TaskHandle_t*  )&LED_RED_Handler);   //任务句柄  
							
//	xTaskCreate((TaskFunction_t )LED_GREAN,            //任务函数
//              (const char*    )"LED_GREAN",          //任务名称
//              (uint16_t       )128,        //任务堆栈大小
//              (void*          )NULL,                  //传递给任务函数的参数
//              (UBaseType_t    )1,       //任务优先级
//              (TaskHandle_t*  )&LED_GREAN_Handler);   //任务句柄  
	
//	xTaskCreate((TaskFunction_t )LASER_SET,            //任务函数
//              (const char*    )"LASER_TOGGLE",          //任务名称
//              (uint16_t       )128,        //任务堆栈大小
//              (void*          )NULL,                  //传递给任务函数的参数
//              (UBaseType_t    )2,       //任务优先级
//              (TaskHandle_t*  )&LASER_Handler);   //任务句柄  
	vTaskDelete(StartTask_Handler); //删除初始任务（只会删除start_task，不会删除在start_TASK里面使能的函数）						
	taskEXIT_CRITICAL();            //退出临界区
}

void LED_RED(void *pvParameters)
{
	
	for(;;)
	{
		/*备用任务1*/
		printf("xTask01 is running!\r\n\n");
		xTaskCreate((TaskFunction_t )LED_GREAN,            //任务函数
              (const char*    )"LED_GREAN",          //任务名称
              (uint16_t       )128,        //任务堆栈大小
              (void*          )NULL,                  //传递给任务函数的参数
              (UBaseType_t    )1,       //任务优先级
              (TaskHandle_t*  )&LED_GREAN_Handler);   //任务句柄
		/*NULL意味着改变自己的优先级*/
		

	}
}

void LED_GREAN(void *pvParameters)
{
	for(;;)
	{
		printf("Set over!\r\n\n");
		printf("Turn again!\r\n\n");
		vTaskPrioritySet(LED_GREAN_Handler,1);
	}
}

void LASER_SET(void *pvParameters)
{
	for(;;)
	{
		/*备用任务3*/
	}
}
/**********************************************************************/



