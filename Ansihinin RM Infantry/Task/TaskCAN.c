#include "TaskCAN.h"


/*�������*/
static TaskHandle_t CAN_ReceiveHandler = NULL;/*���̿���������*/

/*�������*/
QueueHandle_t xCan1RxQueue = NULL;

/*�������*/
void CAN1_ReceiveTask(void *pvParameters);

void CAN_TaskCreate()
{
    /*���д���*/
    xCan1RxQueue = xQueueCreate(20,sizeof(CanRxMsg));

    /*���񴴽�*/
    xTaskCreate(CAN1_ReceiveTask,           /* ������  */        
				"CAN_ReceiveTask",         /* ������    */      
				128,       			      /* ����ջ��С*/  
				NULL,                 /* �������  */    
			    4,       			        /* �������ȼ�*/
				&CAN_ReceiveHandler);   /* ������  */


}

void CAN1_ReceiveTask(void *pvParameters)
{
    CanRxMsg RxMessage;
    while(1)
    {
        xQueueReceive(xCan1RxQueue,&RxMessage,portMAX_DELAY);
        Analysis_getinfo(RxMessage);
        
    }
}


