#include "IFreeRTOS.h"

#include "task.h"
#include "queue.h"
#include "semphr.h"
/**********************************************************************/
/*Ҫ���͵ĵ�����*/
uint32_t Value_to_send;
uint32_t Value_to_send02;
uint32_t Value_to_Recivce;

/*�ϲ������ͷ�����������*/
TaskHandle_t StartTask_Handler;
TaskHandle_t TASK_ONES;
TaskHandle_t TASK_TWOS;
TaskHandle_t TASK_THREES;

/*����������*/
/*����1*/
xQueueHandle QUEUE_ONE;//���о��

/*����״̬*/
portBASE_TYPE QUEUE_ONE_SendStatus;//����״̬����״̬
portBASE_TYPE QUEUE_ONE_SendStatus02;//����״̬����״̬
portBASE_TYPE QUEUE_ONE_RecivceStatus;//���н���״̬



/*���������Ӧ��һ�����鴢����*/
//static uint32_t QUEUE_ONES;


/*configUSE_IDLE_HOOK Ҫ��Ϊ1�ſ���ʹ��*/

//void vApplicationIdleHook(void)
//{
//	GPIO_ToggleBits(GPIOG,GPIO_Pin_2);
//	printf("IN HOOK");
//}
//Receive_st Receiver;
//static const Send_st send[2] =
//{
//	{"First",100},
//	{"Second",200}
//};

/*����һ���ź���*/
static SemaphoreHandle_t  xSemaphore = NULL;
/*����һ���ź�������ֵ*/
portBASE_TYPE xSemaphoreBack;

void IRTOS_Begin(void)
{
		
		xTaskCreate((TaskFunction_t )start_task,            //������
                (const char*    )"start_task",          //��������
                (uint16_t       )128,        //�����ջ��С
                (void*          )NULL,                  //���ݸ��������Ĳ���
                (UBaseType_t    )1,       //�������ȼ�
                (TaskHandle_t*  )&StartTask_Handler);   //������  
		vTaskStartScheduler();//����������ȣ�ע��ֻҪ��ʼ��������ȣ��¼ӽ�����������Զ��ĵ���,ֻ�п����������������ŻῪʼִ��							
}

void start_task(void *pvParameters)
{
	taskENTER_CRITICAL();           //�����ٽ�������ֹ�ڴ�������Ĺ����к���������ˢ�µ����ܷ�
	/*����*/
	
	
	xTaskCreate((TaskFunction_t )TASK_ONE,            //������
              (const char*    )"TASK_ONE",          //��������
              (uint16_t       )128,        //�����ջ��С
              (void*          )NULL,                 //���ݸ��������Ĳ���
              (UBaseType_t    )1,       //�������ȼ�
              (TaskHandle_t*  )&TASK_ONES);   //������
							
	xTaskCreate((TaskFunction_t )TASK_TWO,            //������
              (const char*    )"TASK_TWO",          //��������
              (uint16_t       )128,        //�����ջ��С
              (void*          )NULL,                 //���ݸ��������Ĳ���
              (UBaseType_t    )1,       //�������ȼ�
              (TaskHandle_t*  )&TASK_TWOS);   //������
							
//	xTaskCreate((TaskFunction_t )TASK_THREE,            //������
//              (const char*    )"TASK_THREE",          //��������
//              (uint16_t       )128,        //�����ջ��С
//              (void*          )NULL,                  //���ݸ��������Ĳ���
//              (UBaseType_t    )1,       //�������ȼ�
//              (TaskHandle_t*  )&TASK_THREES);   //������  								
	
	/*����һ���ź���*/
	vSemaphoreCreateBinary(xSemaphore);
							
//	QUEUE_ONE = xQueueCreate(20,sizeof(send)); 
//	if(QUEUE_ONE != NULL)
//	{
//		GPIO_ToggleBits(GPIOF,GPIO_Pin_14);		
//	}
	vTaskDelete(StartTask_Handler); //ɾ����ʼ����ֻ��ɾ��start_task������ɾ����start_TASK����ʹ�ܵĺ�����,����ɾ��֮�󲻻���ִ�ж�Ӧ�ĺ���						
	taskEXIT_CRITICAL();            //�˳��ٽ���
}

void TASK_ONE(void *pvParameters)
{
	for(;;)
	{
		/*�ź�����ȡ*/
		xSemaphoreBack = xSemaphoreTake(xSemaphore,portMAX_DELAY);
		if(xSemaphoreBack == pdPASS)
		{
			vTaskDelay(200);
			printf("Get the Semaphore!\r\n");
		}
//		else if(xSemaphoreBack == pdFALSE)
//		{
//			
//		}
		
//		printf("pvParameters��%x\r\n",(unsigned int)pvParameters);//��ӡ��ַ
//		printf("send[0]��%x\r\n",(unsigned int)send);
		

	}
}

void TASK_TWO(void *pvParameters)
{
	for(;;)
	{
		vTaskDelay(200);
		xSemaphoreGive(xSemaphore);
		
	}
}

void TASK_THREE(void *pvParameters)
{
	for(;;)
	{
		
	}
}
/**********************************************************************/



