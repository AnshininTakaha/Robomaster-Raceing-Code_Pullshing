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





/*����һ���ź���*/
static SemaphoreHandle_t  xSemaphore = NULL;
static SemaphoreHandle_t xCountingSemaphore = NULL;
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
		vTaskStartScheduler();
		//����������ȣ�ע��ֻҪ��ʼ��������ȣ��¼ӽ�����������Զ��ĵ���,ֻ�п����������������ŻῪʼִ��							
}

void start_task(void *pvParameters)
{
	taskENTER_CRITICAL();//�����ٽ�������ֹ�ڴ�������Ĺ����к���������ˢ�µ����ܷ�
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
							
 								
	
	/*����һ����ֵ�ź���*/
	/*���صľ����xSemaphore*/
	vSemaphoreCreateBinary(xSemaphore);

	/*����һ�������ź���*/
	/*���صľ����xCountingSemaphore*/
	xCountingSemaphore = xSemaphoreCreateCounting(10,0);

	vTaskDelete(StartTask_Handler); //ɾ����ʼ����ֻ��ɾ��start_task������ɾ����start_TASK����ʹ�ܵĺ�����,����ɾ��֮�󲻻���ִ�ж�Ӧ�ĺ���						
	taskEXIT_CRITICAL();            //�˳��ٽ���
}

void TASK_ONE(void *pvParameters)
{
	for(;;)
	{
		/*�ź�����ȡ*/

		xSemaphoreBack = xSemaphoreTake(xCountingSemaphore,portMAX_DELAY);
		if(xSemaphoreBack == pdPASS)
		{
			vTaskDelay(200);
			printf("Get the Semaphore!\r\n");
			GPIO_ToggleBits(GPIOE,GPIO_Pin_10);
		}

	}
}

void TASK_TWO(void *pvParameters)
{
	for(;;)
	{
		vTaskDelay(200);
		xSemaphoreGive(xCountingSemaphore);
		
	}
}

void TASK_THREE(void *pvParameters)
{
	for(;;)
	{
		
	}
}
/**********************************************************************/



