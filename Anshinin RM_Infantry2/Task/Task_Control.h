/**
  |--------------------------------- Copyright --------------------------------|
  |                                                                            |
  |                      (C) Copyright 2019,���ޣ�                     |
  |           1 Xuefu Rd, Huadu Qu, Guangzhou Shi, Guangdong Sheng, China      |
  |                           All Rights Reserved                              |
  |                                                                            |
  |           By(GCU The wold of team | ��������ѧ����ѧԺ������Ұ�Ƕ�)         |
  |                    https://github.com/GCUWildwolfteam                      |
  |----------------------------------------------------------------------------|
  |--FileName    : Task_Control.h                                                
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
#ifndef __TASK_CONTROL_H 
#define __TASK_CONTROL_H 

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "Device_Flash.h"

/*�������񴴽�*/
void Control_TaskCreate(void);

/* =========================== DeviceFlash of begin =========================== */
/*֡��ˢ�¿��ƾ��*/
extern TaskHandle_t Device_FlashHandler;
/*֡��ˢ������*/
void Devices_Task(void *pvParameters);
/* =========================== DeviceFlash of end =========================== */






#endif	// __TASK_CONTROL_H
/*-----------------------------------file of end------------------------------*/


