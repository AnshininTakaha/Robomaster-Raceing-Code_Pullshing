#include "TIM.h"

/*����TIM�ڲ��������ٸ�TIM��ֵ*/
TIM_SetComparex_f *const TIM_SetComparex[4] =
{
    TIM_SetCompare1,
    TIM_SetCompare2,
    TIM_SetCompare3,
    TIM_SetCompare4
};

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
    NVIC_Config(TIM6_DAC_IRQn, 9, 0);
		
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
	
	NVIC_Config(TIM7_IRQn, 6, 0);
	
}


/**
  * @brief  TIM12_GPIO��ʼ��(Ħ����)
  * @param  None
  * @retval None
  */
static void TIM12_GPIOInit(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(TIM12_CH1_GPIO_CLK | TIM12_CH2_GPIO_CLK, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;


    GPIO_InitStructure.GPIO_Pin = TIM12_CH1_Pin;
    GPIO_Init(TIM12_CH1_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(TIM12_CH1_GPIO_PORT,TIM12_CH1_PINSOURCE, GPIO_AF_TIM12);


    GPIO_InitStructure.GPIO_Pin = TIM12_CH2_Pin;
    GPIO_Init(TIM12_CH2_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(TIM12_CH2_GPIO_PORT,TIM12_CH2_PINSOURCE, GPIO_AF_TIM12);


}



/**
  * @brief  TIM12��ΪPWM�����ʼ��
  * @param  prescaler 	ʱ��Ԥ��Ƶ
  *			period		��ʱ����װ�ؼĴ�����ֵ
  *			Pulse		ռ�ձȣ����Ϊ��װ�ص�ֵ
  *			��ʱ����ʱƵ�ʣ�ϵͳʱ��Ƶ��/Ԥ��Ƶ/��װ��ֵ
  * @retval None
  */
void TIM12_PWMOutput(u16 prescaler, u16 period, u16 Pulse)
{
    //IO��ʼ��
    TIM12_GPIOInit();

    //ʹ�ܶ�ʱ��ʱ��
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, ENABLE);

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

    TIM_TimeBaseInit(TIM12, &TIM_TimeBaseStructure);

    /*��������ȽϽṹ��*/
    TIM_OCInitTypeDef  TIM_OCInitStructure;
    //�������ģʽ��PWM1ģʽ
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
    //ʹ�����
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
    //��ʹ�ܻ������
    TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Disable;
    //���ó�ʼռ�ձ�
    TIM_OCInitStructure.TIM_Pulse = Pulse;
    //����PWM���ԣ���ʼ��ƽΪ��
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
    //���ÿ���ʱ�����ƽ
    TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;

    //���û������PWM���ԣ���ʼ��ƽΪ��(����ҲҪ���ã�����������ܳ���)
    TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;
    //���û����������ʱ�����ƽ(����ҲҪ���ã�����������ܳ���)
    TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;


    //��ʼ��Ϊ��Ӧͨ���������ͨ��1
    TIM_OC1Init(TIM12, &TIM_OCInitStructure);


    //��ʼ��Ϊ��Ӧͨ���������ͨ��2
    TIM_OC2Init(TIM12, &TIM_OCInitStructure);

    //ʹ�ܶ�ʱ��
    TIM_Cmd(TIM12, ENABLE);

}
