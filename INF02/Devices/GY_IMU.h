#ifndef __GY_IMU_
#define __GY_IMU_

#include "Users.h"

extern uint8_t Cloud_GY_IMU_RXBUFF[30];
#define GY_IMU_BUFFSIZE 	30
#define GY_IMU_PACKAGE_LENGTH 	18
/***************************funtions*************************/
/*GY_IMU��ʼ��*/
void GY_IMU_Init(void);

/*GY_IMU���ݰ�У��*/
uint8_t GY_IMU_Checksum(uint8_t* buff);

/*�������ݰ�У��*/
void GY_IMU_getInfo(uint8_t* buff, uint16_t dataLength, GY_IMU_t* dataOut);

#endif