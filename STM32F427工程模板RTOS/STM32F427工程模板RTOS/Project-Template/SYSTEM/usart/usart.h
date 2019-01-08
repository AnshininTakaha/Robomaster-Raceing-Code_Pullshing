#ifndef __USART_H
#define __USART_H

#include "stm32f4xx.h" 
	
#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
#define GYIMU_BuffSIZE   18+2  //陀螺仪缓冲区长度
	  	
void check1(void);
void usart2_init(u32 bound);
void usart1_init(u32 bound);
void usart3_init(u32 bound);
void USART1_RXDMA_Config(uint32_t USART1_DMABuff_addr, uint32_t buffsize);
void USART2_RXDMA_Config(uint32_t USART2_DMABuff_addr, uint32_t buffsize);
void USART3_RXDMA_Config(uint32_t USART1_DMABuff_addr, uint32_t buffsize);

#endif


