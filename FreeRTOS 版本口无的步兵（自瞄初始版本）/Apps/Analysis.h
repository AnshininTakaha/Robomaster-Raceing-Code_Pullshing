#ifndef __ANALYSIS_H_
#define __ANALYSIS_H_

#include "Users.h"

#define PLATFORM_A_TURN 8192
#define UNDULATION_A_TURN 8192

/*M3508电机对应的储存结构体*/
extern RM3508_st RM3508s[4];
/*M6623电机对应的储存结构体*/
extern RM6623_st RM6623s[2];
/*M2006电机对应的储存结构体*/
extern RM2006_st RM2006s[1];


/*收取各个电机返回的报文*/
void Analysis_getinfo(CanRxMsg RxMessage);

/*云台过零处理*/
void M6623_ZeroDealing_platform(int8_t id);

/*拨弹过零处理*/
void M2006_ZeroDealing_platform(int8_t id);


#endif

