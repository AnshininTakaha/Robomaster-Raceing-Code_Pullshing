#ifndef __DR16__H_
#define __DR16__H_

#include "Users.h"
/*DR16收发结构体的储存量为22u，其中4位是自己定义的NULL位*/
extern uint8_t DR16_Buff[18u+4]; 

/*DR16数据储存结构体*/
extern DR16_DBUS_DATA_st DR16;

/*左右杆数据储存*/
extern rocker_st rocket_Left,rocket_Right;

/*键盘，鼠标左右数据储存*/
extern Key_st keyBorad;
extern Key_st MouseKeyLeft;
extern Key_st MouseKeyRight;


//拨杆上中下对应值
#define DR16_SWITCH_UP			1
#define DR16_SWITCH_MID			3
#define DR16_SWITCH_DOWN		2

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
#endif

