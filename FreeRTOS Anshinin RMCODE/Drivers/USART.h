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
#define USART1_RX_ADDR						(uint32_t)(&USART1->DR)	//串口1数据寄存器地址
#define USART1_RX_DMA_CHANNEL           	DMA_Channel_4		//DMA通道号
#define USART1_RX_DMA_STREAM           		DMA2_Stream2		//DMA数据流
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
#define USART2_RX_ADDR						(uint32_t)(&USART2->DR)	//串口1数据寄存器地址
#define USART2_RX_DMA_CHANNEL           	DMA_Channel_4		//DMA通道号
#define USART2_RX_DMA_STREAM           		DMA1_Stream5		//DMA数据流
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
#define USART3_RX_ADDR						(uint32_t)(&USART3->DR)	//串口1数据寄存器地址
#define USART3_RX_DMA_CHANNEL           	DMA_Channel_4		//DMA通道号
#define USART3_RX_DMA_STREAM           		DMA1_Stream1		//DMA数据流
/********USART3_DMA_define_END********/

\


/***************************funtions*************************/
/*USART1快速初始化*/
void USART1_QuickInit(uint32_t USART_BaudRate);
/*USART1 RXDMA通道初始化*/
void USART1_RXDMA_Config(uint32_t USART1_DMABuff_addr, uint32_t buffsize);
/*USART2 快速初始化*/
void USART2_QuickInit(uint32_t USART_BaudRate);
/*USART2 RXDMA通道初始化*/
void USART2_RXDMA_Config(uint32_t USART2_DMABuff_addr, uint32_t buffsize);
/*USART3快速初始化*/
void USART3_QuickInit(uint32_t USART_BaudRate);
/*USART3 RXDMA通道初始化*/
void USART3_RXDMA_Config(uint32_t USART3_DMABuff_addr, uint32_t buffsize);
/*USART使用printf，scanf端口设置*/
void USART_setPort(USART_TypeDef* USARTx);

/*重定向c库函数printf到串口，重定向后可使用printf函数*/
int fputc(int ch, FILE *f);

/*重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数*/
int fgetc(FILE *f);
/*ANO发送*/
void USART_sendChar(USART_TypeDef* USARTx,char ch);

#endif
