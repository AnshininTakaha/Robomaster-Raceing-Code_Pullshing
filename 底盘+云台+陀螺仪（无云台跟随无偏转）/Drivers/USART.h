#ifndef __USART
#define __USART

#include "Users.h"

/*启用裁判系统*//*开关*/
/*开启DPS系统或者开启遥控系统*/
/*两个互相占通道了你懂得*/
/*1、启用裁判系统
  0、启用DPS*/
#define Judgement_funtion_ON 0

/*快速使能USART1*/
void USART1_QuickInit(uint32_t USART_BaudRate);

/*USART1 RX DMA配置*/
void USART1_RXDMA_Config(uint32_t USART1_DMABuff_addr, uint32_t buffsize);

/*快速使能USART2*/
void USART2_QuickInit(uint32_t USART_BaudRate);

/*快速使能USART3*/
void USART3_QuickInit(uint32_t USART_BaudRate);

/*USART3 RX DMA配置*/
void USART3_RXDMA_Config(uint32_t USART3_DMABuff_addr, uint32_t buffsize);

/*USART使用printf，scanf端口设置*/
void USART_setPort(USART_TypeDef* USARTx);

/*重定向c库函数printf到串口，重定向后可使用printf函数*/
int fputc(int ch, FILE *f);

/*重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数*/
int fgetc(FILE *f);

#endif
