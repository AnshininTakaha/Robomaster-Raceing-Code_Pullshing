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
  |--FileName    : Task_Init.c                                              
  |--Version     : v1.0                                                          
  |--Author      : 口无                                                     
  |--Date        : 2019-02-18             
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
#include "Task_Init.h" 

/*-----------------------------------file of end------------------------------*/

/*开始任务句柄*/
TaskHandle_t StartTaskHandler=NULL;

/**
  * @Data    2019-02-18 20:50
  * @brief   开始任务函数
  * @param   void *pvParameters
  * @retval  void
  */
void TaskStart(void *pvParameters)
{
     /*设置中断优先级分组*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);


    /*进入临界区*/
    taskENTER_CRITICAL();
    /* =========================== Init of begin =========================== */
    
    /*外设初始化*/
    CAN1_QuickInit();

    /*LED初始化*/
    LED_Init();


    /* =========================== Init of end =========================== */

    /* =========================== Task of begin =========================== */
    
    /*CAN任务创建*/
    CAN_TaskCreate();

    /*控制任务创建*/
    Control_TaskCreate();
    

    

    /* =========================== Task of end =========================== */
    
    
    /*删除初始化任务*/
    vTaskDelete(StartTaskHandler);
    taskEXIT_CRITICAL();
}
 

 
