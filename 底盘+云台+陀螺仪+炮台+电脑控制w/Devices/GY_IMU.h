#ifndef GY_IMU_H
#define GY_IMU_H

#include "Users.h"

extern uint8_t Cloud_GY_IMU_RXBUFF[30];
extern GY_IMU_t Cloud_IMU;

/*GY_IMU���ٳ�ʼ��*/
void GY_IMU_Init(void);

/*��鵥λGY_IMU���ݰ�����*/
uint8_t GY_IMU_Checksum(uint8_t* buff);

/*�������GY_IMU���ݰ�*/
void GY_IMU_getInfo(uint8_t* buff, uint16_t dataLength, GY_IMU_t* dataOut);


#endif
