#ifndef __DR16
#define __DR16

/*����������*/
#include "Users.h"

#define DR16_DBUS_PACKSIZE 		18u		//���ջ�����С

#define DR16_ROCKER_MAXVALUE 		660		//ң��ҡ�����ֵ

//���������¶�Ӧֵ
#define DR16_SWITCH_UP			1
#define DR16_SWITCH_MID			3
#define DR16_SWITCH_DOWN		2

#define MOUSEKEY_NONE 	0x00
#define MOUSEKEY_LEFT 	0x01
#define MOUSEKEY_RIGHT 	0x02
/*���ջ�������Ҳ������һ�����ݰ��Ĵ�С��*/
//#define DR16_DBUS_PACKSIZE 		18u		

/*ȫ���ã���������������ʹ��*/
extern uint8_t DR16_rxBuff[18u+2];
extern DR16_DBUS_DATA_t dr16_data;

extern rocker_t dr16_rocker_L,dr16_rocker_R;
extern rocker_t pcRocker;



/*DR16��갴�������ж�*/
static void DR16_mouseKeyProcess(key_t *key);

/*DR16��������ʼ��*/
void DR16_receiverInit(void);

/*DR16�������ݴ���*/
void DR16_dataProcess(uint8_t *pData);

/*����ѹ��*/
int Data_Suppress(int16_t Data_Unsuppress);
#endif
