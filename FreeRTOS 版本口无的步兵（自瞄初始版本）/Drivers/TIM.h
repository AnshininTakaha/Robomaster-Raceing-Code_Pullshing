#ifndef __TIM_H_
#define __TIM_H_

#include "Users.h"
/*调用TIM内部函数快速给TIM设值*/
typedef void TIM_SetComparex_f(TIM_TypeDef* TIMx, uint32_t Compare);
extern TIM_SetComparex_f *const TIM_SetComparex[4];
/********TIM12_Pin_define********/
#define TIM12_CH1_GPIO_CLK          RCC_AHB1Periph_GPIOH
#define TIM12_CH1_GPIO_PORT         GPIOH
#define TIM12_CH1_Pin          	 	GPIO_Pin_6
#define TIM12_CH1_PINSOURCE			GPIO_PinSource6
#define TIM12_CH1_ENABLE			1

#define TIM12_CH2_GPIO_CLK          RCC_AHB1Periph_GPIOH
#define TIM12_CH2_GPIO_PORT         GPIOH
#define TIM12_CH2_Pin          	 	GPIO_Pin_9
#define TIM12_CH2_PINSOURCE			GPIO_PinSource9
#define TIM12_CH2_ENABLE			1
/********TIM12_Pin_define_END********/
/***************************funtions*************************/
/*TIM6初始化*/
void TIM6_CounterMode(u16 prescaler, u16 period);
/*TIM7初始化*/
void TIM7_CounterMode(u16 prescaler, u16 period);
/*TIM12初始化*/
static void TIM12_GPIOInit(void);
/*TIMPWM设置*/
void TIM12_PWMOutput(u16 prescaler, u16 period, u16 Pulse);




#endif
