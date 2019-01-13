#include "CAN.h"
/**
* @name CAN1_QuickInit
* @brief CAN1���ٳ�ʼ������ȡ�������ڵķ���ֵ
* @param None
* @retval 
*/
void CAN1_QuickInit(void)
{
	    /*���ֽṹ��ʹ��*/
    GPIO_InitTypeDef GPIO_InitStructure;
    CAN_InitTypeDef CAN_InitStructure;
    CAN_FilterInitTypeDef  CAN_FilterInitStructure;

    /*ʹ�ܶ�ӦGPIO��ʱ��*/
    /*CAN1TX -> PD1*/
    /*CAN1RX -> PD0*/
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

    /*ʹ�ܶ�Ӧ��CAN1ʱ��*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;

    /*����CAN1��TX����*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /*����CAN1��RX����*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOD, &GPIO_InitStructure);

    /* ���� IO �� CAN1_Tx*/
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_CAN1);

    /*  ���� IO �� CAN1_Rx*/
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_CAN1);

    /********************************CAN��������********************************/
    /*MCR-TTCM  ʱ�䴥��ͨ��ģʽ*/
    CAN_InitStructure.CAN_TTCM = DISABLE;

    /*MCR-ABOM  �Զ����߹���*/
    CAN_InitStructure.CAN_ABOM = ENABLE;

    /*MCR-AWUM  ʹ���Զ�����ģʽ*/
    CAN_InitStructure.CAN_AWUM = ENABLE;

    /*MCR-NART  ��ֹ�����Զ��ش� DISABLE-�Զ��ش�*/			   
    CAN_InitStructure.CAN_NART = DISABLE;

    /*MCR-RFLM  ����FIFO ����ģʽ  DISABLE-���ʱ�±��ĻḲ��ԭ�б���*/
    CAN_InitStructure.CAN_RFLM = DISABLE;

	/*MCR-TXFP  ����FIFO���ȼ� DISABLE-���ȼ�ȡ���ڱ��ı�ʾ��*/
    CAN_InitStructure.CAN_TXFP = DISABLE;

    /*Mode  ����ģʽ*/
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;  	  

    /*��ʱ�������ã���Ƶ�����ã�������ʱ�䵥Ԫ��ʱ�䳤�� 45/(1+3+5)/5=1 Mbps*/
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
    CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;
    CAN_InitStructure.CAN_BS2 = CAN_BS2_5tq;
    CAN_InitStructure.CAN_Prescaler = 5;
    
    CAN_Init(CAN1, &CAN_InitStructure);


    /*************************CANɸѡ����ʼ��*************************/
    CAN_FilterInitStructure.CAN_FilterNumber = 0;									
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;					
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;				
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0 ;			
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;			

    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;				
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000; 				
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;			
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;			

    CAN_FilterInit(&CAN_FilterInitStructure);

    NVIC_Config(CAN1_RX0_IRQn, 10, 0);

    CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
}

/**
* @name CAN_SendData
* @brief ����CANx�źŵ���Ӧ��CAN��
* @param [in] CANx     ��Ӧ��CAN
*        [in] id_type  CAN���Ͷ�Ӧ��id������
         [in]id        CAN��Ӧ��id
         [in]data[8]   ��Ӧ�ķ��͵�����
* @retval       ��Ҫ˵��
*/
void CAN_SendData(CAN_TypeDef* CANx, uint8_t id_type, uint32_t id, uint8_t data[8])
{
    CanTxMsg TxMessage;

    if(id_type == CAN_Id_Standard) 
		{
        TxMessage.StdId = id;
    }
    else 
		{
        TxMessage.ExtId = id;					 //ID��
    }

    TxMessage.IDE = id_type;					 //ID����
    TxMessage.RTR = CAN_RTR_DATA;				 //���͵�Ϊ����
    TxMessage.DLC = 0x08;						 //���ݳ���Ϊ8�ֽ�

    /*����Ҫ���͵�����*/
    for (uint8_t i = 0; i < 8; i++)
    {
        TxMessage.Data[i] = data[i];
    }

    CAN_Transmit(CANx, &TxMessage);
}
