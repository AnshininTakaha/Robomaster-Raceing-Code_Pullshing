#include "Filter.h"

/**
  * @brief  IIR低通滤波，输入与输出不能是同一个变量
  * @param[in]  *in 输入数据
  *				 LpfAttFactor 低通滤波衰减因子 Attenuation should be between 0 to 1.
  * @param[out]	*out 数据输出
  * @retval None
  */
void Filter_IIRLPF(float *in,float *out, float LpfAttFactor)
{
    *out = *out + LpfAttFactor*(*in - *out);
}

void Filter_IIRLPFINT(int *in,int *out, float LpAtt)
{
    *out = *out + LpAtt*(*in - *out);
}
