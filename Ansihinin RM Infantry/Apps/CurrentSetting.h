#ifndef _CURRENTSETTING_H
#define _CURRENTSETTING_H

#include "stm32f4xx.h"
#include "CAN.h"




/*���õ��̵���*/
void Chassis_CurrentSetting(int16_t I1,int16_t I2,int16_t I3,int16_t I4);

/*������̨����*/
void Cloud_And_Emitter_CurrentSetting(int16_t I_Yaw, int16_t I_Pitch, \
	int16_t I_Emitter, int16_t OVER);


#endif
