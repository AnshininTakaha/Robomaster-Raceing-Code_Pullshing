#ifndef __PC_control__H
#define __PC_control__H

#include "Users.h"
extern pc_st pc;

#define Double_Press (Keyboard_WhetherJumpKey(KEYBOARD_PRESSED_SHIFT,FULL_MATCH) && Keyboard_WhetherJumpKey(KEYBOARD_PRESSED_CTRL,FULL_MATCH))

/*速度机制测试（速度测试）*/
#define Speed_S 2200
#define Speed_N 4400
#define Speed_F 6600

/***************************funtions*************************/
/*PC模式初始化*/
void PC_MODE_Init(void);
/*判断Ctrl和Shift的键位模式*/
void Whether_CtrlANDShift_ChangeMode(void);
/*方向处理*/
void Direction_Dealing(rocker_st *rocker);
#endif

