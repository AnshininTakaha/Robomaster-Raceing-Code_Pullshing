#include "LED.h"



/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    LED_Init
  * @brief   LED初始化
  * @param   None
  * @author  口无 
  * @Data    2018-11-05
 **/
/* -------------------------------- end -------------------------------- */

void LED_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOF, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Low_Speed;

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
  GPIO_Init(GPIOF, &GPIO_InitStructure);

  GPIO_WriteBit(GPIOE, GPIO_Pin_7, Bit_SET);
  GPIO_WriteBit(GPIOF, GPIO_Pin_14, Bit_SET);
}
