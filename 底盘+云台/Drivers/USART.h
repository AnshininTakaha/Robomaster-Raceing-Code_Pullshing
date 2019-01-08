#ifndef __USART
#define __USART

#include "Users.h"

/*快速使能USART1*/
void USART1_QuickInit(uint32_t USART_BaudRate);

/*USART1 RX DMA配置*/
void USART1_RXDMA_Config(uint32_t USART1_DMABuff_addr, uint32_t buffsize);

/*快速使能USART2*/
void USART2_QuickInit(uint32_t USART_BaudRate);







/*USART使用printf，scanf端口设置*/
void USART_setPort(USART_TypeDef* USARTx);

/*重定向c库函数printf到串口，重定向后可使用printf函数*/
int fputc(int ch, FILE *f);

/*重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数*/
int fgetc(FILE *f);

#endif
