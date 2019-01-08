#include "usart.h"	
#include "stdio.h"	
#include "stm32f4xx_conf.h"
          
//重定义fputc函数 
int fputc(int ch, FILE *f)
{ 	
	while(USART_GetFlagStatus(USART2, USART_FLAG_TC) == 0);//直到发送完毕   
	USART_SendData(USART2, ch);   
	return ch;
}


//串口1初始化---接收dbus数据
void usart1_init(u32 bound){
	
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB ,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
  
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;  
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
  
	USART_InitStructure.USART_BaudRate = bound;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure); 

	//设置中断来源
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	//设置主优先级
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	//设置抢占式优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

//	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
//USART_ITConfig(USART1, USART_IT_PE, ENABLE);
	USART_ITConfig(USART1, USART_IT_IDLE, ENABLE);//空闲中断
	
	USART_Cmd(USART1, ENABLE);
}




//初始化IO 串口2
//bound:波特率
void usart2_init(u32 bound){
	
   //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE); //使能GPIOD时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);//使能USART2时钟
 
	//串口1对应引脚复用映射
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_USART2); //GPIOA9复用为USART1
	GPIO_PinAFConfig(GPIOD,GPIO_PinSource6,GPIO_AF_USART2); //GPIOA10复用为USART1
	
	//USART1端口配置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6; //GPIOA9与GPIOA10
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用功能
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//速度50MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; //推挽复用输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //上拉
	GPIO_Init(GPIOD,&GPIO_InitStructure); //初始化PA9，PA10

   //USART1 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//波特率设置
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式
  USART_Init(USART2, &USART_InitStructure); //初始化串口1
	
  USART_Cmd(USART2, ENABLE);  //使能串口2 
	
	//USART_ClearFlag(USART1, USART_FLAG_TC);
	

//	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启相关中断

//	//Usart1 NVIC 配置
//  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;//串口1中断通道
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3;//抢占优先级3
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority =3;		//子优先级3
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
//	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器、

}

////串口3初始化---接收陀螺仪数据
//void usart2_init(u32 bound){
//		
//	GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//	
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
//  
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;  
//	GPIO_Init(GPIOD, &GPIO_InitStructure);

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
//	GPIO_Init(GPIOD, &GPIO_InitStructure);
//	

//	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);
//	GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);
//  
//	USART_InitStructure.USART_BaudRate = bound;
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;
//	USART_InitStructure.USART_Parity = USART_Parity_No;
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//	USART_Init(USART2, &USART_InitStructure); 

//	//设置中断来源
//	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
//	//设置主优先级
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	//设置抢占式优先级
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);

//	//USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
//	//USART_ITConfig(USART2, USART_IT_PE, ENABLE);
//	USART_ITConfig(USART2, USART_IT_IDLE, ENABLE);//空闲中断
//	
//	USART_Cmd(USART2, ENABLE);
//}



//串口3初始化---接收陀螺仪数据
//void usart3_init(u32 bound){
//		
//	GPIO_InitTypeDef GPIO_InitStructure;
//	USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;
//	
//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
//  
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;  
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
//	
//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;  
//	GPIO_Init(GPIOD, &GPIO_InitStructure);

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
//	GPIO_Init(GPIOD, &GPIO_InitStructure);
//	

//	GPIO_PinAFConfig(GPIOD, GPIO_PinSource8, GPIO_AF_USART3);
//	GPIO_PinAFConfig(GPIOD, GPIO_PinSource9, GPIO_AF_USART3);
//  
//	USART_InitStructure.USART_BaudRate = bound;
//	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
//	USART_InitStructure.USART_StopBits = USART_StopBits_1;
//	USART_InitStructure.USART_Parity = USART_Parity_No;
//	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
//	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
//	USART_Init(USART3, &USART_InitStructure); 

//	//设置中断来源
//	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
//	//设置主优先级
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
//	//设置抢占式优先级
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);

//	//USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);
//	//USART_ITConfig(USART3, USART_IT_PE, ENABLE);
//	USART_ITConfig(USART3, USART_IT_IDLE, ENABLE);//空闲中断
//	
//	USART_Cmd(USART3, ENABLE);
//}


//void USART1_RXDMA_Config(uint32_t USART1_DMABuff_addr, uint32_t buffsize)
//{
//	DMA_InitTypeDef DMA_InitStructure;

//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);//开启DMA2时钟
//	  
//	DMA_DeInit(DMA2_Stream2);// 复位初始化DMA数据流 

//	while(DMA_GetCmdStatus(DMA2_Stream2) != DISABLE);//确保DMA数据流复位完成
//	
//	DMA_InitStructure.DMA_Channel = DMA_Channel_4; //usart1 rx对应dma2，通道4，数据流2 	
//	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART1->DR);	//设置DMA源：串口数据寄存器地址 	
//	DMA_InitStructure.DMA_Memory0BaseAddr = USART1_DMABuff_addr;//存地址(要传输的变量的指针)
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;		//方向：从外设到内存		
//	DMA_InitStructure.DMA_BufferSize = buffsize;	//传输大小DMA_BufferSize=SENDBUFF_SIZE		
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址不增    	
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	//内存地址自增
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	//外设数据单位		
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	//内存数据单位 8bit	
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMA模式：不断循环
//	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; 	//优先级：中	     
//	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable; 	//禁用FIFO       
//	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;    
//	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single; 	//存储器突发传输 16 个节拍   	
//	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;   //外设突发传输 1 个节拍 
//	DMA_Init(DMA2_Stream2, &DMA_InitStructure);//配置DMA2的数据流		 
//	  
//	DMA_Cmd(DMA2_Stream2, ENABLE);//使能DMA
//  
//	while(DMA_GetCmdStatus(DMA2_Stream2) != ENABLE);// 等待DMA数据流有效
//  
//	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE); 	//使能DMA接收  
//}


//void USART2_RXDMA_Config(uint32_t USART2_DMABuff_addr, uint32_t buffsize)
//{
//	DMA_InitTypeDef DMA_InitStructure;

//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);//开启DMA1时钟
//	  
//	DMA_DeInit(DMA1_Stream5);// 复位初始化DMA数据流 

//	while(DMA_GetCmdStatus(DMA1_Stream5) != DISABLE);//确保DMA数据流复位完成
//	
//	DMA_InitStructure.DMA_Channel = DMA_Channel_4; //usart3 rx对应dma1，通道4，数据流1 	
//	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART2->DR);	//设置DMA源：串口数据寄存器地址 	
//	DMA_InitStructure.DMA_Memory0BaseAddr = USART2_DMABuff_addr;//存地址(要传输的变量的指针)
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;		//方向：从外设到内存		
//	DMA_InitStructure.DMA_BufferSize = buffsize;	//传输大小DMA_BufferSize=SENDBUFF_SIZE		
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址不增    	
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	//内存地址自增
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	//外设数据单位		
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	//内存数据单位 8bit	
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMA模式：不断循环
//	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; 	//优先级：中	     
//	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable; 	//禁用FIFO       
//	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;    
//	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single; 	//存储器突发传输 16 个节拍   	
//	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;   //外设突发传输 1 个节拍 
//	DMA_Init(DMA1_Stream5, &DMA_InitStructure);//配置DMA2的数据流		 
//	  
//	DMA_Cmd(DMA1_Stream5, ENABLE);//使能DMA
//  
//	while(DMA_GetCmdStatus(DMA1_Stream5) != ENABLE);// 等待DMA数据流有效
//  
//	USART_DMACmd(USART2,USART_DMAReq_Rx,ENABLE); 	//使能DMA接收  
//}


//void USART3_RXDMA_Config(uint32_t USART3_DMABuff_addr, uint32_t buffsize)
//{
//	DMA_InitTypeDef DMA_InitStructure;

//	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);//开启DMA1时钟
//	  
//	DMA_DeInit(DMA1_Stream1);// 复位初始化DMA数据流 

//	while(DMA_GetCmdStatus(DMA1_Stream1) != DISABLE);//确保DMA数据流复位完成
//	
//	DMA_InitStructure.DMA_Channel = DMA_Channel_4; //usart3 rx对应dma1，通道4，数据流1 	
//	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART3->DR);	//设置DMA源：串口数据寄存器地址 	
//	DMA_InitStructure.DMA_Memory0BaseAddr = USART3_DMABuff_addr;//存地址(要传输的变量的指针)
//	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;		//方向：从外设到内存		
//	DMA_InitStructure.DMA_BufferSize = buffsize;	//传输大小DMA_BufferSize=SENDBUFF_SIZE		
//	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable; //外设地址不增    	
//	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;	//内存地址自增
//	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;	//外设数据单位		
//	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;	//内存数据单位 8bit	
//	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//DMA模式：不断循环
//	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; 	//优先级：中	     
//	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable; 	//禁用FIFO       
//	DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;    
//	DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single; 	//存储器突发传输 16 个节拍   	
//	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;   //外设突发传输 1 个节拍 
//	DMA_Init(DMA1_Stream1, &DMA_InitStructure);//配置DMA2的数据流		 
//	  
//	DMA_Cmd(DMA1_Stream1, ENABLE);//使能DMA
//  
//	while(DMA_GetCmdStatus(DMA1_Stream1) != ENABLE);// 等待DMA数据流有效
//  
//	USART_DMACmd(USART3,USART_DMAReq_Rx,ENABLE); 	//使能DMA接收  
//}






















