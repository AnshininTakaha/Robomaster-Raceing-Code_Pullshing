#include "mathing.h"
/**
* @name abs_Calculation
* @brief Ŀ�����ֵ
* @param [in] float myabs ����ֵĿ����
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