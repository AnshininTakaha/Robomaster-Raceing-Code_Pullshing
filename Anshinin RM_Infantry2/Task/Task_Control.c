/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,口无,                     |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | 华南理工大学广州学院机器人野狼队)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : Task_Control.c                                              
  |--Version     : v1.0                                                          
  |--Author      : 口无                                                     
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
/*帧率刷新控制句柄*/
static TaskHandle_t Device_FlashHandler = NULL;
/* =========================== DeviceFlash of end =========================== */


/**
  * @Data    2019-02-20 19:46
  * @brief   控制任务创建
  * @param   void
  * @retval  void
  */
void Control_TaskCreate(void)
{
    xTaskCreate(Devices_Task,           /* 任务函数  */        
				"Devices_Task",         /* 任务名    */      
				128,       			      /* 任务栈大小*/  
				NULL,                 /* 任务参数  */    
				2,       			        /* 任务优先级*/
				&Device_FlashHandler);   /* 任务句柄  */
}

/**
  * @Data    2019-02-20 19:49
  * @brief   帧率刷新任务
  * @param   void *pvParameters
  * @retval  void
  */
void Devices_Task(void *pvParameters)
{
    /*创建时间片计算变量*/
    portTickType CurrentControlTick = 0;
	while(1)
	{
		DeviceFlash();
		vTaskDelayUntil(&CurrentControlTick,200 / portTICK_RATE_MS);
	}
}