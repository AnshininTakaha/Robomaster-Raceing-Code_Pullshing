#ifndef __CurrentSetting__H
#define __CurrentSetting__H

#include "Users.h"
/***************************funtions*************************/
/*���̵�����ֵ*/
void Chassis_CurrentSetting(int16_t I1,int16_t I2,int16_t I3,int16_t I4);

/*��̨������ֵ*/
void Cloud_And_Emitter_CurrentSetting(int16_t I_Yaw, int16_t I_Pitch, int16_t I_Emitter, int16_t OVER);

/*���׸�ֵ*/
void CAN_Cylinder(void);


#endif
