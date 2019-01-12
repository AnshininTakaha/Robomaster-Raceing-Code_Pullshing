#include "Filter.h"

/**
  * @brief  IIR��ͨ�˲������������������ͬһ������
  * @param[in]  *in ��������
  *				 LpfAttFactor ��ͨ�˲�˥������ Attenuation should be between 0 to 1.
  * @param[out]	*out �������
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
