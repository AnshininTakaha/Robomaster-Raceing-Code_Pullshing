#include "TIM.h"


/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    TIM6_CounterMode
  * @brief   TIM6��ʱ��ģ�ʹ���ˢ�³�ʼ��
  * @param   prescaler: ��Ƶϵ�� 
**			 		 period: ��װ�ؼĴ�����ֵ
  * @author  ���� 
  * @Data    2018-10-30
 **/
/* -------------------------------- end -------------------------------- */

void TIM6_CounterMode(u16 prescaler, u16 period)
{
    /*ʹ�ܶ�ʱ��*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

    /* ����ʱ���ṹ�� */
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    /*���ö�ʱ��ʱ�ӷ�Ƶ*/
    TIM_TimeBaseStructure.TIM_Prescaler = prescaler;

    /*�����Զ���װ�ؼĴ�����ֵ*/
    TIM_TimeBaseStructure.TIM_Period = period;

    /*��������ʱ��������˲���Ƶ������Ƶ*/
    /*TIM_CKD_DIV1���Ƿ�Ƶһ������˼��Ҳ���ǲ���Ƶ*/
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;

    /*���ü���ģʽ�����ϼ���*/
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    /*TIM6������ʱʹ��*/
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);

    /*ARR�Զ�����ʹ��*/
    TIM_ARRPreloadConfig(TIM6, ENABLE);

    //ʹ�ܶ�ʱ��
    TIM_Cmd(TIM6, ENABLE);

    /*���������ж�*/
    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);

    /*NVIC���ȼ�����*/
    NVIC_Config(TIM6_DAC_IRQn, 1, 0);
		
}

void TIM7_CounterMode(u16 prescaler, u16 period)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
  
	/* ����ʱ���ṹ�� */
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	//���ö�ʱ��ʱ�ӷ�Ƶ
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
	
	//�����Զ���װ�ؼĴ�����ֵ
	TIM_TimeBaseStructure.TIM_Period = period;
	
	//��������ʱ��������˲���Ƶ������Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	
	//���ü���ģʽ�����ϼ���
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
	
	TIM_ARRPreloadConfig(TIM7, ENABLE);
	//ʹ�ܶ�ʱ��
	TIM_Cmd(TIM7, ENABLE);
	
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
	
	NVIC_Config(TIM7_IRQn, 0, 1);
	
}
