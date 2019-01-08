#ifndef __TIMH
#define __TIMH

/*总引导函数*/
#include "Users.h"


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

/*TIMx快速设置补偿值指针操作*/
typedef void TIM_SetComparex_f(TIM_TypeDef* TIMx, uint32_t Compare);
extern TIM_SetComparex_f *const TIM_SetComparex[4];

/*TIM6*/
void TIM6_CounterMode(u16 prescaler, u16 period);

/*TIM7*/
void TIM7_CounterMode(u16 prescaler, u16 period);

/*TIM12*/
static void TIM12_GPIOInit(void);
void TIM12_PWMOutput(u16 prescaler, u16 period, u16 Pulse);

#endif
