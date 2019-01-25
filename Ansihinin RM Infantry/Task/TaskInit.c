#include "TaskInit.h"

/*��ʼ������*/
TaskHandle_t StartTaskHandler=NULL;


void TaskStart(void *pvParameters)
{
    /*�����ж����ȼ�����*/
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    
    /*�����ٽ���*/
    taskENTER_CRITICAL();

    /*�����ʼ��*/
    CAN1_QuickInit();
		LED_Init();
		Laser_Init();
    DR16_Init();
    PC_MODE_Init();

    IMU_Init();
    vTaskDelay(2000);

    
    Chassis_Init();
    Cloud_Init();
    Shoot_Init();
    

    /*�����ʼ��*/
    /*USART�����ʼ��*/
    USART_TaskCreate();
	
    /*CAN�����ʼ��*/
    CAN_TaskCreate();
	
		/*��ʱ����*/
    vTaskDelay(2000);
		
    /*�������������ʼ��*/
    Control_TaskCreate();
    


    vTaskDelete(StartTaskHandler);
    taskEXIT_CRITICAL(); 
    
}

