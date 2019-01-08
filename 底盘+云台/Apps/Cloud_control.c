#include "Cloud_control.h"

Cloud_t Cloud;

/**
  * @brief  设置M6623电机电流值（id号为5,6），M2006电机电流值（id 7）
  * @param  iqyaw 	对应yaw轴电机的电流值，范围-5000~0~5000
  *			iqpitch	对应pitch轴电机的电流值，范围-5000~0~5000
  *			iq7，拨弹电机电流值，范围-10000~0~10000
  * @retval None
  */
void Cloud_setCurrent(int16_t iqyaw, int16_t iqpitch, int16_t iq7, int16_t iq8)
{

	uint8_t data[8];
	
	//数据格式详见说明书P32
	data[0] = iqyaw >> 8;
	data[1] = iqyaw;
	data[2] = iqpitch >> 8;
	data[3] = iqpitch;
	data[4] = iq7 >> 8;
	data[5] = iq7;
	data[6] = iq8 >> 8;
	data[7] = iq8;
	
	CAN_SendData(CAN1, CAN_ID_STD, M6623_SENDID, data);
	
}	


/**
  * @brief  云台初始化，配置参数并归位云台
  * @param  None
  * @retval None
  */
void Cloud_Init(void)
{
	Cloud.LpfAttFactor = 0.05f;
	
	Cloud.yawRaw = Cloud.yawLPF = Cloud_Yaw_Center;
	Cloud.pitchRaw = Cloud.pitchLPF = Cloud_Pitch_Center;
	
	
	//摩擦轮90M/90/20000=50HZ
	TIM12_PWMOutput(89, 19999,1000);
	
	//云台pitch轴电机pid
	PositionPID_paraReset(&M6623s[1].pid, -5.8f, -0.0f, -18.5f, 4000, 1000);
	//云台yaw轴电机pid
	PositionPID_paraReset(&M6623s[0].pid, -4.3f, -0.0f, -20.3f, 4000, 1000);
	
	M6623_setTargetAngle(M6623_YAW, Cloud.yawRaw);
	M6623_setTargetAngle(M6623_PITCH, Cloud.pitchRaw);
	
	//云台归位
	do{
		
		
		for(int i = 0; i<2; i++){
			if(M6623s[i].infoUpdateFlag == 1){
				//PID计算
				M6623s[i].outCurrent = Position_PID(&M6623s[i].pid, M6623s[i].targetAngle, M6623s[i].realAngle); 
				//清标志位
				M6623s[i].infoUpdateFlag = 0;
			}
		}
		
		//设定电机电流值
		Cloud_setCurrent(M6623s[0].outCurrent, M6623s[1].outCurrent, 0, 0);
		
		delay_ms(10);
		
	}while(abs(M6623s[0].pid.err)>100.0f || abs(M6623s[1].pid.err)>100.0f);
	
	//清零防炸
	M6623s[0].turnCount = 0;
	M6623s[1].turnCount = 0;	
	
}	

/**
  * @brief  获取云台Yaw旋转溢出值
  * @param[in]  None
  * @retval 溢出值
  */
float Cloud_getYawOverFlow(void)
{
	float temp = Cloud.yawOverflow;
	Cloud.yawOverflow = 0;
	return temp;
	
}

/**
* @brief  获取云台Yaw旋转角度（以中心为0点）
  * @param[in]  None
  * @retval 角度
  */
float Cloud_getYawAngle(void)
{
	return (Cloud_Yaw_Center - Cloud.yawRaw)/22.75f;
	
}

/**
  * @brief  云台控制处理
  * @param[in]  delta_yaw		航向角变化量
  *				delta_pitch		俯仰角变化量
  *				shoot	射击使能
  *				mode	模式 - 除Status_ControlOFF外，其他正常控制
  * @retval None
  */
void Cloud_processing(float delta_yaw, float delta_pitch, uint8_t shoot, uint8_t mode)
{
	/*如果遥控器是关闭的模式*/
	if(mode == Status_ControlOFF)
	{
		Cloud_setCurrent(0, 0, 0, 0);
		fricMotor_setSpeed(1000);
		return;
	}
	
	/*可能是因为取值是反过来的，所以要用这个来取值*/
	Cloud.yawRaw -= delta_yaw;
	Cloud.pitchRaw -= delta_pitch;
	
	//云台限幅begin
	if(Cloud.yawRaw > Cloud_Yaw_Max)
	{
		/*记下来超过了多少*/
		Cloud.yawOverflow = Cloud_Yaw_Max - Cloud.yawRaw;
		Cloud.yawRaw = Cloud_Yaw_Max;
	}
	if(Cloud.yawRaw < Cloud_Yaw_Min)
	{
		/*记下来还没有到的有多少*/
		Cloud.yawOverflow = Cloud_Yaw_Min - Cloud.yawRaw;
		Cloud.yawRaw = Cloud_Yaw_Min;
	}
	
  /*同理*/	
	if(Cloud.pitchRaw > Cloud_Pitch_Max)
	{
		Cloud.pitchOverflow = Cloud_Pitch_Max - Cloud.pitchRaw;
		Cloud.pitchRaw = Cloud_Pitch_Max;
	}
	if(Cloud.pitchRaw < Cloud_Pitch_Min) 
	{
		Cloud.pitchOverflow = Cloud.pitchRaw - Cloud_Pitch_Min;
		Cloud.pitchRaw = Cloud_Pitch_Min;
	}
	//云台限幅end
	
	/*滤波*/
	Filter_IIRLPF(&Cloud.yawRaw, &Cloud.yawLPF, Cloud.LpfAttFactor);
	Filter_IIRLPF(&Cloud.pitchRaw, &Cloud.pitchLPF, Cloud.LpfAttFactor);
	
		
	/*赋目标角度值*/
	M6623_setTargetAngle(M6623_YAW, Cloud.yawLPF);
	M6623_setTargetAngle(M6623_PITCH, Cloud.pitchLPF);
	
	/*如果填充完毕*/
//	if(shoot && M2006s[0].loadFinish)//识别到射击的同时loadFinish为1
//	{
//		fricMotor_setSpeed(1800);//子弹发射
//		
//		/*每一次拨弹就在当前角度上面加值，转一颗子弹的角度*/
//		M2006s[0].addAngle += M2006_LOADANGLE;
//	}
	
	/*************6623_BEGIN****************/
	for(int i = 0; i<2; i++)
	{
		if(M6623s[i].infoUpdateFlag == 1)
		{
			//PID计算，算出输出的角度值 
			M6623s[i].outCurrent = Position_PID(&M6623s[i].pid, M6623s[i].targetAngle, M6623s[i].realAngle + (8192*M6623s[i].turnCount)); 
			//清标志位
			M6623s[i].infoUpdateFlag = 0;
		}
	}
	/*************6623_END****************/
		
	/*************M2006_BEGIN****************/
//	if(M2006s[0].infoUpdateFlag == 1){
//		static uint8_t M2006s_blocking = 0;
//		M2006s[0].loadFinish = 0;

//		//角度PID计算(外环)
//		int M2006s_PIDOut = Position_PID(&M2006s[0].pid_angle, M2006s[0].addAngle, M2006s[0].realAngle + (8192*M2006s[0].turnCount));
//		//速度PID计算(内环)
//		M2006s[0].outCurrent = Incremental_PID(&M2006s[0].pid_speed, M2006s_PIDOut, M2006s[0].realSpeed);
//		
//		//卡弹处理
//		if(abs(M2006s[0].outCurrent)>5500){
//			if(!M2006s_blocking){
//				//卡弹后反转到原来位置
//				M2006s[0].addAngle -= M2006_LOADANGLE*2;
//				M2006s_blocking = 1;
//			}
//		}
//		
//		//拨弹完毕判断
//		if(abs(M2006s[0].pid_angle.err)<600 && M2006s[0].realSpeed == 0){
//			M2006s[0].loadFinish = 1;
//			M2006s_blocking = 0;
//		}
//		//清零防炸
//		if(M2006s[0].turnCount>100){
//			M2006s[0].addAngle -= (8192*M2006s[0].turnCount);
//			M2006s[0].turnCount = 0;

//		}

//		
//		//清标志位
//		M2006s[0].infoUpdateFlag = 0;
//	}
	/*************M2006_END****************/
	
	//设定电机电流值
	Cloud_setCurrent(M6623s[0].outCurrent, M6623s[1].outCurrent, 1000, 0);
	
}
