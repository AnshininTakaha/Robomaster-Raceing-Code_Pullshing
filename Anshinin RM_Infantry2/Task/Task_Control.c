/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,����,                     |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | ��������ѧ����ѧԺ������Ұ�Ƕ�)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : Task_Control.c                                              
  |--Version     : v1.0                                                          
  |--Author      : ����                                                     
  |--Date        : 2019-02-20             
  |--Libsupports : 
  |--Description :                                                     
  |--FunctionList                                                     
  |-------1. ....                                                     
  |          <version>:                                                     
  |     <modify staff>:                                                       
  |             <data>:                                                       
  |      <description>:                                                        
  |-------2. ...                                                       
  |-----------------------------declaration of end-----------------------------|
 **/
#include "Task_Control.h" 
    
/*-----------------------------------file of end------------------------------*/

/* =========================== DeviceFlash of begin =========================== */
/*֡��ˢ�¿��ƾ��*/
static TaskHandle_t Device_FlashHandler = NULL;
/* =========================== DeviceFlash of end =========================== */


/**
  * @Data    2019-02-20 19:46
  * @brief   �������񴴽�
  * @param   void
  * @retval  void
  */
void Control_TaskCreate(void)
{
    xTaskCreate(Devices_Task,           /* ������  */        
				"Devices_Task",         /* ������    */      
				128,       			      /* ����ջ��С*/  
				NULL,                 /* �������  */    
				2,       			        /* �������ȼ�*/
				&Device_FlashHandler);   /* ������  */
}

/**
  * @Data    2019-02-20 19:49
  * @brief   ֡��ˢ������
  * @param   void *pvParameters
  * @retval  void
  */
void Devices_Task(void *pvParameters)
{
    /*����ʱ��Ƭ�������*/
    portTickType CurrentControlTick = 0;
	while(1)
	{
		DeviceFlash();
		vTaskDelayUntil(&CurrentControlTick,200 / portTICK_RATE_MS);
	}
}