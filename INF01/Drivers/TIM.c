#include "TIM.h"


/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    TIM6_CounterMode
  * @brief   TIM6定时器模型处理刷新初始化
  * @param   prescaler: 分频系数 
**			 		 period: 重装载寄存器的值
  * @author  口无 
  * @Data    2018-10-30
 **/
/* -------------------------------- end -------------------------------- */

void TIM6_CounterMode(u16 prescaler, u16 period)
{
    /*使能定时器*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE);

    /* 配置时基结构体 */
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    /*配置定时器时钟分频*/
    TIM_TimeBaseStructure.TIM_Prescaler = prescaler;

    /*配置自动重装载寄存器的值*/
    TIM_TimeBaseStructure.TIM_Period = period;

    /*配置死区时间与采样滤波分频，不分频*/
    /*TIM_CKD_DIV1就是分频一倍的意思，也就是不分频*/
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;

    /*配置计数模式，向上计数*/
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

    /*TIM6基本计时使能*/
    TIM_TimeBaseInit(TIM6, &TIM_TimeBaseStructure);

    /*ARR自动补偿使能*/
    TIM_ARRPreloadConfig(TIM6, ENABLE);

    //使能定时器
    TIM_Cmd(TIM6, ENABLE);

    /*开启更新中断*/
    TIM_ITConfig(TIM6, TIM_IT_Update, ENABLE);

    /*NVIC优先级设置*/
    NVIC_Config(TIM6_DAC_IRQn, 1, 0);
		
}

void TIM7_CounterMode(u16 prescaler, u16 period)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, ENABLE);
  
	/* 配置时基结构体 */
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	//配置定时器时钟分频
	TIM_TimeBaseStructure.TIM_Prescaler = prescaler;
	
	//配置自动重装载寄存器的值
	TIM_TimeBaseStructure.TIM_Period = period;
	
	//配置死区时间与采样滤波分频，不分频
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	
	//配置计数模式，向上计数
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	
	TIM_TimeBaseInit(TIM7, &TIM_TimeBaseStructure);
	
	TIM_ARRPreloadConfig(TIM7, ENABLE);
	//使能定时器
	TIM_Cmd(TIM7, ENABLE);
	
	TIM_ITConfig(TIM7, TIM_IT_Update, ENABLE);
	
	NVIC_Config(TIM7_IRQn, 0, 1);
	
}
