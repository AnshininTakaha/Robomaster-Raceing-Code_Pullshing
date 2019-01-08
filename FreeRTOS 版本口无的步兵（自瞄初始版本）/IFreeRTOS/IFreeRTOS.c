#include "IFreeRTOS.h"
#include "task.h"
/**********************************************************************/
/*�ϲ������ͷ���������*/

TaskHandle_t StartTask_Handler;
TaskHandle_t LED_RED_Handler;
TaskHandle_t LED_GREAN_Handler;
TaskHandle_t LASER_Handler;

/*configUSE_IDLE_HOOK Ҫ��Ϊ1�ſ���ʹ��*/
void vApplicationIdleHook(void)
{
	GPIO_ToggleBits(GPIOG,GPIO_Pin_2);
	printf("IN HOOK");
}

void IRTOS_Begin(void)
{
		xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )128,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )1,       //�������ȼ�
                (TaskHandle_t*  )&StartTask_Handler);   //������  
		vTaskStartScheduler();//����������� 								
}

void start_task(void *pvParameters)
{
	taskENTER_CRITICAL();           //�����ٽ���
	xTaskCreate((TaskFunction_t )LED_RED,            //������
              (const char*    )"LED_RED",          //��������
              (uint16_t       )128,        //�����ջ��С
              (void*          )NULL,                  //���ݸ��������Ĳ���
              (UBaseType_t    )2,       //�������ȼ�
              (TaskHandle_t*  )&LED_RED_Handler);   //������  
							
//	xTaskCreate((TaskFunction_t )LED_GREAN,            //������
//              (const char*    )"LED_GREAN",          //��������
//              (uint16_t       )128,        //�����ջ��С
//              (void*          )NULL,                  //���ݸ��������Ĳ���
//              (UBaseType_t    )1,       //�������ȼ�
//              (TaskHandle_t*  )&LED_GREAN_Handler);   //������  
	
//	xTaskCreate((TaskFunction_t )LASER_SET,            //������
//              (const char*    )"LASER_TOGGLE",          //��������
//              (uint16_t       )128,        //�����ջ��С
//              (void*          )NULL,                  //���ݸ��������Ĳ���
//              (UBaseType_t    )2,       //�������ȼ�
//              (TaskHandle_t*  )&LASER_Handler);   //������  
	vTaskDelete(StartTask_Handler); //ɾ����ʼ����ֻ��ɾ��start_task������ɾ����start_TASK����ʹ�ܵĺ�����						
	taskEXIT_CRITICAL();            //�˳��ٽ���
}

void LED_RED(void *pvParameters)
{
	
	for(;;)
	{
		/*��������1*/
		printf("xTask01 is running!\r\n\n");
		xTaskCreate((TaskFunction_t )LED_GREAN,            //������
              (const char*    )"LED_GREAN",          //��������
              (uint16_t       )128,        //�����ջ��С
              (void*          )NULL,                  //���ݸ��������Ĳ���
              (UBaseType_t    )1,       //�������ȼ�
              (TaskHandle_t*  )&LED_GREAN_Handler);   //������
		/*NULL��ζ�Ÿı��Լ������ȼ�*/
		

	}
}

void LED_GREAN(void *pvParameters)
{
	for(;;)
	{
		printf("Set over!\r\n\n");
		printf("Turn again!\r\n\n");
		vTaskPrioritySet(LED_GREAN_Handler,1);
	}
}

void LASER_SET(void *pvParameters)
{
	for(;;)
	{
		/*��������3*/
	}
}
/**********************************************************************/



