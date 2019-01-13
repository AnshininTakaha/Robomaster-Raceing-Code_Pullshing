#include "Delay.h"
/**
* @name delay_ms
* @brief ���к��뼶��ʱ
* @param [in] _ms     ���뼶��ʱ
* @retval 
*/
void delay_ms(uint32_t _ms)
{
	SysTick_Config(SystemCoreClock/1000);
		for(u32 i = 0; i < _ms; i++){
		while(!((SysTick->CTRL)&(1<<16)));
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

/**
* @name delay_us
* @brief ����΢�뼶��ʱ
* @param [in] _us     ΢�뼶��ʱ
* @retval 
*/
void delay_us(uint32_t _us)
{
	SysTick_Config(SystemCoreClock/1000000);
	for(u32 i = 0; i < _us; i++){
		while(!((SysTick->CTRL)&(1<<16)));
	}
	SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}