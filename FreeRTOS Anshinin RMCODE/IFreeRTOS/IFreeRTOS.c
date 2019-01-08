#include "IFreeRTOS.h"

#include "task.h"
#include "queue.h"
#include "semphr.h"
/**********************************************************************/
/*要发送的的数据*/
uint32_t Value_to_send;
uint32_t Value_to_send02;
uint32_t Value_to_Recivce;

/*合并阻塞和非阻塞任务句柄*/
TaskHandle_t StartTask_Handler;
TaskHandle_t TASK_ONES;
TaskHandle_t TASK_TWOS;
TaskHandle_t TASK_THREES;

/*队列任务句柄*/
/*队列1*/
xQueueHandle QUEUE_ONE;//队列句柄

/*队列状态*/
portBASE_TYPE QUEUE_ONE_SendStatus;//队列状态发送状态
portBASE_TYPE QUEUE_ONE_SendStatus02;//队列状态发送状态
portBASE_TYPE QUEUE_ONE_RecivceStatus;//队列接受状态





/*定义一个信号量*/
static SemaphoreHandle_t  xSemaphore = NULL;
static SemaphoreHandle_t xCountingSemaphore = NULL;
/*定义一个信号量返回值*/
portBASE_TYPE xSemaphoreBack;

void IRTOS_Begin(void)
{
		
		xTaskCreate((TaskFunction_t )start_task,            //任务函数
                (const char*    )"start_task",          //任务名称
                (uint16_t       )128,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )1,       //任务优先级
                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄  
		vTaskStartScheduler();
		//开启任务调度，注意只要开始了任务调度，新加进来的任务会自动的调度,只有开启了任务调度任务才会开始执行							
}

void start_task(void *pvParameters)
{
	taskENTER_CRITICAL();//进入临界区，防止在创建任务的过程中函数的数据刷新导致跑飞
	/*任务*/
	
	
	xTaskCreate((TaskFunction_t )TASK_ONE,            //任务函数
              (const char*    )"TASK_ONE",          //任务名称
              (uint16_t       )128,        //任务堆栈大小
              (void*          )NULL,                 //传递给任务函数的参数
              (UBaseType_t    )1,       //任务优先级
              (TaskHandle_t*  )&TASK_ONES);   //任务句柄
							
	xTaskCreate((TaskFunction_t )TASK_TWO,            //任务函数
              (const char*    )"TASK_TWO",          //任务名称
              (uint16_t       )128,        //任务堆栈大小
              (void*          )NULL,                 //传递给任务函数的参数
              (UBaseType_t    )1,       //任务优先级
              (TaskHandle_t*  )&TASK_TWOS);   //任务句柄
							
 								
	
	/*创建一个二值信号量*/
	/*返回的句柄是xSemaphore*/
	vSemaphoreCreateBinary(xSemaphore);

	/*创建一个计数信号量*/
	/*返回的句柄是xCountingSemaphore*/
	xCountingSemaphore = xSemaphoreCreateCounting(10,0);

	vTaskDelete(StartTask_Handler); //删除初始任务（只会删除start_task，不会删除在start_TASK里面使能的函数）,但是删除之后不会再执行对应的函数						
	taskEXIT_CRITICAL();            //退出临界区
}

void TASK_ONE(void *pvParameters)
{
	for(;;)
	{
		/*信号量读取*/

		xSemaphoreBack = xSemaphoreTake(xCountingSemaphore,portMAX_DELAY);
		if(xSemaphoreBack == pdPASS)
		{
			vTaskDelay(200);
			printf("Get the Semaphore!\r\n");
			GPIO_ToggleBits(GPIOE,GPIO_Pin_10);
		}

	}
}

void TASK_TWO(void *pvParameters)
{
	for(;;)
	{
		vTaskDelay(200);
		xSemaphoreGive(xCountingSemaphore);
		
	}
}

void TASK_THREE(void *pvParameters)
{
	for(;;)
	{
		
	}
}
/**********************************************************************/



