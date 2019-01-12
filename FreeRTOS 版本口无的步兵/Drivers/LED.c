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
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE | RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOG, ENABLE);
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Low_Speed;
	
	#if New_RM
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
  GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_WriteBit(GPIOF, GPIO_Pin_14, Bit_SET);
	GPIO_WriteBit(GPIOE, GPIO_Pin_11, Bit_SET);
	#else
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_Init(GPIOE, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
  GPIO_Init(GPIOF, &GPIO_InitStructure);

  GPIO_WriteBit(GPIOE, GPIO_Pin_7, Bit_RESET);
  GPIO_WriteBit(GPIOF, GPIO_Pin_14, Bit_SET);
	
	#endif
	
	#if New_RM
	/*自定义LED排灯*/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
  GPIO_Init(GPIOG, &GPIO_InitStructure);
	
	GPIO_WriteBit(GPIOG, GPIO_Pin_1, Bit_SET);
	GPIO_WriteBit(GPIOG, GPIO_Pin_2, Bit_SET);
	GPIO_WriteBit(GPIOG, GPIO_Pin_3, Bit_SET);
	GPIO_WriteBit(GPIOG, GPIO_Pin_4, Bit_SET);
	GPIO_WriteBit(GPIOG, GPIO_Pin_5, Bit_SET);
	GPIO_WriteBit(GPIOG, GPIO_Pin_6, Bit_SET);
	GPIO_WriteBit(GPIOG, GPIO_Pin_7, Bit_SET);
	GPIO_WriteBit(GPIOG, GPIO_Pin_8, Bit_SET);
	#endif
}
