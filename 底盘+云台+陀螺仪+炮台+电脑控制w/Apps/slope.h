#ifndef _SLOPE__
#define _SLOPE__

#include "Users.h"

/*б�»���Ĭ��ֵ*/
#define SLOPE_GEN_DAFAULT \
{ \
.count = 0, \
.scale = 0, \
.out = 0, \
} \

/*Ĭ�ϻ����ʼ������*/
void slope_init(slope_t *slope, int32_t scale);

/*б�¼��㺯���ӿ�*/
float slope_calculation(slope_t *slope);


#endif

