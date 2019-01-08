#include "CAN.h"


/**
  * @brief  CAN1快速初始化
  * @param  None
  * @retval None
	* @function CAN1初始化使能FMP0挂起中断，接受M3508四个轮子返回的报文
  */
void CAN1_QuickInit(void)
{
    /*各种结构体使能*/
    GPIO_InitTypeDef GPIO_InitStructure;
    CAN_InitTypeDef CAN_InitStructure;
    CAN_FilterInitTypeDef  CAN_FilterInitStructure;

    /*使能对应GPIO的时钟*/
    /*CAN1TX -> PD1*/
    /*CAN1RX -> PD0*/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    /*使能对应的CAN1时钟*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

    /*GPIO初始化（不包括引脚）*/
    /*说白了就是把基本的结构体先写出来，后面就直接换引脚定义就是了，比较的方便*/

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
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

    /*配置CAN1的TX引脚*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /*配置CAN1的RX引脚*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /*复用(连接)IO口*/
    /*原理可以查看数据手册所有IO复用功能图的那一页*/

    /* 连接 IO 到 CAN1_Tx*/
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_CAN1);

    /*  连接 IO 到 CAN1_Rx*/
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_CAN1);

    /*************************CAN基本配置*************************/
    CAN_InitStructure.CAN_TTCM = DISABLE;			   //MCR-TTCM  时间触发通信模式
    CAN_InitStructure.CAN_ABOM = ENABLE;			   //MCR-ABOM  自动离线管理
    CAN_InitStructure.CAN_AWUM = ENABLE;			   //MCR-AWUM  使用自动唤醒模式
    CAN_InitStructure.CAN_NART = DISABLE;			   //MCR-NART  禁止报文自动重传	  DISABLE-自动重传
    CAN_InitStructure.CAN_RFLM = DISABLE;			   //MCR-RFLM  接收FIFO 锁定模式  DISABLE-溢出时新报文会覆盖原有报文
    CAN_InitStructure.CAN_TXFP = DISABLE;			   //MCR-TXFP  发送FIFO优先级 DISABLE-优先级取决于报文标示符
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;  	   //Mode  工作模式

    /*三时间宽度设置，分频器设置*/
    //SS
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
    //BS1
    CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;
    //BS2
    CAN_InitStructure.CAN_BS2 = CAN_BS2_5tq;
    //分频
    CAN_InitStructure.CAN_Prescaler = 5;
    //BTR-BRP 波特率分频器  定义了时间单元的时间长度 45/(1+3+5)/5=1 Mbps

    /*封装*/
    CAN_Init(CAN1, &CAN_InitStructure);


    /*************************CAN筛选器初始化*************************/
    CAN_FilterInitStructure.CAN_FilterNumber = 0;									//筛选器组0
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;					//工作在ID掩码模式
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;				//筛选器位宽为单个32位。
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0 ;			//筛选器被关联到FIFO0
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;			//使能筛选器
    /* 使能筛选器，按照标志的内容进行比对筛选，扩展ID不是如下的就抛弃掉，是的话，会存入FIFO0。 */

    //不进行过滤,虽然是筛选模式，但是全部的位置都是位置都是0，相当于不进行筛选。

    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;				//要筛选的ID高位
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000; 				//要筛选的ID低位
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;			//筛选器高16位每位不须匹配
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;			//筛选器低16位每位不须匹配

    //封装
    CAN_FilterInit(&CAN_FilterInitStructure);

    /**/
    NVIC_Config(CAN1_RX0_IRQn, 1, 1);

    CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
}




/**
  * @brief  CAN发送数据
  * @param  CANx 		CAN编号
  * 		id_type ·	id类型 CAN_ID_STD， CAN_ID_EXT
  *			id			id号
  * 		data[8]		8个数据
  * @retval None
  */
void CAN_SendData(CAN_TypeDef* CANx, uint8_t id_type, uint32_t id, uint8_t data[8])
{
    CanTxMsg TxMessage;

    if(id_type == CAN_Id_Standard) {
        TxMessage.StdId = id;
    }
    else {
        TxMessage.ExtId = id;					 //ID号
    }

    TxMessage.IDE = id_type;					 //ID类型
    TxMessage.RTR = CAN_RTR_DATA;				 //发送的为数据
    TxMessage.DLC = 0x08;						 //数据长度为8字节

    /*设置要发送的数据*/
    for (uint8_t i = 0; i < 8; i++)
    {
        TxMessage.Data[i] = data[i];
    }

    CAN_Transmit(CANx, &TxMessage);
}
