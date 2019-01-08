/**
  ******************************************************************************
  * @file    GPIO/GPIO_IOToggle/stm32f4xx_it.c 
  * @author  MCD Application Team
  * @version V1.8.0
  * @date    04-November-2016
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"


/** @addtogroup STM32F4xx_StdPeriph_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief   This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}



		



/******************************************************************************/
/*                 STM32F4xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f40xx.s/startup_stm32f427x.s/startup_stm32f429x.s).    */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @brief  USART1中断服务函数【遥控器，鼠标控制等数据的处理】
  * @param  None
  * @retval None
  */
	//检查数据包是否传输完毕
void USART1_IRQHandler(void)
	{
		if(USART_GetITStatus(USART1, USART_IT_IDLE) != RESET)//判断USART1的是否【不处于】空闲中断，如果 【不处于】空闲中断则进入if条件语句
	{
		//关闭DMA，USART1_RX_DMA_STREAM = DMA2_Stream2
		DMA_Cmd(DMA2_Stream2, DISABLE);
		
		//printf("%d\n",DMA_GetCurrDataCounter(USART1_RX_DMA_STREAM));
		//获取DMAbuff剩余大小，是否匹配
		//如果DMA剩余的数据流大小等于2
		//uint8_t DR16_rxBuff[DR16_DBUS_PACKSIZE+2]
		//这个时候剩下的 DR16_DBUS_PACKSIZE 是空包，也就是说数据完全传输完毕了，可以进行数据的传输和解码了
		if (DMA_GetCurrDataCounter(DMA2_Stream2) == 2)
		{
			//printf("%s\n", DR16_rxBuff);
			
			DR16_dataProcess(DR16_rxBuff);//进行DR16接收数据处理，解码和遥控器四个chx进行数据归零
		}
		
		//再次设置传输数据长度，+2保证安全，所以前面判断的时候是2，代表数据包 DR16_DBUS_PACKSIZE 空包
    DMA_SetCurrDataCounter(DMA2_Stream2,18u+2);
		//重新打开DMA进行数据的接受
		DMA_Cmd(DMA2_Stream2, ENABLE);
		
		
		//清除空闲中断标志位
		(void)USART1->DR;
		(void)USART1->SR;
		//串口空闲中断标志位并不能通过下面的函数清除【重点】
		//USART_ClearITPendingBit(USART1, USART_IT_IDLE);
	}
	}


/**
  * @brief  USART2中断服务函数【裁判系统】
  * @param  None
  * @retval None
  */
void USART2_IRQHandler(void)
	{
		
	}

/**
  * @brief  USART3中断服务函数【GY_IMU】
  * @param  None
  * @retval None
  */
void USART3_IRQHandler(void)
{
		if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)
	{
		//关闭DMA
		DMA_Cmd(DMA1_Stream1, DISABLE);
		
		/*计算长度*/
		uint16_t DMA_Counter = DMA_GetCurrDataCounter(DMA1_Stream1);
		
		GY_IMU_getInfo(Cloud_GY_IMU_RXBUFF, 30-DMA_Counter, &Cloud_IMU);
		
		
		//设置传输数据长度
    DMA_SetCurrDataCounter(DMA1_Stream1,30);
		//打开DMA
		DMA_Cmd(DMA1_Stream1, ENABLE);
		
		
		//清除空闲中断标志位
		(void)USART3->DR;
		(void)USART3->SR;
		//串口空闲中断标志位并不能通过下面的函数清除
		//USART_ClearITPendingBit(USART1, USART_IT_IDLE);
	}
}

	
	
/**
  * @brief  CAN1 FIFO0 接收中断服务函数
  * @param  None
  * @retval None
	* @funtion 使用CAN1的挂起中断来返回轮子的报文
  */
void CAN1_RX0_IRQHandler(void)
	{
		/*启用CAN 发送的结构体*/
		CanRxMsg RxMessage;	
		
		if(CAN_GetITStatus(CAN1, CAN_IT_FMP0))//如果检测到挂起中断
		{
			CAN_Receive(CAN1,CAN_FIFO0,&RxMessage);//接受收到的数据
			
			/*因为全部的数据都是通过CAN1来接受的，所以接受回来之后还要看是哪一个的消息，也就是说要判断*/
			/*下面的函数是通过判断返回的ID的同时对数据进行解包*/
			/*通过解包来获得可能需要用到的值*/
			
			/*M3508是轮子的电机*/
			M3508_getInfo(RxMessage);//获取电机返回的报文
			
			/*M6623是云台的电机*/
			M6623_getInfo(RxMessage);
			
			/*M2006是拨弹电机*/
			//M2006_getInfo(RxMessage);//拨弹电机
			
			/*可以通过这个代码来看返回的数值是什么*/
			/*在调试的时候好好的利用这个东西哦QAQ！*/
			/*printf("id %x, data %x, T%x, IL%x, IH%x, SL%x, SH%x, AL%x, AH%x\n", RxMessage.StdId, RxMessage.Data[7],
																				RxMessage.Data[6],
																				RxMessage.Data[5],
																				RxMessage.Data[4],
																				RxMessage.Data[3],
																				RxMessage.Data[2],
																				RxMessage.Data[1],
																				RxMessage.Data[0]);*/
			
			CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);//清楚中断标志位
			
		}
	}

#if old_control_proment
/**
  * @brief  TIM6 DAC 中断服务函数
  * @param  None
  * @retval None
  */
void TIM6_DAC_IRQHandler(void)//各种模式对应的速度模型处理
{
	/*检测到TIM6中断*/
	if(TIM_GetITStatus(TIM6 ,TIM_IT_Update) != RESET)
	{
		/*设置储存函数*/
		static int counter = 0;//次数计算
		float Chassis_Vx = 0.0f, Chassis_Vy = 0.0f, Chassis_VOmega = 0.0f;//底盘对应的X,Y,Omega的值

		
		/*因为是云台的部分所以先不用*/
		float Cloud_deltaPitch = 0.0f;
		float Cloud_deltaYaw = 0.0f;		
		uint8_t shoot = 0;
		
		
		if(++counter >100)
		{
//			LED_GREEN_TOGGLE();
			/*每刷新100次翻转一下绿色的灯，便于观察*/
			GPIO_ToggleBits(GPIOE,GPIO_Pin_7);
			counter = 0;
		}
		
		
		/*************Chassis_BEGIN底盘控制处理开始****************/
		/*遥控器的左上角右上角的小拉杆是可以通过USART1发送数据接收的*/
		/*通过判断那两个东西来决定数据*/
		/*遥控器模式*/
		
		if(dr16_data.rc.s_left == Status_ControlByRC)
		{
			/*调试的时候方便瞬间停止*/
			if(dr16_data.rc.s_right != 3)
			{
				Chassis_Vx = dr16_rocker_L.x*5.0f;
				Chassis_Vy = (dr16_rocker_L.y/*+dr16_rocker_R.y*/)*5.0f;
				Chassis_VOmega = dr16_rocker_R.x*5.0f /*Cloud_getYawOverFlow()*6.0f*/;
				
				/*倒车*/
				if(Chassis_Vx < 0)
				{
					Chassis_VOmega = -Chassis_VOmega;
				}
				
			}
		}
		/*PC控制模式*/
		else if(dr16_data.rc.s_left == Status_ControlByPC)
		{
			Chassis_Vx = pcRocker.x*3.0f;
			Chassis_Vy = pcRocker.y*3.0f;
			Chassis_VOmega = pcRocker.degrees*3.0f/* + Cloud_getYawOverFlow()*14.0f*/;
		}
		
		Chassis_processing(Chassis_Vx, Chassis_Vy, Chassis_VOmega, dr16_data.rc.s_left);//dr16_data.rc.s_left就是遥控器左边摇杆对应的模式
		
		/*************Cloud_BEGIN云台部分****************/
		//云台处理代码
		
		if(dr16_data.rc.s_left == Status_ControlByRC)
		{//使用遥控器控制云台
			Key_Scan();
			if(dr16_data.rc.s_right == 3)
			{
				Cloud_deltaYaw = (dr16_rocker_R.x)/5;      //通过遥控器控制x轴欧拉角
				Cloud_deltaPitch = (dr16_rocker_R.y)/5;    //通过遥控器控制y轴欧拉角
			}
			shoot = userKeyList[0].keyPressedJump || dr16_data.rc.s_right ==1;//和上面的一样，按键跳变判定
		}
		else if(dr16_data.rc.s_left == Status_ControlByPC)
		{//通过PC控制
			Cloud_deltaYaw = dr16_data.mouse.x*5.0f;
			Cloud_deltaPitch = dr16_data.mouse.y*5.0f;
			
			shoot = dr16_data.mouse.keyLeft.keyPressedJump;
		}
		
		
		
		Cloud_processing(Cloud_deltaYaw, Cloud_deltaPitch, shoot, dr16_data.rc.s_left);
		
		TIM_ClearITPendingBit(TIM6 , TIM_IT_Update); 
	}
}
#else

float YawRad = 0.0f;
float Chassis_Vx = 0.0f,Chassis_Vy = 0.0f, Chassis_VOmega = 0.0f;
/**
  * @brief  TIM6 DAC 中断服务函数
  * @param  None
  * @retval None
  */
void TIM6_DAC_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM6,TIM_IT_Update) != RESET)
	{
		//闪灯计数器
		static int counter = 0.0f;
		//底盘运动
		
		//云台
		float Cloud_delta_Yaw = 0.0f,Cloud_delta_Pitch = 0.0f;
		
		//闪灯
		if(++counter > 100)
		{
			GPIO_ToggleBits(GPIOE,GPIO_Pin_7);
			counter = 0;
		}
		
		//这里其实已经在右杆判断了
		switch(Control_getMode())
		{
			case ControlMode_ByRC:
				//超级电容开关code...
			
				//按键识别
				Key_Scan();
			  //模式设置
				Cloud.mode = Cloud_Mode_WithIMU;
				Chassis.mode =  Chassis_Mode_Follow;
			
				//底盘取值(比例控制)
			  //因为是用的云台追踪所以没有VOmage
				
			Chassis_Vx = dr16_rocker_L.x / DR16_ROCKER_MAXVALUE * Chassis_MaxSpeed_X;
			Chassis_Vy = dr16_rocker_L.y / DR16_ROCKER_MAXVALUE * Chassis_MaxSpeed_Y;
				
				//云台取值（叠加法）
				Cloud_delta_Yaw = dr16_rocker_R.x /8;
				Cloud_delta_Pitch = dr16_rocker_R.y/7;
				

				break;
				
				case ControlMode_OFF:
				break;
			
			
		}
		
		
		/*云台跟随判断*/				
			if(Cloud.mode == Cloud_Mode_WithIMU)
			{
				/*计算距离中间的角度值，然后转黄成为弧度进行计算*/
				YawRad = Get_Cloud_YAWAngle_withCenter()*DEG_TO_RAD;
				/*保存及时的横向方向的值，然后进行计算*/
				float temp_Vx = Chassis_Vx;
				Chassis_Vx = Chassis_Vx*cos(YawRad) - Chassis_Vy*sin(YawRad);
				Chassis_Vy = Chassis_Vy*cos(YawRad) + temp_Vx*sin(YawRad);
			}
			/*解算*/
				Chassis_processing(Chassis_Vx, Chassis_Vy, Chassis_VOmega, Control_getMode());
			
			switch(Cloud.mode)
			{
			case Cloud_Mode_Normal:
				Cloud_processing_Normal(Cloud_delta_Yaw, Cloud_delta_Pitch, Control_getMode());
			break;
			
			case Cloud_Mode_WithIMU:
				Cloud_processing_WithIMU(Cloud_delta_Yaw, Cloud_delta_Pitch, Control_getMode());
			break;
			}
			
			TIM_ClearITPendingBit(TIM6 , TIM_IT_Update);
			
	}
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
