#include "TaskInit.h"

/*��ʼ������*/
TaskHandle_t StartTaskHandler=NULL;


void TaskStart(void *pvParameters)
{
    /*�����ж����ȼ�����*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    
    /*�����ʼ��*/
	LED_Init();
    DR16_Init();
    

    







    /*�����ʼ��*/
    taskENTER_CRITICAL();
    
    /*USART�����ʼ��*/
    USART_TaskCreate();
	


    vTaskDelay(1000);
    /*������������*/



    vTaskDelete(StartTaskHandler);
    taskEXIT_CRITICAL(); 
    
}

