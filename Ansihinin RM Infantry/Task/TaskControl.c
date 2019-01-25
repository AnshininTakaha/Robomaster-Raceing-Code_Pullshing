#include "TaskControl.h"

/*任务相关*/
static TaskHandle_t Chassical_ProcessHandler = NULL;/*底盘控制任务句柄*/
static TaskHandle_t Cloud_ProcessHandler = NULL;/*底盘控制任务句柄*/
static TaskHandle_t Device_FlashHandler = NULL;/*帧率刷新控制函数*/
static TaskHandle_t LED_LightHandler = NULL;/*流水灯控制句柄*/
static TaskHandle_t PC_ControlHandler = NULL;/*电脑按键控制句柄*/
static TaskHandle_t GM6020_TestHandler = NULL;/*GM6020PID测试句柄*/
/*队列相关*/


/*任务函数相关*/
void Chassical_Task(void *pvParameters);
void Devices_Task(void *pvParameters);
void LED_LightTask(void *pvParameters);
void Cloud_Task(void *pvParameters);
void PC_ControlTask(void *pvParameters);

void GM6020_TestTask(void *pvParameters);

void Control_TaskCreate()
{
    /*队列创建*/
    

    /*任务创建*/
	xTaskCreate(LED_LightTask,           /* 任务函数  */        
								"LED_LightTask",         /* 任务名    */      
								128,       			      /* 任务栈大小*/  
								NULL,                 /* 任务参数  */    
								2,       			        /* 任务优先级*/
								&LED_LightHandler);   /* 任务句柄  */
		
  	xTaskCreate(Chassical_Task,           /* 任务函数  */        
								"Chassical_Task",         /* 任务名    */      
								128,       			      /* 任务栈大小*/  
								NULL,                 /* 任务参数  */    
								2,       			        /* 任务优先级*/
								&Chassical_ProcessHandler);   /* 任务句柄  */
	
	xTaskCreate(Cloud_Task,           /* 任务函数  */        
								"Cloud_Task",         /* 任务名    */      
								256,       			      /* 任务栈大小*/  
								NULL,                 /* 任务参数  */    
								2,       			        /* 任务优先级*/
								&Cloud_ProcessHandler);   /* 任务句柄  */

	xTaskCreate(Devices_Task,           /* 任务函数  */        
								"Devices_Task",         /* 任务名    */      
								128,       			      /* 任务栈大小*/  
								NULL,                 /* 任务参数  */    
								2,       			        /* 任务优先级*/
								&Device_FlashHandler);   /* 任务句柄  */

	xTaskCreate(PC_ControlTask,           /* 任务函数  */        
								"PC_ControlTask",         /* 任务名    */      
								128,       			      /* 任务栈大小*/  
								NULL,                 /* 任务参数  */    
								3,       			        /* 任务优先级*/
								&PC_ControlHandler  );   /* 任务句柄  */


	
	


}

void LED_LightTask(void *pvParameters)
{
	portTickType CurrentControlTick = 0;
	while(1)
	{	
		
		GPIO_ToggleBits(GPIOE,GPIO_Pin_9);
		vTaskDelayUntil(&CurrentControlTick,5 / portTICK_RATE_MS);
		GPIO_ToggleBits(GPIOE,GPIO_Pin_10);
		vTaskDelayUntil(&CurrentControlTick,10 / portTICK_RATE_MS);
		GPIO_ToggleBits(GPIOE,GPIO_Pin_11);
		vTaskDelayUntil(&CurrentControlTick,15 / portTICK_RATE_MS);
		GPIO_ToggleBits(GPIOE,GPIO_Pin_12);
		vTaskDelayUntil(&CurrentControlTick,20 / portTICK_RATE_MS);
		GPIO_ToggleBits(GPIOE,GPIO_Pin_13);
		vTaskDelayUntil(&CurrentControlTick,25 / portTICK_RATE_MS);
		GPIO_ToggleBits(GPIOE,GPIO_Pin_14);
		vTaskDelayUntil(&CurrentControlTick,30 / portTICK_RATE_MS);
		GPIO_ToggleBits(GPIOE,GPIO_Pin_15);
	}
}



void Chassical_Task(void *pvParameters)
{
	portTickType CurrentControlTick = 0;
	while(1)
	{
		Chassis_Judgement();
		vTaskDelayUntil(&CurrentControlTick,10 / portTICK_RATE_MS);
	}
}	

void Cloud_Task(void *pvParameters)
{
	portTickType CurrentControlTick = 0;
	while(1)
	{
		Cloud_Judgement();
		vTaskDelayUntil(&CurrentControlTick,10 / portTICK_RATE_MS);
	}
}

void Devices_Task(void *pvParameters)
{
	portTickType CurrentControlTick = 0;
	while(1)
	{
		DevicesFlash();
		vTaskDelayUntil(&CurrentControlTick,200 / portTICK_RATE_MS);
	}
}

void PC_ControlTask(void *pvParameters)
{
	portTickType CurrentControlTick = 0;
	while(1)
	{
		vTaskDelayUntil(&CurrentControlTick,10 / portTICK_RATE_MS);
	}
}












