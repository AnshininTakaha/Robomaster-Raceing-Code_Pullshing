#ifndef _TASK_CONTROL_H
#define _TASK_CONTROL_H


#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "Devices_Flash.h"
#include "ChassisControl.h"
#include "CloudControl.h"



extern TaskHandle_t Chassical_ProcessHandler;
extern TaskHandle_t Device_FlashHandler;
extern TaskHandle_t LED_LightHandler;
extern TaskHandle_t Cloud_ProcessHandler;




/*控制任务创建*/
void Control_TaskCreate();



#endif
