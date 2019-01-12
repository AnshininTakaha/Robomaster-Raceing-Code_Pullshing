#ifndef __CurrentSetting__H
#define __CurrentSetting__H

#include "Users.h"
/***************************funtions*************************/
/*底盘电流赋值*/
void Chassis_CurrentSetting(int16_t I1,int16_t I2,int16_t I3,int16_t I4);

/*云台电流赋值*/
void Cloud_And_Emitter_CurrentSetting(int16_t I_Yaw, int16_t I_Pitch, int16_t I_Emitter, int16_t OVER);

/*气缸赋值*/
void CAN_Cylinder(void);


#endif
