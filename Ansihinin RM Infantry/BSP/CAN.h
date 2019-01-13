#ifndef _CAN_H
#define _CAN_H

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "NVIC.h"

/*CAN1快速初始化*/
void CAN1_QuickInit(void);
/*CAN发送数值*/
void CAN_SendData(CAN_TypeDef* CANx, uint8_t id_type, uint32_t id, uint8_t data[8]);






#endif
