#ifndef __Motor_M2006_h
#define __Motor_M2006_h

#include "Users.h"

extern M2006s_t M2006s[1];


#define M2006_start_up		3800		/* �����ʼλ�� */


#define M2006_READID_START	0x207
#define M2006_READID_END	0x207
#define M2006_SENDID		0x1FF
#define M2006_LOADANGLE		36864			/* �����һ������Ҫת�ĽǶ���  4.5*8191 ��2006 8�ײ�����*/





/*M2006��ȡ������Ϣ*/
void M2006_getInfo(CanRxMsg RxMessage);


#endif
