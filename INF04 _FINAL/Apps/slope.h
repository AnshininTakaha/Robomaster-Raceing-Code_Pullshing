#ifndef __SLOPE_H
#define __SLOPE_H

#include "Users.h"
/*����Ĭ��ֵ����*/
#define SLOPE_DAFAULT \
{ \
.count = 0, \
.scale = 0, \
.out = 0, \
} \

#define Slope_ACCTime 500

extern slope_st fb_slope;
extern slope_st lr_slope;
//extern slope_st qe_slope;

/*б����ʼ�����溯��*/
void slope_init(slope_st *slope, int32_t scale);
/*б����ʼ�����溯��*/
float slope_calculation(slope_st *slope);





#endif
