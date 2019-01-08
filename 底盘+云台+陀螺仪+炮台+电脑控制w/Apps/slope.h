#ifndef _SLOPE__
#define _SLOPE__

#include "Users.h"

/*斜坡缓冲默认值*/
#define SLOPE_GEN_DAFAULT \
{ \
.count = 0, \
.scale = 0, \
.out = 0, \
} \

/*默认缓冲初始化函数*/
void slope_init(slope_t *slope, int32_t scale);

/*斜坡计算函数接口*/
float slope_calculation(slope_t *slope);


#endif

