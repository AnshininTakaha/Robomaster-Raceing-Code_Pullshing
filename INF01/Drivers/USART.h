#ifndef __USART_H_
#define __USART_H_

#include "Users.h"

/***************************funtions*************************/
/*USART1���ٳ�ʼ��*/
void USART1_QuickInit(uint32_t USART_BaudRate);
/*USART1 RXDMAͨ����ʼ��*/
void USART1_RXDMA_Config(uint32_t USART1_DMABuff_addr, uint32_t buffsize);





#endif
