#ifndef __IFREERTOS_H_
#define __IFREERTOS_H_

#include "Users.h"
/*IRTOSϵͳ����*/
void IRTOS_Begin(void);

/*start_task��������*/
void start_task(void *pvParameters);

/*���й��Ӻ���*/
void vApplicationIdleHook(void);

/*��������������*/
void LED_RED(void *pvParameters);
void LED_GREAN(void *pvParameters);
void LASER_SET(void *pvParameters);


#endif
