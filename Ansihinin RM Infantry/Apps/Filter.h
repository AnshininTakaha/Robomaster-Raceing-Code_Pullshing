#ifndef _FILTER_H
#define _FILTER_H


#include "stm32f4xx.h"








/*ILF�˲�*/
void Filter_IIRLPF(float *in,float *out, float LpfAttFactor);

/*ILF INT�˲�*/
void Filter_IIRLPFINT(int *in,int *out, float LpAtt);



#endif
