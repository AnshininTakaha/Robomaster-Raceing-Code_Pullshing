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
#include "FreeRTOS.h"
#include "task.h"
extern void xPortSysTickHandler( void );

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
//void SVC_Handler(void)
//{
//}

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
//void PendSV_Handler(void)
//{
//}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	if(xTaskGetSchedulerState()!=taskSCHEDULER_NOT_STARTED)//系统已经运�??
    {
        xPortSysTickHandler();	
    }
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
  * @brief  USART1ң���������ж�
  * @param  None
  * @retval None
  */
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
		
		/*USART1�����ж�*/
		(void)USART1->DR;
    	(void)USART1->SR;
		//ע��������仰��û�а취����жϵ�
     	//USART_ClearITPendingBit(USART1, USART_IT_IDLE);
	}
	
}


/**
  * @brief  USART2�����жϣ����飩
  * @param  None
  * @retval None
  */
	int cv_x,cv_y;
	int x_ILF,y_ILF;
	int last_cv_x,last_cv_y;
	int HC_X,HC_Y;
	int USARTCounter = 0;

	int NControl;
	int SendConunter = 0;
void USART2_IRQHandler(void)
{
	DMA_Cmd(USART2_RX_DMA_STREAM, DISABLE);
		
	//	uint16_t DMA_Counter = DMA_GetCurrDataCounter(USART2_RX_DMA_STREAM);
		
	int x,y;
	if(SendConunter++ > 1000)
	{
		GPIO_ToggleBits(GPIOF,GPIO_Pin_14);
		SendConunter = 0;
	}

	if(CV_RXBUFF[0] == 'S')
	{
		if(sscanf(CV_RXBUFF, "S%d,%d", &x,&y) == 2)//ɨ����Ч��ֵΪ2
		{
			/*x�����*/
			// if(abs(x) > 320 && abs(x) < 370)
			// {
				Cloud.YAW_Attitude_pid.Kp = -1.5;
				Cloud.YAW_Attitude_pid.Ki = -0.0;
				Cloud.YAW_Attitude_pid.Kd = -0.2;
			// }
			
	
			/*y�����*/
				// RM6623s[1].pid_angle.Kp = 1.18;
			if(y > 240  && y < 480)
			{
				RM6623s[1].pid_angle.Kp = 1.8;
				RM6623s[1].pid_angle.Ki = 0.0;
				RM6623s[1].pid_angle.Kd = 1.2;
			}
			else
			{
				RM6623s[1].pid_angle.Kp = 2.1;
				RM6623s[1].pid_angle.Ki = 0.0;
				RM6623s[1].pid_angle.Kd = 1.2;
			}
			
			
			
			
/*С����ͷ����λ�ã�640*480��*/
			Filter_IIRLPFINT(&x,&x_ILF,0.6);
			Filter_IIRLPFINT(&y,&y_ILF,0.4);
			USARTCounter++;
			cv_x = x_ILF-320;
			cv_y = y_ILF-240;
			
/*������ͷ����λ�ã�1280*1024��*/
			// Filter_IIRLPFINT(&x,&x_ILF,0.6);
			// Filter_IIRLPFINT(&y,&y_ILF,0.4);
			
			// cv_x = x_ILF-640;
			// cv_y = y_ILF-512;

				
			last_cv_x = cv_x;
			last_cv_y = cv_y;
		}		
	}

	// else if(CV_RXBUFF[0] == 'N')
	// {
		
	//   if(sscanf(CV_RXBUFF, "N%d", &NControl) == 1)
	// 	{
			
	// 		if(NControl == 1000000)
	// 		{
	// 			// cv_x = 0;
	// 			// cv_y = 0;
	// 		}
	// 		else if(NControl == 2000000)
	// 		{
	// 			// cv_x = -25;
	// 			// cv_y = 0;
	// 			// text = 1;
	// 		}
	// 		else if(NControl == 3000000)
	// 		{
	// 			// cv_x = 25;
	// 			// cv_y = 0;
	// 		}
	// 	}		
	// }

		
		
	//�����жϳ���
  DMA_SetCurrDataCounter(USART2_RX_DMA_STREAM,10);
	//��������DMA
	DMA_Cmd(USART2_RX_DMA_STREAM, ENABLE);
		
		
	//���USART2�жϱ�־λ
	(void)USART2->DR;
	(void)USART2->SR;
}
	

	
/**
  * @brief  USART3��̨IMU�����ж�
  * @param  None
  * @retval None
  */
void USART3_IRQHandler(void)
{
	
	if(USART_GetITStatus(USART3, USART_IT_IDLE) != RESET)
	{
		//DMA����
		DMA_Cmd(USART3_RX_DMA_STREAM, DISABLE);
		
		uint16_t DMA_Counter = DMA_GetCurrDataCounter(USART3_RX_DMA_STREAM);
		
		GY_IMU_getInfo(Cloud_GY_IMU_RXBUFF, GY_IMU_BUFFSIZE-DMA_Counter, \
		&Cloud_IMU);
		
		
		//�����ܽ��ܳ���
    	DMA_SetCurrDataCounter(USART3_RX_DMA_STREAM,GY_IMU_BUFFSIZE);
		//��������DMA
		DMA_Cmd(USART3_RX_DMA_STREAM, ENABLE);
		
		
		//����жϱ�־λ
		(void)USART3->DR;
		(void)USART3->SR;
		//ע�⣬������ԭ���ķ������޷�����жϱ�־λ��
		//USART_ClearITPendingBit(USART1, USART_IT_IDLE);
	}
	
}

/**
  * @brief  CAN1 FIFO0 �����ж�
  * @param  None
  * @retval None
  */
void CAN1_RX0_IRQHandler(void)
	{
		CanRxMsg CAN1Feedback_Msg;
		
		if(CAN_GetITStatus(CAN1,CAN_IT_FMP0))
		{
			
			CAN_Receive(CAN1,CAN_FIFO0,&CAN1Feedback_Msg);
			
			Analysis_getinfo(CAN1Feedback_Msg);
			
			CAN_ClearITPendingBit(CAN1, CAN_IT_FMP0);
		}
	}


/**
  * @brief  TIM6 DAC ˢ���ж�
  * @param  None
  * @retval None
  */
float cv_XRatio = 1.2f;
float cv_YRatio = 0.7f;
float CounterSS= 0 ;
int CounterUSART2 = 0;
int A= 0 ;
void TIM6_DAC_IRQHandler(void)
{
	
	static int counter = 0.0f;
	float Chassis_Vx = 0.0f,Chassis_Vy = 0.0f,Chassis_VOmega = 0.0f;
	float Cloud_delta_Yaw = 0.0f,Cloud_delta_Pitch = 0.0f;
	float YawRad = 0.0f;
	int apo = 0;
	
	
	if(TIM_GetITStatus(TIM6,TIM_IT_Update))
	{
		
		 if(++counter > 100)
        {
					#if New_RM
//                  GPIO_ToggleBits(GPIOE,GPIO_Pin_11);
					#else
					GPIO_ToggleBits(GPIOE,GPIO_Pin_7);
					#endif
           counter = 0;
        }

			if(CounterUSART2++ >= 100)
			{
				A = USARTCounter;
				printf("A = %d\r\n",USARTCounter);
				CounterUSART2 =0;	
				USARTCounter = 0;
			}

	
			switch(GetSwitch_Mode())
			{
				case Status_ControlOFF:
					last_cv_x = 0;
					last_cv_y = 0;
					break;
				
				/*****************RC*******************/
				case Status_ControlByRC:
					/*��ͷģʽ*/
//					pc.PCMode = Mode_Chassiscal_NoneHead;
					/*��̨����ģʽ*/
					pc.PCMode = Mode_Cloud_PlatformFollowing;
					// CAN_Cylinder();//���ײ���
					Chassis_Vx = rocket_Left.x /660 *Chassis_MaxSpeed_X;
					Chassis_Vy = rocket_Left.y /600 *Chassis_MaxSpeed_Y;
					Cloud_delta_Yaw = rocket_Right.x/8;
					Cloud_delta_Pitch = rocket_Right.y/7;
				
				
					if(DR16.rc.s_left == 1)
					{
						LASER(0);
						firction_OFF();
					}
					
					if(DR16.rc.s_left == 2 || DR16.rc.s_left == 3)
					{
						LASER(1);
						firction_ON();
						
						/*��������*/
						//Chassis_VOmega = 200;	
						
					}
					
					/*����*/
						Cloud_delta_Yaw += cv_x/3;
						Cloud_delta_Pitch += cv_y/3;
						HC_X = Cloud_delta_Yaw;
						HC_Y = Cloud_delta_Pitch;
						cv_x = 0;
						cv_y = 0;


					
					
					/*����׼��*/
					Fire.Fire_ready = (DR16.rc.s_left == 2)?1:0;
					break;
					
				/*****************PC*******************/	
				case Status_ControlByPC:
					if(pc.NowStatus == 0)
					{
						PC_MODE_Init();
					}
					
					switch(pc.PCMode)
					{
						/*pcֹͣģʽ*/
						case Mode_STOP_Mode:
							/*KEYBOARD_PRESSED_C | KEYBOARD_PRESSED_CTRL:*/
							Fire.Fire_ready = 0;
							Firction.firction_ready = 0;
							firction_OFF();
							break;
						
						/*pc��ͷģʽ*/
						case Mode_Chassiscal_NoneHead:
							/*KEYBOARD_PRESSED_V | KEYBOARD_PRESSED_CTRL:*/
							
							Chassis_Vx = pcRocket.x;
							Chassis_Vy = pcRocket.y;
							Chassis_VOmega = pcRocket.degrees;
							/*��׼�ж�*/
							if(DR16.mouse.keyRight == 1)
							{
								Cloud_delta_Yaw = DR16.mouse.x*1.0f;
								Cloud_delta_Pitch = DR16.mouse.y * 1.0f;
							}
							else
							{
								Cloud_delta_Yaw = DR16.mouse.x*2.0f;
								Cloud_delta_Pitch = DR16.mouse.y*1.5f;
							}
							/*pc��ͷģʽ*/
							if(pc.PCMode == Mode_Chassiscal_NoneHead)
							{
								YawRad = Get_Cloud_YAWAngle_withCenter()*DEG_TO_RAD;
								/*��ͷģʽ�ٶ����ֽ⹫ʽ*/
								float temp_Vx = Chassis_Vx;
								Chassis_Vx = Chassis_Vx*cos(YawRad) - Chassis_Vy*sin(YawRad);
								Chassis_Vy = Chassis_Vy*cos(YawRad) + temp_Vx*sin(YawRad);
							}
							break;
						
						/*����ģʽ?*/
						case Mode_Cloud_PlatformFollowing:
							/*KEYBOARD_PRESSED_F | KEYBOARD_PRESSED_CTRL:*/
							
							Chassis_Vx = pcRocket.x;
							Chassis_Vy = pcRocket.y;
							Chassis_VOmega = pcRocket.degrees;
						
							
							if(DR16.mouse.keyRight == 1)
							{
								Cloud_delta_Yaw = DR16.mouse.x*1.0f;
								Cloud_delta_Pitch = DR16.mouse.y * 1.0f;
								
								
							}
							else
							{
								Cloud_delta_Yaw = DR16.mouse.x*2.0f;
								Cloud_delta_Pitch = DR16.mouse.y*1.5f;
							}
							
								

//							if(pc.Vision_shooting == 1)
//							{
//								Cloud_delta_Yaw += cv_x;
//								Cloud_delta_Pitch += cv_y;
//								cv_x = 0;
//								cv_y = 0;
//							}
							
							
							break;
						
						/**/
						case Mode_Supply_StationMode:
							/*KEYBOARD_PRESSED_R | KEYBOARD_PRESSED_CTRL:*/
							
							break;
						
//						case Mode_Auto_firing:
//							/*�Զ�����ģʽ*/
//							Chassis_Vx = pcRocket.x;
//							Chassis_Vy = pcRocket.y;
//							Chassis_VOmega = pcRocket.degrees;
//						
//							/*��׼ģʽ*/
//							if(DR16.mouse.keyRight == 1)
//							{
//								Cloud_delta_Yaw = DR16.mouse.x*1.0f;
//								Cloud_delta_Pitch = DR16.mouse.y * 1.0f;
//								/*test*/
//								Cloud_delta_Yaw += cv_x*cv_XRatio;
//								cv_x = 0;
//								Cloud_delta_Pitch += cv_y*cv_YRatio;
//								cv_y = 0;	
//							}
//							else
//							{
//								Cloud_delta_Yaw = DR16.mouse.x*2.0f;
//								Cloud_delta_Pitch = DR16.mouse.y*1.5f;
//							}
//							
//							break;


						default:
						break;
					}
					
					/*����׼��ģʽ*/
					Fire.Fire_ready = DR16.mouse.keyLeft;
					break;
			}
			
			
			
			
			
			
			
			Chassis_Process(Chassis_Vx,Chassis_Vy,Chassis_VOmega,GetSwitch_ModeChassis());
			
			Double_Cloud_process(Cloud_delta_Yaw,Cloud_delta_Pitch,GetSwitch_ModeCloud());
	
			
	
				
		
		TIM_ClearITPendingBit(TIM6,TIM_IT_Update);
	}
}

/* -------------------------------- begin  -------------------------------- */
/**
* @Name    {TIM7_IRQHandler}
* @brief   TIM7ˢ���жϣ���Ҫ�����ճ���ˢ�£�
* @param   {NONE}
* @author  ����
* @Data    {Date}
**/
/* -------------------------------- end -------------------------------- */
int DMR_counter = 0;
void TIM7_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM7,TIM_IT_Update)!= RESET)
	{
		
		if(++DMR_counter >20)//50ms =TIM7 *5
		{
//			GPIO_ToggleBits(GPIOF,GPIO_Pin_14);
			DeviceFlash_Process();
      		DMR_counter = 0;
		}
		
		
		DR16_Key_Whether_Process(DR16.keyBoard.key_code,&keyBorad);
		
		/*�Ƿ�����Ctrl����Shift*/
		Whether_CtrlANDShift_ChangeMode();
		
		/*****Mode Setting*****/
		if(pc.Ctrl_Open)
		{
			switch(keyBorad.key_Status)
				{
					
					case KEYBOARD_PRESSED_C | KEYBOARD_PRESSED_CTRL:
						pc.PCMode = Mode_STOP_Mode;
					break;
					
					case KEYBOARD_PRESSED_F | KEYBOARD_PRESSED_CTRL:
						pc.PCMode = Mode_Cloud_PlatformFollowing;
					break;
					
					case KEYBOARD_PRESSED_V | KEYBOARD_PRESSED_CTRL:
						pc.PCMode = Mode_Chassiscal_NoneHead;
					break;
					
					case KEYBOARD_PRESSED_R | KEYBOARD_PRESSED_CTRL:
						pc.PCMode = Mode_Supply_StationMode;
					break;
					
//					case KEYBOARD_PRESSED_R | KEYBOARD_PRESSED_CTRL:
//						pc.PCMode = Mode_Auto_firing;
//					break;
					
					default:
					break;
				}
		}
		
		/*****switch Setting*****/
		Direction_Dealing(&pcRocket);
		Devices_dealing();
		
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
