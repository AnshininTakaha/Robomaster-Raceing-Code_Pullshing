#ifndef __Filter
#define __Filter

/*����������*/
#include "Users.h"

/*�˲�ԭ����*/
void sensorsAccIIRLPFilter(vector_t *in,vector_t *out);
void Filter_IIRLPF(float *in,float *out, float LpfAttFactor);



#endif
