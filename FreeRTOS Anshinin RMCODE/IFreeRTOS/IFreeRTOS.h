#ifndef __IFREERTOS_H_
#define __IFREERTOS_H_

#include "Users.h"
typedef struct
{
	char* name;
	int old;
	
}Send_st;

typedef struct
{
	char* R_name;
	int R_old;
	
}Receive_st;


//void Initing();
/*IRTOS系统启动*/
void IRTOS_Begin(void);

/*start_task任务启动*/
void start_task(void *pvParameters);

/*空闲钩子函数*/
void vApplicationIdleHook(void);

/*两个灯任务启动*/
void TASK_ONE(void *pvParameters);
void TASK_TWO(void *pvParameters);
void TASK_THREE(void *pvParameters);


#endif
