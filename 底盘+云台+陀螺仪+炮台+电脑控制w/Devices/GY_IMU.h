#ifndef GY_IMU_H
#define GY_IMU_H

#include "Users.h"

extern uint8_t Cloud_GY_IMU_RXBUFF[30];
extern GY_IMU_t Cloud_IMU;

/*GY_IMU快速初始化*/
void GY_IMU_Init(void);

/*检查单位GY_IMU数据包数据*/
uint8_t GY_IMU_Checksum(uint8_t* buff);

/*检查整个GY_IMU数据包*/
void GY_IMU_getInfo(uint8_t* buff, uint16_t dataLength, GY_IMU_t* dataOut);


#endif
