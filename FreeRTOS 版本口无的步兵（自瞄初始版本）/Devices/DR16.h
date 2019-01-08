#ifndef __DR16__H_
#define __DR16__H_

#include "Users.h"
/*DR16收发结构体的储存量为22u，其中4位是自己定义的NULL位*/
extern uint8_t DR16_Buff[18u+4]; 

/*DR16数据储存结构体*/
extern DR16_DBUS_DATA_st DR16;

/*左右杆数据储存*/
extern rocker_st rocket_Left,rocket_Right;
extern rocker_st pcRocket;
/*键盘，鼠标左右数据储存*/
extern Key_st keyBorad;
extern Key_st MouseKeyLeft;
extern Key_st MouseKeyRight;


//拨杆上中下对应值
#define DR16_SWITCH_UP			1
#define DR16_SWITCH_MID			3
#define DR16_SWITCH_DOWN		2


/*-------键盘键值 Begin------*/
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
/*-------键盘键值 End------*/
#define FULL_MATCH			0x01
#define HAVE_MATCH			0x00
/***************************funtions*************************/
/*DR16遥控器初始化*/
void DR16_Init(void);
/*键位值（包含鼠标的值）输出和控制*/
void DR16_Key_Whether_Process(uint16_t KeyStatus, Key_st *key);
/*数据压制*/
int Data_Suppres(int16_t data);
/*数据解包*/
void DR16_Process(uint8_t *pData);
/*获取遥控器的右边摇杆的值（底盘）（模式控制）*/
int GetSwitch_ModeChassis(void);
/*获取遥控器的右边摇杆的值（云台）（模式控制）*/
int GetSwitch_ModeCloud(void);
/*获取总的遥控器的右边摇杆的值（总模式，在中断里面使用）（模式控制）*/
int GetSwitch_Mode(void);
/*判断是否跳变，按下键位跳变*/
uint16_t Keyboard_WhetherJumpKey(uint16_t KeyCode, uint8_t mode);
uint16_t Keyboard_WhetherPressedKey(uint16_t KeyCode, uint8_t mode);
#endif

