#include "mathing.h"
/**
* @name abs_Calculation
* @brief 目标绝对值
* @param [in] float myabs 绝对值目标数
* @retval 
*/
float abs_Calculation(float myabs)
{
    if(myabs >= 0)
    {
        myabs = myabs;
    }
    if(myabs < 0)
    {
        myabs = -myabs;
    }
    return myabs;
}