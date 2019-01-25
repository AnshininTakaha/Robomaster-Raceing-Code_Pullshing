#ifndef _TIM_H
#define _TIM_H

#include "stm32f4xx.h"
#include "NVIC.h"
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

/********TIM5_Pin_define********/
#define TIM5_CH1_GPIO_CLK           RCC_AHB1Periph_GPIOA
#define TIM5_CH1_GPIO_PORT          GPIOA
#define TIM5_CH1_Pin          	 	GPIO_Pin_0
#define TIM5_CH1_PINSOURCE			GPIO_PinSource0
#define TIM5_CH1_ENABLE			    1

#define TIM5_CH2_GPIO_CLK           RCC_AHB1Periph_GPIOA
#define TIM5_CH2_GPIO_PORT          GPIOA
#define TIM5_CH2_Pin          	 	GPIO_Pin_1
#define TIM5_CH2_PINSOURCE			GPIO_PinSource1
#define TIM5_CH2_ENABLE			    1
/********TIM1_Pin_define_END********/
/*TIM6计数模式初始化*/
void TIM6_CounterMode(u16 prescaler, u16 period);
/*TIM7计数模式初始化*/
void TIM7_CounterMode(u16 prescaler, u16 period);

/*TIM12初始化*/
static void TIM12_GPIOInit(void);
/*TIM12PWM设置*/
void TIM12_PWMOutput(u16 prescaler, u16 period, u16 Pulse);

/*TIM5初始化*/
static void TIM5_GPIOInit(void);
/*TIM5PWM设置*/
void TIM5_PWMOutput(uint16_t prescaler, uint16_t period, uint16_t Pulse);

#endif
