#ifndef KEY_H
#define KEY_H

#include "Users.h"

#define	KEY_ON	 1		//��������
#define	KEY_OFF	 0		//�����ſ�

#define KEY_COUNT 1


#define KEY_GPIO_CLK             	RCC_AHB1Periph_GPIOD
#define KEY_PIN                  	GPIO_Pin_10
#define KEY_GPIO_PORT           	GPIOD




extern key_t userKeyList[KEY_COUNT];

void KEY_Init(void);
void Key_point(void);
void Key_Scan(void);






#endif