#ifndef __DR16
#define __DR16

/*总引导函数*/
#include "Users.h"

#define DR16_DBUS_PACKSIZE 		18u		//接收机包大小

#define DR16_ROCKER_MAXVALUE 		660		//遥控摇杆最大值

//拨杆上中下对应值
#define DR16_SWITCH_UP			1
#define DR16_SWITCH_MID			3
#define DR16_SWITCH_DOWN		2

#define MOUSEKEY_NONE 	0x00
#define MOUSEKEY_LEFT 	0x01
#define MOUSEKEY_RIGHT 	0x02

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

#define KEY_FULL_MATCH			0x01
#define KEY_HAVE_MATCH			0x00

/*全调用，方便其他函数的使用*/
extern uint8_t DR16_rxBuff[18u+2];
extern DR16_DBUS_DATA_t dr16_data;

extern rocker_t dr16_rocker_L,dr16_rocker_R;
extern rocker_t pcRocker;

extern key_t dr16_keyBorad;
extern key_t dr16_mouseKeyLeft;
extern key_t dr16_mouseKeyRight;

/*DR16鼠标按键处理判断*/
//static void DR16_mouseKeyProcess(key_t *key);
void DR16_KeypointProcess(uint16_t KeyStatus, key_t *key);
/*DR16接收器初始化*/
void DR16_receiverInit(void);

/*检测按键跳变*/
uint16_t dr16_keyboard_isJumpKey(uint16_t KeyCode, uint8_t mode);
/*检测按键按下*/
uint16_t dr16_keyboard_isPressedKey(uint16_t KeyCode, uint8_t mode);

/*DR16接收数据处理*/
void DR16_dataProcess(uint8_t *pData);

/*数据压制*/
int Data_Suppress(int16_t Data_Unsuppress);
#endif
