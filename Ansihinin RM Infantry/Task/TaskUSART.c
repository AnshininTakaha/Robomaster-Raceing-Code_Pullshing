#include "TaskUSART.h"

/*�������*/
static TaskHandle_t USART1_ReceiverHandler = NULL;
static TaskHandle_t UASRTSend_xHandler = NULL;
/*�������*/
QueueHandle_t xUsart1RxQueue = NULL;

/*USART1��������*/
void USART1_ReceiveTask(void *pvParameters);

void USART_TaskCreate(void)
{
    xUsart1RxQueue = xQueueCreate(18u+2,(18u+2)*sizeof(uint8_t));

     xTaskCreate(USART1_ReceiveTask,           /* ������  */        
				"USART1_Task",         /* ������    */      
				512,       			      /* ����ջ��С*/  
				NULL,                 /* �������  */    
			    4,       			        /* �������ȼ�*/
				&USART1_ReceiverHandler);   /* ������  */
	
	
                 
}

void USART1_ReceiveTask(void *pvParameters)
{
   uint8_t usart1RxBuffer[20];
   while(1)
   {
        xQueueReceive(xUsart1RxQueue, &usart1RxBuffer,portMAX_DELAY);
        DR16_Process(usart1RxBuffer);
	    GPIO_ToggleBits(GPIOE,GPIO_Pin_9);
        
   }
}



