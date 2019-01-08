#ifndef __USART
#define __USART

#include "Users.h"

/*����ʹ��USART1*/
void USART1_QuickInit(uint32_t USART_BaudRate);

/*USART1 RX DMA����*/
void USART1_RXDMA_Config(uint32_t USART1_DMABuff_addr, uint32_t buffsize);

/*����ʹ��USART2*/
void USART2_QuickInit(uint32_t USART_BaudRate);







/*USARTʹ��printf��scanf�˿�����*/
void USART_setPort(USART_TypeDef* USARTx);

/*�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����*/
int fputc(int ch, FILE *f);

/*�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���*/
int fgetc(FILE *f);

#endif
