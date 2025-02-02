/**
  ******************************************************************************
  * @file    README.txt
  * @author  口无
  * @version V1.0
  * @date    2018-09-09
  * @brief   说明文件
  *****************************************************************************
  ******************************************************************************
说明：此文件只适合理解和调试（因为代码部分全部都修正的比较的直观，而不是采用宏定义）
如果需要调试请使用本文件夹的另一个代码
******************************************************************************
  *	第一部分：
  * Update:
  *	2018.9.5  新建工程，开始解读代码
  * 2018.9.7  更新相关的共用体，结构体，解读typedef.h构成
  * 2018.9.8  更新和解读CAN1接受M3508报文过程代码（带超详细解释）
              包括：
			  CAN1初始化
			  NVIC初始化带参函数
			  CAN1的FMP0挂起中断过程
			  获取M3508电机信息函数
  * 2018.9.9  更新和解读了DR16遥控器的部分相关代码
			  包括：
  			  DR16指针部分处理判断
  			  USART1初始化代码（未完成）
  * 2018.9.10 完善USART1的初始化代码
			  完善USART1 RX DMA 配置对应函数代码
			  完善重定义printf和scanf的对应代码
			  完善了遥控器Rocker相关（将x，y坐标变成摇杆数据的函数）
			  DR16遥控器解码函数相关
  * 2018.9.11 TIM6初始化函数
  * 		  TIM6中断函数
  *           滤波器、麦轮解算、PID
			  USART1中断，初始化整体PID信息
  * 2018.9.12 调试完毕，开始仿真PID问题（PID稳定性）
  * 2018.9.13 增加DPS，遥控器稳定压制模式（遥控器防抖），视波长测试流
			  PID调试完成
			  DPS波形调试完成（不要放在中♂断哦！~）
			  底盘部分整合
  ******************************************************************************
  *	第二部分：
  * Update:
  * 2018.9.13：底盘程序封装完毕，开始学习和解读云台程序
  * 2018.9.15：解读完毕，开始进行代码改写
  * 2018.9.16：修改DSP和裁判系统开关
  * 2018.9.17：DSP读取数值代码修改
  * 2018.9.19：TIM12初始化代码优化
  * 2018.9.20: DR16遥控器数值压制优化abs
  * 2018.9.29：云台代码完成（只包含机械角度）
			   PID数值控制完成，代码优化完成
			   开始控制上下限幅角度
  * 2018.9.30：过零处理优化和新思路，陀螺仪加速器IMU调试读回值成功
			   IMU代码优化和陀螺仪的各种问题汇总
  * 2018.10.1：云台PID第二次调试（优化），解读新代码的云台追踪部分和裁判系统部分
			   准备迭代代码和总结底盘、云台汇总的准备
  * 2018.10.2: 云台追踪思路第一个版本挂了，底盘汇总完成，准备云台汇总
			   写了倒车的代码
  ******************************************************************************
  * 第三部分：
  * Update:
  * 2018.10.3：修改云台Init初始化代码（双环模式），修改云台process代码（双环模式）
			   解读it中断代码
  * 2018.10.5  第一次双环代码失败，反思ing
  * 2018.10.9  修改M6623解码函数的初始化问题（第一次初始化角度过大回弹问题）
  * 2018.10.12 双环成功，开始调整云台稳定性
  * 2018.10.13 修复M6623解码函数的初始化问题（回归上一次函数的迭代，问题是出在另一个函数里面）
  * 2018.10.14 准备重新调整M3508、M6623的位置PID和速度PID
			   添加了了时间插件，注释插件等等，不过还没有开始进行修改
			   修复了DAP的RDDI问题
  * 2018.10.15 继续修复
  * 2018.10.17 我diao终于修好了，是陀螺仪的硬件问题
  * 2018.10.18 开始老老实实的调PID吧
  * 2018.10.19 帧率刷新成功，但是PID还没有调到很好的数值
  ******************************************************************************
  * 第四部分：
  * Update:
  * 2018.10.20 基本方向控制成功w，不过云台的PID要再调整一次才行
  ******************************************************************************
  *   I/O口与外设：
  *		时钟：		SYSCLK-180M
  *					APB1-45M， Timer-90M
  *					APB2-90M， Timer-180M
  *		CAN： 		CAN1: 		PD0(RX), PD1(TX)
  *					CAN2: 		PB12(RX), PB13(TX)
  *		串口：		USART2(Debug)：	PD5(TX), PD6(RX)
  *		定时：		TIM6		10ms  
  *                 TIM7        10ms
  *		DR遥控器  	USART1_rx(PB7): DMA1-通道4数据流5
  *		摩擦轮： 	TIM12： 	PH6(CH1), PH9(CH2)
  *		MPU6500:	SPI(HW)		PF6(NSS), PF7(SCK), PF8(MISO), PF9(MOSI)
  *
  *	  中断优先级配置：（优先级分组2）
  *		CAN1接收中断：	1, 1
  *		CAN2接收中断：	1, 2
  *		TIM6定时中断：	1, 0
  *		串口2接收中断：	0, 3
  *		串口1空闲中断：	0, 2
  *	  PID参数：
  *		底盘：	3.0，	1.2，	0.0
  *		云台：  -3.2，  0.0，   -0.01
  *		拨弹： speed：	2.0f, 0.2f, 0.0f 限幅8000  内环
  *			   angle：  0.3f, 0.0f, 0.8f 限幅3000  外环
  * 
  *
  *  ****			底盘ID
  *					车头
  *			2					1
  *			3					4
  ****
  
  /*旧版PID数据*/
  /***********************************************************************/
	
	/*云台电机写在Could的函数里面了，为了方便调用*/

	//云台pitch轴电机pi
//	PositionPID_paraReset(&M6623s[1].pid, -7.2f, 0.0f, -4.9f, 4000, 1000);
	//云台yaw轴电机pid
//	PositionPID_paraReset(&M6623s[0].pid, -9.2f, 0.0f, -4.9f, 4000, 1000);
	
	/***********************************************************************/
	
	
	//拨弹电机pid
//	IncrementalPID_paraReset(&M2006s[0].pid_speed, 2.0f, 0.3f, 0.0f, 8000, 1000);
//	PositionPID_paraReset(&M2006s[0].pid_angle, 0.8f, 0.0f, 3.2f, 8000, 500);
	
	/*IncrementalPID_paraReset(&M2006s[0].pid_speed, 1.8f, 0.18f, 0.0f, 6000, 2000);*/
	/*PositionPID_paraReset(&M2006s[0].pid_angle, 0.3f, 0.0f, 0.8f, 2000, 500);*/
	
  */