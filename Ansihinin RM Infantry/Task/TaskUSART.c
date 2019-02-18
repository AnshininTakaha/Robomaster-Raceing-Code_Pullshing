#include "TaskUSART.h"
extern uint16_t s_U3dataLength;
extern uint16_t s_U6dataLength;
/*�������*/
static TaskHandle_t USART1_ReceiverHandler = NULL;/*DR16��USART1�����ƾ��*/
static TaskHandle_t USART6_ReceiverHandler = NULL;/*IMU��USART6�����ƾ��*/
// static TaskHandle_t UASRTSend_xHandler = NULL;/*USART���;��*/
/*�������*/
QueueHandle_t xUsart1RxQueue = NULL;
QueueHandle_t xUsart3RxQueue = NULL;
QueueHandle_t xUsart6RxQueue = NULL;
/*USART1��������*/
void USART1_ReceiveTask(void *pvParameters);

void USART6_ReceiveTask(void *pvParameters);

void USART_TaskCreate(void)
{
    /*���д���*/
    xUsart1RxQueue = xQueueCreate(18u+2,(18u+2)*sizeof(uint8_t));
    xUsart6RxQueue = xQueueCreate(GY_IMU_BUFFSIZE,GY_IMU_BUFFSIZE*sizeof(uint8_t));

    /*���񴴽�*/
    xTaskCreate(USART1_ReceiveTask,           /* ������  */        
				"USART1_ReceiveTask",         /* ������    */      
				128,       			      /* ����ջ��С*/  
				NULL,                 /* �������  */    
			    4,       			        /* �������ȼ�*/
				&USART1_ReceiverHandler);   /* ������  */
	
		xTaskCreate(USART6_ReceiveTask,           /* ������  */        
				"USART6_ReceiveTask",         /* ������    */      
				128,       			      /* ����ջ��С*/  
				NULL,                 /* �������  */    
			    4,       			        /* �������ȼ�*/
				&USART6_ReceiverHandler);   /* ������  */
	 
                 
}

void USART1_ReceiveTask(void *pvParameters)
{
   uint8_t usart1RxBuffer[20];
   while(1)
   {
        xQueueReceive(xUsart1RxQueue, &usart1RxBuffer, portMAX_DELAY);
        DR16_Process(usart1RxBuffer);
		GPIO_ToggleBits(GPIOB,GPIO_Pin_5);
        
   }
}

void USART6_ReceiveTask(void *pvParameters)
{
	uint8_t usart6RxBuffer[30];
	while(1)
	{
		xQueueReceive(xUsart6RxQueue,&usart6RxBuffer,portMAX_DELAY);
		GY_IMU_getInfo(usart6RxBuffer,s_U6dataLength,&Cloud_IMU);
		GPIO_ToggleBits(GPIOB,GPIO_Pin_4);
	}
}



