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
/*IRTOSϵͳ����*/
void IRTOS_Begin(void);

/*start_task��������*/
void start_task(void *pvParameters);

/*���й��Ӻ���*/
void vApplicationIdleHook(void);

/*��������������*/
void TASK_ONE(void *pvParameters);
void TASK_TWO(void *pvParameters);
void TASK_THREE(void *pvParameters);


#endif
