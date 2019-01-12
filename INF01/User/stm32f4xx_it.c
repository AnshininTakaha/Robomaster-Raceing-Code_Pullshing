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
		if(USART_GetITStatus(USART1,USART_IT_IDLE) != RESET)
		{
			DMA_Cmd(DMA2_Stream2,DISABLE);
			
			if(DMA_GetCurrDataCounter(DMA2_Stream2) == 4)
			{
				DR16_Process(DR16_Buff);
			}
			
			DMA_SetCurrDataCounter(DMA2_Stream2,18u+4);
			
			DMA_Cmd(DMA2_Stream2,ENABLE);
			
			/*清除空闲中断标志位*/
			(void)USART1->DR;
      (void)USART1->SR;
			//串口空闲中断标志位并不能通过下面的函数清除
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
  * @brief  CAN1 FIFO0 接收中断服务函数
  * @param  None
  * @retval None
  */
void CAN1_RX0_IRQHandler(void)
	{
		CanRxMsg CAN1Feedback_Msg;
		
		if(CAN_GetITStatus(CAN1,CAN_IT_FMP0))
		{
			/*接受到的储存到CAN1Feedback_Msg*/
			CAN_Receive(CAN1,CAN_FIFO0,&CAN1Feedback_Msg);
			/*分析电机接受到的报文*/
			Analysis_getinfo(CAN1Feedback_Msg);
			
			CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
		}
	}


/**
  * @brief  TIM6 DAC 中断服务函数
  * @param  None
  * @retval None
  */

float Chassis_Vx = 0.0f,Chassis_Vy = 0.0f,Chassis_VOmega = 0.0f;
void TIM6_DAC_IRQHandler(void)//各种模式对应的速度模型处理
{
	/*counter计时器*/
	static int counter = 0.0f;
	/*底盘运动速度*/
	
	/*云台运动速度*/
	float Cloud_delta_Yaw = 0.0f,Cloud_delta_Pitch = 0.0f;
	
	
	if(TIM_GetITStatus(TIM6,TIM_IT_Update))
	{
		 if(++counter > 100)
        {
           GPIO_ToggleBits(GPIOE,GPIO_Pin_7);
           counter = 0;
        }
	
			switch(GetSwitch_Mode())
			{
				case Status_ControlOFF:
					Chassis_Vx = 0;Chassis_Vy = 0;Chassis_VOmega = 0;
					break;
				
				case Status_ControlByRC:
					Chassis_Vx = rocket_Left.x /660 *Chassis_MaxSpeed_X;
					Chassis_Vy = rocket_Left.y /600 *Chassis_MaxSpeed_Y;
					Chassis_VOmega = rocket_Right.x /600 *Chassis_MaxSpeed_W;
					
					break;
				case Status_ControlByPC:
					break;
			}
			
			Chassis_Process(Chassis_Vx,Chassis_Vy,Chassis_VOmega,GetSwitch_Mode());
	
	
	
	
				
		
		TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
	}
}

int DMR_counter = 0;
void TIM7_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM7,TIM_IT_Update)!= RESET)
	{
		
		if(++DMR_counter >20)//50ms =TIM7 *5
		{
			GPIO_ToggleBits(GPIOF,GPIO_Pin_14);
			DeviceFlash_Process();
      DMR_counter = 0;
		}

		TIM_ClearITPendingBit(TIM7,TIM_IT_Update);
	}
}

/**
  * @}
  */ 

/**
  * @}
  */ 


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
