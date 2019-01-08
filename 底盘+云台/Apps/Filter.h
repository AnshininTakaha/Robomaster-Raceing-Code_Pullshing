#ifndef __Filter
#define __Filter

/*总引导函数*/
#include "Users.h"

/*滤波原理函数*/
void sensorsAccIIRLPFilter(vector_t *in,vector_t *out);
void Filter_IIRLPF(float *in,float *out, float LpfAttFactor);



#endif
