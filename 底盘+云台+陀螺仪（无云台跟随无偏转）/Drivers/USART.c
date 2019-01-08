/**
  ******************************************************************************
  * @file    USART.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   USART应用函数接口
  ******************************************************************************
  */

#include "USART.h"



/*裁判系统的定义*/

static USART_TypeDef* Using_USART = USART2;
//char USART2_buff[255];
//uint8_t USART2_Pointer = 0;


/**
  * @brief  USART1快速初始化
  * @param  USART_BaudRate 	波特率设置
  * @retval None
  * @Using 	用于接收DR16接收机Dbus数据
  */
void USART1_QuickInit(uint32_t USART_BaudRate)
{
	/*使能结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	
	/* 使能 GPIO 时钟 */
	/*USART1_TX -> PB6*/
	/*USART1_RX -> PB7*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);

	/* 使能 USART1 时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  
	/* GPIO初始化 */
	/* 是否启用复用输出
		GPIO_OType：
	 1、GPIO_OType_PP 不启用复用输出
	 2、GPIO_OType_OD	启用复用输出
	*/
	
	/* 是否上下拉
		GPIO_PuPd
	1、GPIO_PuPd_NOPULL
	2、GPIO_PuPd_UP
	3、GPIO_PuPd_DOWN
	*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	 
	/* 配置Tx引脚  */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;  
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	/* 配置Rx引脚 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/*映射接口复用*/
	/* 连接 PXx 到 USARTx_Tx，其实就是IO口复用*/
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);

/*  连接 PXx 到 USARTx_Rx，其实就是IO口复用*/
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
  
	/* 配置串USART 模式 */
	/* 波特率设置：USART_BAUDRATE */
	USART_InitStructure.USART_BaudRate = USART_BaudRate;
	
	/* 数据长度(数据位+校验位)：8 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	
	/* 停止位：1个停止位 */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	
	/* 校验位选择：不使用校验 */
	USART_InitStructure.USART_Parity = USART_Parity_No;
	
	/* 硬件流控制：不使用硬件流 */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	
	/* USART模式控制：同时使能接收和发送 */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	/* 完成USART初始化配置 */
	USART_Init(USART1, &USART_InitStructure); 
	
	/* 串口中断优先级配置 */
	NVIC_Config(USART1_IRQn, 0, 2);
  
	/* 使能串口接收中断 */
	//USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	/* 使能串口空闲中断 */
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);
	
	/* 使能串口 */
	USART_Cmd(USART1, ENABLE);
}




/**
  * @brief  USART1 RX DMA 配置，外设到内存(USART1->DR)
  * @param  USART1_DMABuff_addr->DMA目标存储地址
						buffsize->传输数据长度
  * @retval 无
	* @using  用于接收DR16接收机Dbus数据的DMA通道的设置
  */
void USART1_RXDMA_Config(uint32_t USART1_DMABuff_addr, uint32_t buffsize)
{
	DMA_InitTypeDef DMA_InitStructure;

	/*开启DMA2时钟*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	  
	/* 复位初始化DMA数据流 */
	/* USART1_RX_DMA_STREAM = DMA2_Stream2 */
	/*这里USART1的DMA通道对应的是DMA2的通道4，数据流2，这个可以通过查DMA外设通道查的*/
	DMA_DeInit(DMA2_Stream2);

	/* 确保DMA数据流复位完成 */
	while(DMA_GetCmdStatus(DMA2_Stream2) != DISABLE)
	{
		/*如果没有复位完成会无限的卡着while这里*/
	}

	/*usart1 rx对应dma2，通道4，数据流2*/	
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;
  
	/*设置DMA源：串口数据寄存器地址*/
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);//(uint32_t)(&USART1->DR)	//串口1数据寄存器地址
	
	/*内存地址(要传输的变量的指针)*/
	/*USART1_DMABuff_addr ->参数*/
	/*参数，可自己设定*/
	DMA_InitStructure.DMA_Memory0BaseAddr = USART1_DMABuff_addr;
	
	/*方向：从外设到内存*/		
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;	
	
	/*传输大小DMA_BufferSize=SENDBUFF_SIZE*/	
	/*buffsize ->参数*/
	DMA_InitStructure.DMA_BufferSize = buffsize;
	
	/*外设地址不增*/	    
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
	
	/*内存地址自增*/
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
	
	/*外设数据单位*/	
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	
	/*内存数据单位 8bit*/
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	
	
	/*DMA模式：不断循环*/
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	
	/*优先级：中*/	
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;
	
	/*禁用FIFO*/
	/*查清楚这里是什么意思的*/
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;        
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;    
	
	/*存储器突发传输 16 个节拍*/
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	
	/*外设突发传输 1 个节拍*/
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
	
	/*配置DMA2的数据流*/		   
	DMA_Init(DMA2_Stream2, &DMA_InitStructure);
	  
	/*使能DMA*/
	DMA_Cmd(DMA2_Stream2, ENABLE);
  
	/* 等待DMA数据流有效*/
	while(DMA_GetCmdStatus(DMA2_Stream2) != ENABLE)
	{
		
	}
  
	/*使能DMA接收请求*/
  USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE); 
  
}

/************************************************************************************************/
/*USART2有两种工作的方式，一个是裁判系统，一个是DPS*/
/**
  * @brief  USART2快速初始化(DataScope)
  * @param  USART_BaudRate 	波特率设置
  * @retval None
  * @Using 	DSP读取波形图像或者裁判系统返回
  */
void USART2_QuickInit(uint32_t USART_BaudRate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	/* 使能 GPIO 时钟 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD ,ENABLE);

	/* 使能 USART2 时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
  
	/* GPIO初始化 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	
	/* 配置Tx引脚  */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;  
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* 配置Rx引脚 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	/* 连接 PXx 到 USARTx_Tx*/
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);

	/*  连接 PXx 到 USARTx_Rx*/
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);
  
	/* 配置串USART 模式 */
	/* 波特率设置：USART_BAUDRATE */
	USART_InitStructure.USART_BaudRate = USART_BaudRate;
	/* 数据长度(数据位+校验位)：8 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	/* 停止位：1个停止位 */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	/* 校验位选择：不使用校验 */
	USART_InitStructure.USART_Parity = USART_Parity_No;
	/* 硬件流控制：不使用硬件流 */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* USART模式控制：同时使能接收和发送 */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* 完成USART初始化配置 */
	USART_Init(USART2, &USART_InitStructure); 
	
	/*启用裁判系统*/
#if Judgement_funtion_ON
	
	/* 串口中断优先级配置 */
	NVIC_Config(USART2_IRQn, 0, 3);
	
	/* 使能串口空闲中断 */
	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);
	
#endif
	/* 使能串口 */
	USART_Cmd(USART2, ENABLE);
}

/**
  * @brief  USART3快速初始化(IMU)
  * @param  USART_BaudRate 	波特率设置
  * @retval None
  * @Using 	IMU加速计陀螺仪的读值
  */


void USART3_QuickInit(uint32_t USART_BaudRate)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	/* 使能 GPIO 时钟 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD ,ENABLE);

	/* 使能 USART3 时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
  
	/* GPIO初始化 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	
	/* 配置Tx引脚  */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;  
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	/* 配置Rx引脚 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	/* 连接 PXx 到 USARTx_Tx*/
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3);

	/*  连接 PXx 到 USARTx_Rx*/
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3);
  
	/* 配置串USART 模式 */
	/* 波特率设置：USART_BAUDRATE */
	USART_InitStructure.USART_BaudRate = USART_BaudRate;
	/* 数据长度(数据位+校验位)：8 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	/* 停止位：1个停止位 */
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	/* 校验位选择：不使用校验 */
	USART_InitStructure.USART_Parity = USART_Parity_No;
	/* 硬件流控制：不使用硬件流 */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	/* USART模式控制：同时使能接收和发送 */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	/* 完成USART初始化配置 */
	USART_Init(USART3, &USART_InitStructure); 
	
	/* 串口中断优先级配置 */
	NVIC_Config(USART3_IRQn, 0, 3);
	
	/* 使能串口空闲中断 */
	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);
	
	/* 使能串口 */
	USART_Cmd(USART3, ENABLE);
}

/**
  * @brief  USART3 RX DMA 配置，外设到内存(USART3->DR)
  * @param  USART3_DMABuff_addr		DMA目标存储地址
  * @retval 无
  */
void USART3_RXDMA_Config(uint32_t USART3_DMABuff_addr, uint32_t buffsize)
{
	DMA_InitTypeDef DMA_InitStructure;

	/*开启DMA1时钟*/
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	  
	/* 复位初始化DMA数据流 */
	DMA_DeInit(DMA1_Stream1);

	/* 确保DMA数据流复位完成 */
	while(DMA_GetCmdStatus(DMA1_Stream1) != DISABLE){
	}

	/*USART3 rx对应dma1，通道4，数据流5*/	
	DMA_InitStructure.DMA_Channel = DMA_Channel_4;  
	/*设置DMA源：串口数据寄存器地址*/
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART3->DR);	 
	/*内存地址(要传输的变量的指针)*/
	DMA_InitStructure.DMA_Memory0BaseAddr = USART3_DMABuff_addr;
	/*方向：从外设到内存*/		
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;	
	/*传输大小DMA_BufferSize=SENDBUFF_SIZE*/	
	DMA_InitStructure.DMA_BufferSize = buffsize;
	/*外设地址不增*/	    
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; 
	/*内存地址自增*/
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	
	/*外设数据单位*/	
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
	/*内存数据单位 8bit*/
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	
	/*DMA模式：不断循环*/
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	/*优先级：中*/	
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium;      
	/*禁用FIFO*/
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;        
	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;    
	/*存储器突发传输 16 个节拍*/
	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;    
	/*外设突发传输 1 个节拍*/
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;    
	/*配置DMA2的数据流*/		   
	DMA_Init(DMA1_Stream1, &DMA_InitStructure);
	  
	/*使能DMA*/
	DMA_Cmd(DMA1_Stream1, ENABLE);
  
	/* 等待DMA数据流有效*/
	while(DMA_GetCmdStatus(DMA1_Stream1) != ENABLE)
	{

	}
  
	//使能DMA接收  
	USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE); 
  
}







































/**
  * @brief  USART使用printf，scanf端口设置
  * @param  USARTx 	USART外设
  * @retval None
  */
void USART_setPort(USART_TypeDef* USARTx){
	Using_USART = USARTx;
}

///重定向c库函数printf到串口，重定向后可使用printf函数
int fputc(int ch, FILE *f)
{
		/* 发送一个字节数据到串口 */
		USART_SendData(Using_USART, (uint8_t) ch);
		
		/* 等待发送完毕 */
		while (USART_GetFlagStatus(Using_USART, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///重定向c库函数scanf到串口，重写向后可使用scanf、getchar等函数
int fgetc(FILE *f)
{
		/* 等待串口输入数据 */
		while (USART_GetFlagStatus(Using_USART, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(Using_USART);
}
