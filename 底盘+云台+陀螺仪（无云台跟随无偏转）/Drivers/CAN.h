#ifndef __CAN
#define __CAN

#include "Users.h"


/*CAN1���ٶ���*/
void CAN1_QuickInit(void);

/*CANx�������ݺ���*/
void CAN_SendData(CAN_TypeDef* CANx, uint8_t id_type, uint32_t id, uint8_t data[8]);



#endif

