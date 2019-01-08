#ifndef __PC_processing__
#define __PC_processing__

#include "Users.h"

#define KEY_ACC_TIME     500  //ms
extern slope_t fb_slope;
extern slope_t lr_slope;

/*键盘上面的WASD处理*/
void MOPC_WASD_Dealing(rocker_t *rocker);

/*键盘上面的QE处理*/
void MOPC_QE_Dealing(rocker_t *rocker);
#endif

