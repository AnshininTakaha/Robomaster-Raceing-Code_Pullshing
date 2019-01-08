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
/*接收机整包（也就是整一个数据包的大小）*/
//#define DR16_DBUS_PACKSIZE 		18u		

/*全调用，方便其他函数的使用*/
extern uint8_t DR16_rxBuff[18u+2];
extern DR16_DBUS_DATA_t dr16_data;

extern rocker_t dr16_rocker_L,dr16_rocker_R;
extern rocker_t pcRocker;



/*DR16鼠标按键处理判断*/
static void DR16_mouseKeyProcess(key_t *key);

/*DR16接收器初始化*/
void DR16_receiverInit(void);

/*DR16接收数据处理*/
void DR16_dataProcess(uint8_t *pData);

/*数据压制*/
int Data_Suppress(int16_t Data_Unsuppress);
#endif
