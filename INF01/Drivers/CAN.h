#ifndef __CAN_H
#define __CAN_H

#include "Users.h"

/***************************funtions*************************/

/*CAN1���ٳ�ʼ��*/
void CAN1_QuickInit(void);


/*CAN������ֵ*/
void CAN_SendData(CAN_TypeDef* CANx, uint8_t id_type, uint32_t id, uint8_t data[8]);


#endif
