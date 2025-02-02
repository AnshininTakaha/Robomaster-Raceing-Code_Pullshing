#include "Laser.h"


/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    Laser_Init
  * @brief   激光初始化
  * @param   None
  * @author  口无 
  * @Data    2018-11-09
 **/
/* -------------------------------- end -------------------------------- */

void Laser_Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(LASER_GPIO_CLK, ENABLE);

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Low_Speed;

    GPIO_InitStructure.GPIO_Pin = LASER_PIN;
    GPIO_Init(LASER_GPIO_PORT, &GPIO_InitStructure);

    LASER_ON();
}




