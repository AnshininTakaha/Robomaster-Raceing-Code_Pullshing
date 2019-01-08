#ifndef __CAN
#define __CAN

#include "Users.h"


/*CAN1快速定义*/
void CAN1_QuickInit(void);

/*CANx发送数据函数*/
void CAN_SendData(CAN_TypeDef* CANx, uint8_t id_type, uint32_t id, uint8_t data[8]);



#endif

