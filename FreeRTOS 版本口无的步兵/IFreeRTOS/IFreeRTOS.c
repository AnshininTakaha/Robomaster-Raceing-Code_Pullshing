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



/*队列里面对应的一个数组储存体*/
//static uint32_t QUEUE_ONES;


/*configUSE_IDLE_HOOK 要置为1才可以使用*/

//void vApplicationIdleHook(void)
//{
//	GPIO_ToggleBits(GPIOG,GPIO_Pin_2);
//	printf("IN HOOK");
//}
//Receive_st Receiver;
//static const Send_st send[2] =
//{
//	{"First",100},
//	{"Second",200}
//};

/*定义一个信号量*/
static SemaphoreHandle_t  xSemaphore = NULL;
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
		vTaskStartScheduler();//开启任务调度，注意只要开始了任务调度，新加进来的任务会自动的调度,只有开启了任务调度任务才会开始执行							
}

void start_task(void *pvParameters)
{
	taskENTER_CRITICAL();           //进入临界区，防止在创建任务的过程中函数的数据刷新导致跑飞
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
							
//	xTaskCreate((TaskFunction_t )TASK_THREE,            //任务函数
//              (const char*    )"TASK_THREE",          //任务名称
//              (uint16_t       )128,        //任务堆栈大小
//              (void*          )NULL,                  //传递给任务函数的参数
//              (UBaseType_t    )1,       //任务优先级
//              (TaskHandle_t*  )&TASK_THREES);   //任务句柄  								
	
	/*创建一个信号量*/
	vSemaphoreCreateBinary(xSemaphore);
							
//	QUEUE_ONE = xQueueCreate(20,sizeof(send)); 
//	if(QUEUE_ONE != NULL)
//	{
//		GPIO_ToggleBits(GPIOF,GPIO_Pin_14);		
//	}
	vTaskDelete(StartTask_Handler); //删除初始任务（只会删除start_task，不会删除在start_TASK里面使能的函数）,但是删除之后不会再执行对应的函数						
	taskEXIT_CRITICAL();            //退出临界区
}

void TASK_ONE(void *pvParameters)
{
	for(;;)
	{
		/*信号量读取*/
		xSemaphoreBack = xSemaphoreTake(xSemaphore,portMAX_DELAY);
		if(xSemaphoreBack == pdPASS)
		{
			vTaskDelay(200);
			printf("Get the Semaphore!\r\n");
		}
//		else if(xSemaphoreBack == pdFALSE)
//		{
//			
//		}
		
//		printf("pvParameters：%x\r\n",(unsigned int)pvParameters);//打印地址
//		printf("send[0]：%x\r\n",(unsigned int)send);
		

	}
}

void TASK_TWO(void *pvParameters)
{
	for(;;)
	{
		vTaskDelay(200);
		xSemaphoreGive(xSemaphore);
		
	}
}

void TASK_THREE(void *pvParameters)
{
	for(;;)
	{
		
	}
}
/**********************************************************************/



