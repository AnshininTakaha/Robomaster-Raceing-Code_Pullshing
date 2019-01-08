#include "NVIC.h"


/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    NVIC_Config
  * @brief   �ж�����
  * @param   IRQChannel: ͨ��
**					 MainPriority: ��ռ���ȼ�
**			 	   SubPriority: �Ƚ����ȼ�
  * @author  ���� 
  * @Data    2018-10-26
 **/
/* -------------------------------- end -------------------------------- */

void NVIC_Config(uint16_t IRQChannel, uint16_t MainPriority, uint16_t SubPriority)
{
    /*�жϽṹ��*/
    NVIC_InitTypeDef NVIC_InitStructure;

    /*�ж���Դͨ��������*/
    NVIC_InitStructure.NVIC_IRQChannel = IRQChannel;

    /*��Ҫ�����ȼ�*/
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = MainPriority;

    /*������ռ�ĵ����ȼ�*/
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;

    /*ͨ��ʹ��*/
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

    /*NVIC�жϺ�����װ*/
    NVIC_Init(&NVIC_InitStructure);
}
