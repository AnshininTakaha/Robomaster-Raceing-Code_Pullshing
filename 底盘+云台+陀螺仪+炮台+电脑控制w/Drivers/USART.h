#ifndef __USART
#define __USART

#include "Users.h"

/*���ò���ϵͳ*//*����*/
/*����DPSϵͳ���߿���ң��ϵͳ*/
/*��������ռͨ�����㶮��*/
/*1�����ò���ϵͳ
  0������DPS*/
#define Judgement_funtion_ON 0

/*����ʹ��USART1*/
void USART1_QuickInit(uint32_t USART_BaudRate);

/*USART1 RX DMA����*/
void USART1_RXDMA_Config(uint32_t USART1_DMABuff_addr, uint32_t buffsize);

/*����ʹ��USART2*/
void USART2_QuickInit(uint32_t USART_BaudRate);

/*����ʹ��USART3*/
void USART3_QuickInit(uint32_t USART_BaudRate);

/*USART3 RX DMA����*/
void USART3_RXDMA_Config(uint32_t USART3_DMABuff_addr, uint32_t buffsize);

/*USARTʹ��printf��scanf�˿�����*/
void USART_setPort(USART_TypeDef* USARTx);

/*�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����*/
int fputc(int ch, FILE *f);

/*�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���*/
int fgetc(FILE *f);

#endif
