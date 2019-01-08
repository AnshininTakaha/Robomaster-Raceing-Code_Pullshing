#ifndef __DR16__H_
#define __DR16__H_

#include "Users.h"
/*DR16�շ��ṹ��Ĵ�����Ϊ22u������4λ���Լ������NULLλ*/
extern uint8_t DR16_Buff[18u+4]; 

/*DR16���ݴ���ṹ��*/
extern DR16_DBUS_DATA_st DR16;

/*���Ҹ����ݴ���*/
extern rocker_st rocket_Left,rocket_Right;
extern rocker_st pcRocket;
/*���̣�����������ݴ���*/
extern Key_st keyBorad;
extern Key_st MouseKeyLeft;
extern Key_st MouseKeyRight;


//���������¶�Ӧֵ
#define DR16_SWITCH_UP			1
#define DR16_SWITCH_MID			3
#define DR16_SWITCH_DOWN		2


/*-------���̼�ֵ Begin------*/
#define KEYBOARD_PRESSED_NONE 	0x0000

#define KEYBOARD_PRESSED_W 		0x0001
#define KEYBOARD_PRESSED_S 		0x0002
#define KEYBOARD_PRESSED_A 		0x0004
#define KEYBOARD_PRESSED_D 		0x0008
#define KEYBOARD_PRESSED_SHIFT 	0x0010
#define KEYBOARD_PRESSED_CTRL 	0x0020
#define KEYBOARD_PRESSED_Q  	0x0040
#define KEYBOARD_PRESSED_E 		0x0080

#define KEYBOARD_PRESSED_R		0x0100
#define KEYBOARD_PRESSED_F		0x0200
#define KEYBOARD_PRESSED_G		0x0400
#define KEYBOARD_PRESSED_Z		0x0800
#define KEYBOARD_PRESSED_X		0x1000
#define KEYBOARD_PRESSED_C		0x2000
#define KEYBOARD_PRESSED_V		0x4000
#define KEYBOARD_PRESSED_B		0x8000
/*-------���̼�ֵ End------*/
#define FULL_MATCH			0x01
#define HAVE_MATCH			0x00
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
/*�ж��Ƿ����䣬���¼�λ����*/
uint16_t Keyboard_WhetherJumpKey(uint16_t KeyCode, uint8_t mode);
uint16_t Keyboard_WhetherPressedKey(uint16_t KeyCode, uint8_t mode);
#endif

