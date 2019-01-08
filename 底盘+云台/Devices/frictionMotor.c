#include "frictionMotor.h"


#define FRICMOTOR_SPEEDMAX		2000
#define FRICMOTOR_SPEEDMIN		1018

/**
  * @brief  ����Ħ���ֵ���ٶ�
  * @param  speed 	����ٶȣ���Χ1000~2000
  * @retval None
  */
void fricMotor_setSpeed(uint16_t speed)
{
	if(speed<FRICMOTOR_SPEEDMIN) speed=FRICMOTOR_SPEEDMIN;
	if(speed>FRICMOTOR_SPEEDMAX) speed=FRICMOTOR_SPEEDMAX;
	TIM_SetComparex[0](TIM12, speed);
	TIM_SetComparex[1](TIM12, speed);
	
}	