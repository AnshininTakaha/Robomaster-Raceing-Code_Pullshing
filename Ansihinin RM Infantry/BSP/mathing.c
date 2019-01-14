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

/**
* @name Ki限幅
* @brief Ki限幅
* @param [in] float *KI_OUT 出来的数据
*        [in] arg2 float MAXER 最大值
* @retval 在PID计算的时候给KI进行限幅
*/
void Ki_Limiting(float *KI_OUT,float MAXER)
{
    if(*KI_OUT > MAXER)
    {
        *KI_OUT = MAXER;
    }
    if(*KI_OUT < -MAXER)
    {
        *KI_OUT = -MAXER;
    }
}
/**
* @name Output_Limting
* @brief PWM输出限幅
* @param [in] float *Output 输出限幅
*        [in] float MAXER 输出最大值
* @retval 
*/
void Output_Limting(float *Output, float MAXER)
{
    if(*Output > MAXER)
    {
        *Output = MAXER;
    }
    if(*Output < -MAXER)
    {
        *Output = -MAXER;
    }
}








