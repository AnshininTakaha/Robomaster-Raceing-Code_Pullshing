#ifndef __ROCKER_H
#define __ROCKER_H
/*函数总引导*/
#include "Users.h"

/*把遥控器的值变成x，y的值存放进去rocker_t里面*/
void Rocker_getData(float posX, float posY, rocker_t *roc);


#endif
