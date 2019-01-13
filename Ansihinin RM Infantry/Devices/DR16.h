#ifndef _DR16_H
#define _DR16_H


#include "KEY.h"
#include "USART.h"
#include <stdbool.h>
#include "mathing.h"




#pragma anon_unions

/*遥控器结构体*/
typedef struct
{
		/*遥控器变量*/
    struct 
		{
        int16_t ch0;
        int16_t ch1;
        int16_t ch2;
        int16_t ch3;

        uint8_t s_left;
        uint8_t s_right;
    } rc;
		
		/*电脑变量*/
    struct
    {
        int16_t x;
        int16_t y;
        int16_t z;

        uint8_t keyLeft;
        uint8_t keyRight;

    } mouse;

		/*键盘变量*/
    union
    {
        uint16_t key_code;
        struct 
				{
					
					 
					//WASDQE
            bool press_W:1;
            bool press_S:1;
            bool press_A:1;
            bool press_D:1;
						bool press_Shift:1;
            bool press_Ctrl:1;
            bool press_Q:1;
            bool press_E:1;
   
					/*功能性组合键*/
            bool press_R:1;
            bool press_F:1;
            bool press_G:1;
            bool press_Z:1;
            bool press_X:1;
            bool press_C:1;
            bool press_V:1;
            bool press_B:1;
           
        };
    } keyBoard;
		
	/*帧率控制（判断是否离线）*/
	uint16_t UpdateFrame;
	uint8_t OFFLINE_SET;
		
} DR16_t;
/*左右遥感结构体*/
typedef struct
{
    float x;
    float y;
    float radian;
    float degrees;
    float distance;
} rocker_t;


extern uint8_t DR16_Buff[18u+2]; 
extern DR16_t DR16;


/*DR16初始化*/
void DR16_Init(void);

/*DR16遥控解码*/
void DR16_Process(uint8_t *pData);

/*数据压制*/
int Data_Suppres(int16_t data);

/*单个遥控杆的数值传递*/
void Rocker_Stander(float positionX, float positionY, rocker_t *rocket);





#endif
