#ifndef _IMU_H
#define _IMU_H

#include "stm32f4xx.h"
#include "USART.h"

#define GY_IMU_BUFFSIZE 30
#define GY_IMU_PACKAGE_LENGTH 	18

#define DMA_USE_6

typedef struct 
{
		float x;
		float y;
		float z;
}vector_t;

typedef struct 
{
	float roll;
	float pitch;
	float yaw;
}eular_t;

typedef struct
{
	vector_t gyro;
	eular_t eular;
	
	float lastYaw;
	float totalYaw;
	int16_t turnCount;
	uint8_t devStatus; 
	
	uint8_t UpdateFlag;
	uint16_t UpdateFrame;
	uint8_t OFFLINE_SET;
}GY_IMU_t;

extern GY_IMU_t Cloud_IMU;


/*初始化IMU*/
void IMU_Init(void);

/*IMU数值单个解码*/
uint8_t GY_IMU_Checksum(uint8_t* buff);


/*IMU解码*/
void GY_IMU_getInfo(uint8_t* buff, uint16_t dataLength, GY_IMU_t* dataOut);

extern uint8_t Cloud_GY_IMU_RXBUFF[GY_IMU_BUFFSIZE];








#endif
