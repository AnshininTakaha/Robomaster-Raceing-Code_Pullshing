#ifndef __DR16__H_
#define __DR16__H_

#include "Users.h"
/*DR16�շ��ṹ��Ĵ�����Ϊ22u������4λ���Լ������NULLλ*/
extern uint8_t DR16_Buff[18u+4]; 

/*DR16���ݴ���ṹ��*/
extern DR16_DBUS_DATA_st DR16;

/*���Ҹ����ݴ���*/
extern rocker_st rocket_Left,rocket_Right;

/*���̣�����������ݴ���*/
extern Key_st keyBorad;
extern Key_st MouseKeyLeft;
extern Key_st MouseKeyRight;


//���������¶�Ӧֵ
#define DR16_SWITCH_UP			1
#define DR16_SWITCH_MID			3
#define DR16_SWITCH_DOWN		2

/***************************funtions*************************/
/*DR16ң������ʼ��*/
void DR16_Init(void);
/*��λֵ����������ֵ������Ϳ���*/
void DR16_Key_Whether_Process(uint16_t KeyStatus, Key_st *key);
/*����ѹ��*/
int Data_Suppres(int16_t data);
/*���ݽ��*/
void DR16_Process(uint8_t *pData);
/*��ȡң�������ұ�ҡ�˵�ֵ�����̣���ģʽ���ƣ�*/
int GetSwitch_ModeChassis(void);
/*��ȡң�������ұ�ҡ�˵�ֵ����̨����ģʽ���ƣ�*/
int GetSwitch_ModeCloud(void);
/*��ȡ�ܵ�ң�������ұ�ҡ�˵�ֵ����ģʽ�����ж�����ʹ�ã���ģʽ���ƣ�*/
int GetSwitch_Mode(void);
#endif

