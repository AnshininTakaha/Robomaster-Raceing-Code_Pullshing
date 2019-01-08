#ifndef __SLOPE_H
#define __SLOPE_H

#include "Users.h"
/*缓冲默认值设置*/
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

/*斜波初始化缓存函数*/
void slope_init(slope_st *slope, int32_t scale);
/*斜波初始化缓存函数*/
float slope_calculation(slope_st *slope);





#endif
