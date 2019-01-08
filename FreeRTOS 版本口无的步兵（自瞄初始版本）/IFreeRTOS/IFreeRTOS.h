#ifndef __IFREERTOS_H_
#define __IFREERTOS_H_

#include "Users.h"
/*IRTOS系统启动*/
void IRTOS_Begin(void);

/*start_task任务启动*/
void start_task(void *pvParameters);

/*空闲钩子函数*/
void vApplicationIdleHook(void);

/*两个灯任务启动*/
void LED_RED(void *pvParameters);
void LED_GREAN(void *pvParameters);
void LASER_SET(void *pvParameters);


#endif
