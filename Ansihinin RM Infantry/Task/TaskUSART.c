#include "TaskUSART.h"
extern uint16_t s_U3dataLength;
/*�������*/
static TaskHandle_t USART1_ReceiverHandler = NULL;/*DR16��USART1�����ƾ��*/
static TaskHandle_t USART3_ReceiverHandler = NULL;/*IMU��USART3�����ƾ��*/
// static TaskHandle_t UASRTSend_xHandler = NULL;/*USART���;��*/
/*�������*/
QueueHandle_t xUsart1RxQueue = NULL;
QueueHandle_t xUsart3RxQueue = NULL;
/*USART1��������*/
void USART1_ReceiveTask(void *pvParameters);
void USART3_ReceiveTask(void *pvParameters);

void USART_TaskCreate(void)
{
    /*���д���*/
    xUsart1RxQueue = xQueueCreate(18u+2,(18u+2)*sizeof(uint8_t));
    xUsart3RxQueue = xQueueCreate(GY_IMU_BUFFSIZE,GY_IMU_BUFFSIZE*sizeof(uint8_t));

    /*���񴴽�*/
    xTaskCreate(USART1_ReceiveTask,           /* ������  */        
				"USART1_ReceiveTask",         /* ������    */      
				128,       			      /* ����ջ��С*/  
				NULL,                 /* �������  */    
			    4,       			        /* �������ȼ�*/
				&USART1_ReceiverHandler);   /* ������  */
	
    xTaskCreate(USART3_ReceiveTask,           /* ������  */        
				"USART3_ReceiveTask",         /* ������    */      
				128,       			      /* ����ջ��С*/  
				NULL,                 /* �������  */    
			    4,       			        /* �������ȼ�*/
				&USART3_ReceiverHandler);   /* ������  */
	
                 
}

void USART1_ReceiveTask(void *pvParameters)
{
   uint8_t usart1RxBuffer[20];
   while(1)
   {
        xQueueReceive(xUsart1RxQueue, &usart1RxBuffer,portMAX_DELAY);
        DR16_Process(usart1RxBuffer);
	    GPIO_ToggleBits(GPIOB,GPIO_Pin_5);
        
   }
}

void USART3_ReceiveTask(void *pvParameters)
{
    uint8_t usart3RxBuffer[30];
    while(1)
    {
        xQueueReceive(xUsart3RxQueue, &usart3RxBuffer,portMAX_DELAY);
        GY_IMU_getInfo(usart3RxBuffer,s_U3dataLength,&Cloud_IMU);
        
    }
}



