#ifndef __USART_H_
#define __USART_H_

#include "Users.h"
/********USART1_Pin_define********/
#define USART1_TX_GPIO_CLK          RCC_AHB1Periph_GPIOB
#define USART1_TX_GPIO_PORT         GPIOB
#define USART1_TX_Pin          	 	GPIO_Pin_6
#define USART1_TX_PINSOURCE			GPIO_PinSource6

#define USART1_RX_GPIO_CLK          RCC_AHB1Periph_GPIOB
#define USART1_RX_GPIO_PORT         GPIOB
#define USART1_RX_Pin           	GPIO_Pin_7
#define USART1_RX_PINSOURCE			GPIO_PinSource7
/********USART1_Pin_define_END********/

/********USART1_DMA_define********/
#define USART1_RX_ADDR						(uint32_t)(&USART1->DR)	//����1���ݼĴ�����ַ
#define USART1_RX_DMA_CHANNEL           	DMA_Channel_4		//DMAͨ����
#define USART1_RX_DMA_STREAM           		DMA2_Stream2		//DMA������
/********USART1_DMA_define_END********/

/********USART2_Pin_define********/
#define USART2_TX_GPIO_CLK          RCC_AHB1Periph_GPIOD
#define USART2_TX_GPIO_PORT         GPIOD
#define USART2_TX_Pin          	 	GPIO_Pin_5
#define USART2_TX_PINSOURCE			GPIO_PinSource5

#define USART2_RX_GPIO_CLK          RCC_AHB1Periph_GPIOD
#define USART2_RX_GPIO_PORT         GPIOD
#define USART2_RX_Pin           	GPIO_Pin_6
#define USART2_RX_PINSOURCE			GPIO_PinSource6
/********USART2_Pin_define_END********/

/********USART2_DMA_define********/
#define USART2_RX_ADDR						(uint32_t)(&USART2->DR)	//����1���ݼĴ�����ַ
#define USART2_RX_DMA_CHANNEL           	DMA_Channel_4		//DMAͨ����
#define USART2_RX_DMA_STREAM           		DMA1_Stream5		//DMA������
/********USART2_DMA_define_END********/

/********USART3_Pin_define********/
#define USART3_TX_GPIO_CLK          RCC_AHB1Periph_GPIOD
#define USART3_TX_GPIO_PORT         GPIOD
#define USART3_TX_Pin          	 	GPIO_Pin_8
#define USART3_TX_PINSOURCE			GPIO_PinSource8

#define USART3_RX_GPIO_CLK          RCC_AHB1Periph_GPIOD
#define USART3_RX_GPIO_PORT         GPIOD
#define USART3_RX_Pin           	GPIO_Pin_9
#define USART3_RX_PINSOURCE			GPIO_PinSource9
/********USART3_Pin_define_END********/
/********USART3_DMA_define********/
#define USART3_RX_ADDR						(uint32_t)(&USART3->DR)	//����1���ݼĴ�����ַ
#define USART3_RX_DMA_CHANNEL           	DMA_Channel_4		//DMAͨ����
#define USART3_RX_DMA_STREAM           		DMA1_Stream1		//DMA������
/********USART3_DMA_define_END********/

\


/***************************funtions*************************/
/*USART1���ٳ�ʼ��*/
void USART1_QuickInit(uint32_t USART_BaudRate);
/*USART1 RXDMAͨ����ʼ��*/
void USART1_RXDMA_Config(uint32_t USART1_DMABuff_addr, uint32_t buffsize);
/*USART2 ���ٳ�ʼ��*/
void USART2_QuickInit(uint32_t USART_BaudRate);
/*USART2 RXDMAͨ����ʼ��*/
void USART2_RXDMA_Config(uint32_t USART2_DMABuff_addr, uint32_t buffsize);
/*USART3���ٳ�ʼ��*/
void USART3_QuickInit(uint32_t USART_BaudRate);
/*USART3 RXDMAͨ����ʼ��*/
void USART3_RXDMA_Config(uint32_t USART3_DMABuff_addr, uint32_t buffsize);
/*USARTʹ��printf��scanf�˿�����*/
void USART_setPort(USART_TypeDef* USARTx);

/*�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����*/
int fputc(int ch, FILE *f);

/*�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���*/
int fgetc(FILE *f);
/*ANO����*/
void USART_sendChar(USART_TypeDef* USARTx,char ch);

#endif
