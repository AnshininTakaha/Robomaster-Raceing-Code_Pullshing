#ifndef __MOTOR_M3508
#define __MOTOR_M3508

/*������*/
#include "Users.h"
#include "typedef.h"

/*�ѹ�������õ�h�ļ�����ȥ������֮�����������ʹ��*/
extern M3508s_t M3508s[4];

/*ͨ��ȡ���յ��ı��Ľ��н��*/
void M3508_getInfo(CanRxMsg RxMessage);

/*���ĸ��������Ӧ�ĵ���ֵ*/
void M3508_setCurrent(int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4);
#endif

