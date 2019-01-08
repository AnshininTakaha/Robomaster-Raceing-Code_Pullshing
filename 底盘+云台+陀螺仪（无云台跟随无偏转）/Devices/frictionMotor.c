#include "frictionMotor.h"


#define FRICMOTOR_SPEEDMAX		2000
#define FRICMOTOR_SPEEDMIN		1018

/**
  * @brief  设置摩擦轮电机速度
  * @param  speed 	电机速度，范围1000~2000
  * @retval None
  */
void fricMotor_setSpeed(uint16_t speed)
{
	if(speed<FRICMOTOR_SPEEDMIN) speed=FRICMOTOR_SPEEDMIN;
	if(speed>FRICMOTOR_SPEEDMAX) speed=FRICMOTOR_SPEEDMAX;
	TIM_SetComparex[0](TIM12, speed);
	TIM_SetComparex[1](TIM12, speed);
	
}	