//#include "stm32f4xx.h"
//#include "led.h"
//#include "delay.h"


//int main(void)
//{
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
//	delay_init(180);
//	LED_Init();	
//  while(1)
//	{
//	}
//}
#include "stdio.h"
#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "math.h"
#include "time.h"
#include "semphr.h"

/*定义一个信号量*/
static SemaphoreHandle_t  xSemaphore = NULL;
/*定义一个信号量返回值*/
portBASE_TYPE xSemaphoreBack;


u8 UsartSendData[3][20] = {"Task1 Send data\r\n",
													 "Task2 Send data\r\n",
													 "Task3 Send data\r\n"};

static QueueHandle_t xQueue = NULL;
QueueHandle_t xMutex;

//重写printf打印函数
void prvNewPrintString(const portCHAR *pcString)
{
	/*试图获取互斥量。获取失败则进入无超时等待*/
	xSemaphoreTake(xMutex,portMAX_DELAY);
	{
		printf("%s",pcString);
	}
	xSemaphoreGive(xMutex);
	
	//vTaskDelay(rand()&0x1FF)
}	
													 
void led0_task(void *pvParameters)
{
	while(1)
	{
		xSemaphoreBack = xSemaphoreTake(xSemaphore,portMAX_DELAY);
		if(xSemaphoreBack == pdFALSE)
		{
			vTaskDelay(200);
			printf("fhduisfhuids\r\n");
		}
		
	}
}

void led1_task(void *pvParameters)
{
	while(1)
	{
		vTaskDelay(200);
		//xSemaphoreGive(xSemaphoreBack);
	}
}

void float_task(void *p_arg)
{
	static float float_num = 0.00;
	while(1)
	{
		float_num += 0.01f;
		printf("float_num的值为：%.4f\r\n",float_num);
		vTaskDelay(1000);
	}
}

//发送数据给终端
void usart_send(char *Pcstring)
{
	char *cdata;
  cdata	= Pcstring;
	
	printf("%s",cdata);
	
}

//数据发送任务
void UsartSendDataTask(void *pvParameters)
{
	char *Pcstring;
	
	Pcstring = (char*)pvParameters;
	
	for(;;)
	{
		usart_send(Pcstring);
		
		vTaskDelay(100);
	}
}

//队列发送任务
void vSendTask(void *pvParameters)
{
	char *Pcstring;
	portBASE_TYPE xStatus;
	
	Pcstring = (char*)pvParameters;
	
	for(;;)
	{
		
		/*往队列发送数据*/
		xStatus = xQueueSendToBack(xQueue,&pvParameters,portMAX_DELAY);
		
		if(xStatus != pdPASS)
		{
			
			printf("Could not send to the queue.\r\n");
			
		}
	}
}

//队列接收函数
void vReceiveTask(void *pvParameters)
{
	portBASE_TYPE xStatus;
	char *Pcstring;
	const portTickType xTicksToWait = 100/portTICK_RATE_MS;
	
	for(;;)
	{
		if(uxQueueMessagesWaiting(xQueue)!=0)
		{
			
			printf("Queue should have been empty!\t\n");
		
		}
		/*从队列中接收数据
		阻塞超时时间为无限超时时间
		*/
		xStatus = xQueueReceive(xQueue,&Pcstring,xTicksToWait);
		if(xStatus == pdPASS)
		{
			
			printf("Receive = %s",Pcstring);
			
		}
		else
		{
			
			printf("Could not receive from the queue.\r\n");
			
		}
	}
}

int main(void)
{
	
	LED_Init();
	
//	LED1=0;
//	LED2=0;
	
//	xMutex = xSemaphoreCreateMutex();
//	
//		//创建队列
//	xQueue = xQueueCreate(3, sizeof(UsartSendData[0]));
//	
//		//创建任务1
//	xTaskCreate(UsartSendDataTask,
//							"Task 1",
//							1000,
//							UsartSendData[0],
//							1,
//							NULL);
//	//创建任务2
//	xTaskCreate(UsartSendDataTask,
//							"Task 2",
//							1000,
//							UsartSendData[1],
//							1,
//							NULL);
//		//创建任务3
//	xTaskCreate(UsartSendDataTask,
//							"Task 3",
//							1000,
//							UsartSendData[2],
//							1,
//							NULL);
  vSemaphoreCreateBinary(xSemaphore);
	//创建任务1
	xTaskCreate(led0_task,
							"Task 1",
							1000,
							NULL,
							1,
							NULL);
	//创建任务2
	xTaskCreate(led1_task,
							"Task 2",
							1000,
							NULL,
							2,
							NULL);
//		//创建任务3
//	xTaskCreate(float_task,
//							"Task 3",
//							1000,
//							NULL,
//							1,
//							NULL);
//	
//	//启动调度器
	vTaskStartScheduler();
	
	while(1)
	{

	}
}







