#ifndef _PCControl_H
#define _PCControl_H


#include "stm32f4xx.h"
#include "DR16.h"

typedef struct
{
	uint16_t PCMode;
	uint16_t NowStatus;

	uint16_t Shift_Open;
	uint16_t Ctrl_Open;
  	uint16_t Right_M_Open;
	uint16_t Vision_shooting;
}pc_t;

extern pc_t pc;
void PC_MODE_Init(void);



#endif
