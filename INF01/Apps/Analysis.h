#ifndef __ANALYSIS_H_
#define __ANALYSIS_H_

#include "Users.h"

#define PLATFORM_A_TURN 8192
#define UNDULATION_A_TURN 8192

/*M3508�����Ӧ�Ĵ���ṹ��*/
extern RM3508_st RM3508s[4];
/*M6623�����Ӧ�Ĵ���ṹ��*/
extern RM6623_st RM6623s[2];
/*M2006�����Ӧ�Ĵ���ṹ��*/
extern RM2006_st RM2006s[1];


/*��ȡ����������صı���*/
void Analysis_getinfo(CanRxMsg RxMessage);

/*��̨���㴦��*/
void M6623_ZeroDealing_platform(int8_t id);

/*�������㴦��*/
void M2006_ZeroDealing_platform(int8_t id);


#endif

