#ifndef __Motor_M2006_h
#define __Motor_M2006_h

#include "Users.h"

extern M2006s_t M2006s[1];


#define M2006_start_up		3800		/* 电机初始位置 */


#define M2006_READID_START	0x207
#define M2006_READID_END	0x207
#define M2006_SENDID		0x1FF
#define M2006_LOADANGLE		36864			/* 电机拨一个弹需要转的角度数  4.5*8191 （2006 8孔拨弹）*/





/*M2006获取报文信息*/
void M2006_getInfo(CanRxMsg RxMessage);


#endif
