#include "CAN.h"


/**
  * @brief  CAN1���ٳ�ʼ��
  * @param  None
  * @retval None
	* @function CAN1��ʼ��ʹ��FMP0�����жϣ�����M3508�ĸ����ӷ��صı���
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

    /*GPIO��ʼ�������������ţ�*/
    /*˵���˾��ǰѻ����Ľṹ����д�����������ֱ�ӻ����Ŷ�������ˣ��Ƚϵķ���*/

    /* �Ƿ����ø������
    	GPIO_OType��
     1��GPIO_OType_PP �����ø������
     2��GPIO_OType_OD	���ø������
    */

    /* �Ƿ�������
    	GPIO_PuPd
    1��GPIO_PuPd_NOPULL
    2��GPIO_PuPd_UP
    3��GPIO_PuPd_DOWN
    */
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

    /*����(����)IO��*/
    /*ԭ����Բ鿴�����ֲ�����IO���ù���ͼ����һҳ*/

    /* ���� IO �� CAN1_Tx*/
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource1, GPIO_AF_CAN1);

    /*  ���� IO �� CAN1_Rx*/
    GPIO_PinAFConfig(GPIOD, GPIO_PinSource0, GPIO_AF_CAN1);

    /*************************CAN��������*************************/
    CAN_InitStructure.CAN_TTCM = DISABLE;			   //MCR-TTCM  ʱ�䴥��ͨ��ģʽ
    CAN_InitStructure.CAN_ABOM = ENABLE;			   //MCR-ABOM  �Զ����߹���
    CAN_InitStructure.CAN_AWUM = ENABLE;			   //MCR-AWUM  ʹ���Զ�����ģʽ
    CAN_InitStructure.CAN_NART = DISABLE;			   //MCR-NART  ��ֹ�����Զ��ش�	  DISABLE-�Զ��ش�
    CAN_InitStructure.CAN_RFLM = DISABLE;			   //MCR-RFLM  ����FIFO ����ģʽ  DISABLE-���ʱ�±��ĻḲ��ԭ�б���
    CAN_InitStructure.CAN_TXFP = DISABLE;			   //MCR-TXFP  ����FIFO���ȼ� DISABLE-���ȼ�ȡ���ڱ��ı�ʾ��
    CAN_InitStructure.CAN_Mode = CAN_Mode_Normal;  	   //Mode  ����ģʽ

    /*��ʱ�������ã���Ƶ������*/
    //SS
    CAN_InitStructure.CAN_SJW = CAN_SJW_1tq;
    //BS1
    CAN_InitStructure.CAN_BS1 = CAN_BS1_3tq;
    //BS2
    CAN_InitStructure.CAN_BS2 = CAN_BS2_5tq;
    //��Ƶ
    CAN_InitStructure.CAN_Prescaler = 5;
    //BTR-BRP �����ʷ�Ƶ��  ������ʱ�䵥Ԫ��ʱ�䳤�� 45/(1+3+5)/5=1 Mbps

    /*��װ*/
    CAN_Init(CAN1, &CAN_InitStructure);


    /*************************CANɸѡ����ʼ��*************************/
    CAN_FilterInitStructure.CAN_FilterNumber = 0;									//ɸѡ����0
    CAN_FilterInitStructure.CAN_FilterMode = CAN_FilterMode_IdMask;					//������ID����ģʽ
    CAN_FilterInitStructure.CAN_FilterScale = CAN_FilterScale_32bit;				//ɸѡ��λ��Ϊ����32λ��
    CAN_FilterInitStructure.CAN_FilterFIFOAssignment = CAN_Filter_FIFO0 ;			//ɸѡ����������FIFO0
    CAN_FilterInitStructure.CAN_FilterActivation = ENABLE;			//ʹ��ɸѡ��
    /* ʹ��ɸѡ�������ձ�־�����ݽ��бȶ�ɸѡ����չID�������µľ����������ǵĻ��������FIFO0�� */

    //�����й���,��Ȼ��ɸѡģʽ������ȫ����λ�ö���λ�ö���0���൱�ڲ�����ɸѡ��

    CAN_FilterInitStructure.CAN_FilterIdHigh = 0x0000;				//Ҫɸѡ��ID��λ
    CAN_FilterInitStructure.CAN_FilterIdLow = 0x0000; 				//Ҫɸѡ��ID��λ
    CAN_FilterInitStructure.CAN_FilterMaskIdHigh = 0x0000;			//ɸѡ����16λÿλ����ƥ��
    CAN_FilterInitStructure.CAN_FilterMaskIdLow = 0x0000;			//ɸѡ����16λÿλ����ƥ��

    //��װ
    CAN_FilterInit(&CAN_FilterInitStructure);

    /**/
    NVIC_Config(CAN1_RX0_IRQn, 1, 1);

    CAN_ITConfig(CAN1, CAN_IT_FMP0, ENABLE);
}




/**
  * @brief  CAN��������
  * @param  CANx 		CAN���
  * 		id_type ��	id���� CAN_ID_STD�� CAN_ID_EXT
  *			id			id��
  * 		data[8]		8������
  * @retval None
  */
void CAN_SendData(CAN_TypeDef* CANx, uint8_t id_type, uint32_t id, uint8_t data[8])
{
    CanTxMsg TxMessage;

    if(id_type == CAN_Id_Standard) {
        TxMessage.StdId = id;
    }
    else {
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
