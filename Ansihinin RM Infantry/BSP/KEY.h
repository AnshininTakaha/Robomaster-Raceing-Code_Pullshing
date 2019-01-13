#ifndef _KEY_H
#define _KEY_H


#include "stm32f4xx.h"
#include "stdint.h"
typedef struct
{
	uint16_t key_Status;
	uint16_t last_key_Status;
	uint16_t key_dowm_point;
	uint16_t key_up_point;
	uint16_t key_longpress_point;
	uint16_t pointing_time;
}Key_st;

/*°´¼üÅÐ¶Ï*/
void DR16_Key_Whether_Process(uint16_t KeyStatus, Key_st *key);






#endif
