#include "Filter.h"


void Filter_IIRLPF(float *in,float *out, float LpfAttFactor)
{
    *out = *out + LpfAttFactor*(*in - *out);
}

void Filter_IIRLPFINT(int *in,int *out, float LpAtt)
{
    *out = *out + LpAtt*(*in - *out);
}


