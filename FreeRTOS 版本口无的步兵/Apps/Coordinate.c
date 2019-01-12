#include "Coordinate.h"


/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    Rocker_to_pc
  * @brief   电脑X，Y轴值转换成为遥控器的X,Y的值
  * @param   positionX:  对应的X轴
**					 positionY:  对应的Y轴
**				   rocket(st): 遥控器储存的结构体
  * @author  口无
  * @Data    2018-11-01
 **/
/* -------------------------------- end -------------------------------- */

void Rocker_Stander(float positionX, float positionY, rocker_st *rocket)
{
    rocket->x = positionX;
    rocket->y = positionY;
    rocket->radian = atan2(rocket->y,rocket->x);
    rocket->degrees = rocket->radian * 180.0f / PI;//using the PI of arm_...
    rocket->distance = __sqrtf(pow(rocket->x,2) + pow(rocket->y,2));
    if(rocket -> degrees > 180)
    {
        rocket -> distance = -rocket -> distance;
    }
}



