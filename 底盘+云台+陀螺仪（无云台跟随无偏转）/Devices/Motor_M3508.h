#ifndef __MOTOR_M3508
#define __MOTOR_M3508

/*总引导*/
#include "Users.h"
#include "typedef.h"

/*把共用体调用到h文件里面去，方便之后各个函数的使用*/
extern M3508s_t M3508s[4];

/*通过取得收到的报文进行解包*/
void M3508_getInfo(CanRxMsg RxMessage);

/*给四个电机发对应的电流值*/
void M3508_setCurrent(int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4);
#endif

