#ifndef __Motor_M6623_H
#define __Motor_M6623_H


#include "Users.h"

extern M6623s_t M6623s[2];

#define M6623_READID_START		0x205
#define M6623_READID_END		0x206
#define M6623_SENDID			0x1FF
#define M6623_CALIBRATIONID		0x3F0

/*获取M6623的值*/
void M6623_getInfo(CanRxMsg RxMessage);

/*设置电机的目标角度*/
void M6623_setTargetAngle(M6623Name_e motorName, int32_t angle);





#endif