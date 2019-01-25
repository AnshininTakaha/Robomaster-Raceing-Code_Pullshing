#include "TaskControl.h"

/*�������*/
static TaskHandle_t Chassical_ProcessHandler = NULL;/*���̿���������*/
static TaskHandle_t Cloud_ProcessHandler = NULL;/*���̿���������*/
static TaskHandle_t Device_FlashHandler = NULL;/*֡��ˢ�¿��ƺ���*/
static TaskHandle_t LED_LightHandler = NULL;/*��ˮ�ƿ��ƾ��*/
static TaskHandle_t PC_ControlHandler = NULL;/*���԰������ƾ��*/
static TaskHandle_t GM6020_TestHandler = NULL;/*GM6020PID���Ծ��*/
/*�������*/


/*���������*/
void Chassical_Task(void *pvParameters);
void Devices_Task(void *pvParameters);
void LED_LightTask(void *pvParameters);
void Cloud_Task(void *pvParameters);
void PC_ControlTask(void *pvParameters);

void GM6020_TestTask(void *pvParameters);

void Control_TaskCreate()
{
    /*���д���*/
    

    /*���񴴽�*/
	xTaskCreate(LED_LightTask,           /* ������  */        
								"LED_LightTask",         /* ������    */      
								128,       			      /* ����ջ��С*/  
								NULL,                 /* �������  */    
								2,       			        /* �������ȼ�*/
								&LED_LightHandler);   /* ������  */
		
  	xTaskCreate(Chassical_Task,           /* ������  */        
								"Chassical_Task",         /* ������    */      
								128,       			      /* ����ջ��С*/  
								NULL,                 /* �������  */    
								2,       			        /* �������ȼ�*/
								&Chassical_ProcessHandler);   /* ������  */
	
	xTaskCreate(Cloud_Task,           /* ������  */        
								"Cloud_Task",         /* ������    */      
								256,       			      /* ����ջ��С*/  
								NULL,                 /* �������  */    
								2,       			        /* �������ȼ�*/
								&Cloud_ProcessHandler);   /* ������  */

	xTaskCreate(Devices_Task,           /* ������  */        
								"Devices_Task",         /* ������    */      
								128,       			      /* ����ջ��С*/  
								NULL,                 /* �������  */    
								2,       			        /* �������ȼ�*/
								&Device_FlashHandler);   /* ������  */

	xTaskCreate(PC_ControlTask,           /* ������  */        
								"PC_ControlTask",         /* ������    */      
								128,       			      /* ����ջ��С*/  
								NULL,                 /* �������  */    
								3,       			        /* �������ȼ�*/
								&PC_ControlHandler  );   /* ������  */


	
	


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












