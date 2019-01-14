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

/**
* @name Ki�޷�
* @brief Ki�޷�
* @param [in] float *KI_OUT ����������
*        [in] arg2 float MAXER ���ֵ
* @retval ��PID�����ʱ���KI�����޷�
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
* @brief PWM����޷�
* @param [in] float *Output ����޷�
*        [in] float MAXER ������ֵ
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








