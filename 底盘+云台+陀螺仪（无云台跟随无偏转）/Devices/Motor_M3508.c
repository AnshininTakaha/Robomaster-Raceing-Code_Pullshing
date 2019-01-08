/**
  ******************************************************************************
  * @file    M3508_Motor.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   M3508无刷电机，配套C620电调驱动应用函数接口
  ******************************************************************************
  */

#include "Motor_M3508.h"

/*定义一个储存的共用体*/
M3508s_t M3508s[4];

/**
  * @brief  从CAN报文中获取M3508电机信息
  * @param  *RxMessage 	CAN报文接收结构体指针
  *			**info		M3508s_t电机数组指针
  * @retval None
  */
void M3508_getInfo(CanRxMsg RxMessage)
	{
	/*报文ID确认，看看是不是四个轮子其中的一个*/
	/*如果不是的话就跳过*/
	/*为什么STDID要放在下面赋值？
	方便赋值，不需要赋值判断之后再次赋值，比较的方便*/
	if((RxMessage.StdId < 0x201) || (RxMessage.StdId > 0x204))
		return;
	
	/*在检验之后才定义对应需要储存的STDID，方便操作和加快运行的速度*/
	uint32_t StdId;
	
	/*计算出现在对应的ID对应的编号（分别是1、2、3、4），方便后面的赋值操作*/
	StdId = RxMessage.StdId - 0x201;
	
	/*解包数据，数据格式详见C620电调说明书P33*/
	M3508s[StdId].realAngle = (uint16_t)(RxMessage.Data[0]<<8 | RxMessage.Data[1]); //转子机械角度高8位和低8位
	
	M3508s[StdId].realSpeed = (int16_t)(RxMessage.Data[2]<<8 | RxMessage.Data[3]);  //转子转速高8位和低8位
	
	M3508s[StdId].realCurrent = (int16_t)(RxMessage.Data[4]<<8 | RxMessage.Data[5]);//实际转矩高8位和低8位
	
	M3508s[StdId].temperture = RxMessage.Data[6];                                   //电机温度
	
	M3508s[StdId].infoUpdateFlag = 1;                                               //是否可以更新的标志位
}	



/**
  * @brief  设置M3508电机电流值（id号为1~4）
  * @param  iqx (x:1~4) 对应id号电机的电流值，范围-16384~0~16384
  * @retval None
  */
void M3508_setCurrent(int16_t iq1, int16_t iq2, int16_t iq3, int16_t iq4)
{

	uint8_t data[8];
	
	//数据格式详见说明书P32
	data[0] = iq1 >> 8;
	data[1] = iq1;
	data[2] = iq2 >> 8;
	data[3] = iq2;
	data[4] = iq3 >> 8;
	data[5] = iq3;
	data[6] = iq4 >> 8;
	data[7] = iq4;
	
	/*通过CAN1给四个轮子发送对应的电流*/
	/*发到基地址，数据格式会按照格式开始编排，达到给电机赋电流的目的*/
	CAN_SendData(CAN1, CAN_ID_STD, 0x200, data);
	
}	

