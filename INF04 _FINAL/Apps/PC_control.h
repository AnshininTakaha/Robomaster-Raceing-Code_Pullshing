#ifndef __PC_control__H
#define __PC_control__H

#include "Users.h"
extern pc_st pc;

#define Double_Press (Keyboard_WhetherJumpKey(KEYBOARD_PRESSED_SHIFT,FULL_MATCH) && Keyboard_WhetherJumpKey(KEYBOARD_PRESSED_CTRL,FULL_MATCH))

/*�ٶȻ��Ʋ��ԣ��ٶȲ��ԣ�*/
#define Speed_S 2200
#define Speed_N 4400
#define Speed_F 6600

/***************************funtions*************************/
/*PCģʽ��ʼ��*/
void PC_MODE_Init(void);
/*�ж�Ctrl��Shift�ļ�λģʽ*/
void Whether_CtrlANDShift_ChangeMode(void);
/*������*/
void Direction_Dealing(rocker_st *rocker);
#endif

