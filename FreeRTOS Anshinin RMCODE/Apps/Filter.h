#ifndef Filter_H
#define Filter_H

#include "Users.h"
/***************************funtions*************************/
/*ÂË²¨*/
void Filter_IIRLPF(float *in,float *out, float LpfAttFactor);
void Filter_IIRLPFINT(int *in,int *out, float LpAtt);



#endif

