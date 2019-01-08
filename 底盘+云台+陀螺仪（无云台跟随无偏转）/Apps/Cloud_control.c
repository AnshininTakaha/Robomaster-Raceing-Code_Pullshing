#include "Cloud_control.h"

Cloud_t Cloud;

/**
  * @brief  ��ȡ��̨Yaw��Pitch����ת�Ƕȣ��ֱ����м���Ե���Ϊ��㣩
  * @param[in]  None
  * @retval �Ƕ�
  */
float Get_Cloud_YAWAngle_withCenter(void)
{
	return(M6623s[0].totalAngle - Cloud_Yaw_Center) / 22.75f; 
}

float Get_Cloud_YAWAngle_withLeft(void)
{
	return(M6623s[0].totalAngle - Cloud_Yaw_Min) / 22.75f;
}

float Get_Cloud_PITCHAngle_withCenter(void)
{
	return(M6623s[1].totalAngle - Cloud_Pitch_Center);
}

float Get_Cloud_PITCHAngle_withDown(void)
{
	return(M6623s[1].totalAngle - Cloud_Pitch_Min);
}

/**
  * @brief  ǿ��������̨IMU���꣨�ƹ����壩
  * @param[in]  posYaw
  *				posPitch
  * @retval None
  */
void Cloud_setIMUPosForced(float posYaw, float posPitch)
{
	Cloud.IMUYawLPF = Cloud.IMUYawRaw = posYaw;
	Cloud.IMUPitchLPF = Cloud.IMUPitchRaw = posPitch;
}
/**
  * @brief  ǿ��������̨��е���꣨�ƹ���������
  * @param[in]  posYaw
  *				posPitch
  * @retval None
  */
void Cloud_setAbsPosForced(float posYaw, float posPitch)
{
	Cloud.yawLPF = Cloud.yawRaw = posYaw;
	Cloud.pitchLPF = Cloud.pitchRaw = posPitch;
}









/**
  * @brief  ����M6623�������ֵ��id��Ϊ5,6����M2006�������ֵ��id 7��
  * @param  iqyaw 	��Ӧyaw�����ĵ���ֵ����Χ-5000~0~5000
  *			iqpitch	��Ӧpitch�����ĵ���ֵ����Χ-5000~0~5000
  *			iq7�������������ֵ����Χ-10000~0~10000
  * @retval None
  */
void Cloud_setCurrent(int16_t iqyaw, int16_t iqpitch, int16_t iq7, int16_t iq8)
{

	uint8_t data[8];
	
	//���ݸ�ʽ���˵����P32
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

#if old_control_proment
/**
  * @brief  �ɵ���̨��ʼ�������ò�������λ��̨
  * @param  None
  * @retval None
  */
void Cloud_Init(void)
{
	Cloud.LpfAttFactor = 0.05f;
	
	Cloud.yawRaw = Cloud.yawLPF = Cloud_Yaw_Center;
	Cloud.pitchRaw = Cloud.pitchLPF = Cloud_Pitch_Center;
	
	
	//Ħ����90M/90/20000=50HZ���൱�ڸ�Ħ���ֳ�ʼ��
	TIM12_PWMOutput(89, 19999,1000);
	
	//��̨pitch����pid
	PositionPID_paraReset(&M6623s[1].pid, -5.8f, -0.0f, -18.5f, 4000, 1000);
	//��̨yaw����pid
	PositionPID_paraReset(&M6623s[0].pid, -4.3f, -0.0f, -20.3f, 4000, 1000);
	
	M6623_setTargetAngle(M6623_YAW, Cloud.yawRaw);
	M6623_setTargetAngle(M6623_PITCH, Cloud.pitchRaw);
	
	//��̨��λ
	do{
		for(int i = 0; i<2; i++){
			if(M6623s[i].infoUpdateFlag == 1)
			{
				//PID����
				M6623s[i].outCurrent = Position_PID(&M6623s[i].pid, M6623s[i].targetAngle, M6623s[i].realAngle); 
				//���־λ
				M6623s[i].infoUpdateFlag = 0;
			}
		}
		
		//�趨�������ֵ
		Cloud_setCurrent(M6623s[0].outCurrent, M6623s[1].outCurrent, 0, 0);
		
		delay_ms(10);
		
	}while(abs(M6623s[0].pid.err)>100.0f || abs(M6623s[1].pid.err)>100.0f);
	
	//�����ը
	M6623s[0].turnCount = 0;
	M6623s[1].turnCount = 0;	
	
}	

void Cloud_processing(float delta_yaw, float delta_pitch, uint8_t shoot, uint8_t mode)
{
	/*���ң�����ǹرյ�ģʽ*/
	if(mode == Status_ControlOFF)
	{
		Cloud_setCurrent(0, 0, 0, 0);
		fricMotor_setSpeed(1000);
		return;
	}
	
	/*��������Ϊȡֵ�Ƿ������ģ�����Ҫ�������ȡֵ*/
	Cloud.yawRaw -= delta_yaw;
	Cloud.pitchRaw -= delta_pitch;
	
	//��̨�޷�begin
	if(Cloud.yawRaw > Cloud_Yaw_Max)
	{
		/*�����������˶���*/
		Cloud.yawOverflow = Cloud_Yaw_Max - Cloud.yawRaw;
		Cloud.yawRaw = Cloud_Yaw_Max;
	}
	if(Cloud.yawRaw < Cloud_Yaw_Min)
	{
		/*��������û�е����ж���*/
		Cloud.yawOverflow = Cloud_Yaw_Min - Cloud.yawRaw;
		Cloud.yawRaw = Cloud_Yaw_Min;
	}
	
  /*ͬ��*/	
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
	//��̨�޷�end
	
	/*�˲�*/
	Filter_IIRLPF(&Cloud.yawRaw, &Cloud.yawLPF, Cloud.LpfAttFactor);
	Filter_IIRLPF(&Cloud.pitchRaw, &Cloud.pitchLPF, Cloud.LpfAttFactor);
	
		
	/*��Ŀ��Ƕ�ֵ*/
	M6623_setTargetAngle(M6623_YAW, Cloud.yawLPF);
	M6623_setTargetAngle(M6623_PITCH, Cloud.pitchLPF);
	
	/*���������*/
//	if(shoot && M2006s[0].loadFinish)//ʶ�������ͬʱloadFinishΪ1
//	{
//		fricMotor_setSpeed(1800);//�ӵ�����
//		
//		/*ÿһ�β������ڵ�ǰ�Ƕ������ֵ��תһ���ӵ��ĽǶ�*/
//		M2006s[0].addAngle += M2006_LOADANGLE;
//	}
	
	/*************6623_BEGIN****************/
	for(int i = 0; i<2; i++)
	{
		if(M6623s[i].infoUpdateFlag == 1)
		{
			//PID���㣬�������ĽǶ�ֵ 
			M6623s[i].outCurrent = Position_PID(&M6623s[i].pid, M6623s[i].targetAngle, M6623s[i].realAngle + (8192*M6623s[i].turnCount)); 
			//���־λ
			M6623s[i].infoUpdateFlag = 0;
		}
	}
	/*************6623_END****************/
		
	/*************M2006_BEGIN****************/
//	if(M2006s[0].infoUpdateFlag == 1){
//		static uint8_t M2006s_blocking = 0;
//		M2006s[0].loadFinish = 0;

//		//�Ƕ�PID����(�⻷)
//		int M2006s_PIDOut = Position_PID(&M2006s[0].pid_angle, M2006s[0].addAngle, M2006s[0].realAngle + (8192*M2006s[0].turnCount));
//		//�ٶ�PID����(�ڻ�)
//		M2006s[0].outCurrent = Incremental_PID(&M2006s[0].pid_speed, M2006s_PIDOut, M2006s[0].realSpeed);
//		
//		//��������
//		if(abs(M2006s[0].outCurrent)>5500){
//			if(!M2006s_blocking){
//				//������ת��ԭ��λ��
//				M2006s[0].addAngle -= M2006_LOADANGLE*2;
//				M2006s_blocking = 1;
//			}
//		}
//		
//		//��������ж�
//		if(abs(M2006s[0].pid_angle.err)<600 && M2006s[0].realSpeed == 0){
//			M2006s[0].loadFinish = 1;
//			M2006s_blocking = 0;
//		}
//		//�����ը
//		if(M2006s[0].turnCount>100){
//			M2006s[0].addAngle -= (8192*M2006s[0].turnCount);
//			M2006s[0].turnCount = 0;

//		}

//		
//		//���־λ
//		M2006s[0].infoUpdateFlag = 0;
//	}
	/*************M2006_END****************/
	
	//�趨�������ֵ
	Cloud_setCurrent(M6623s[0].outCurrent, M6623s[1].outCurrent, 1000, 0);
	
}

#else
/**
  * @brief  ��̨��ʼ�������ò�������λ��̨
  * @param  None
  * @retval None
  */
void Cloud_Init(void)
{
	Cloud.LpfAttFactor = Cloud_LpfAttFactor;
	/*Ȧ������*/
	/*���ǵ�����һ��ʼ���������*/
//	M6623s[0].turnCount = 0;
//	M6623s[1].turnCount = 0;
	Cloud_IMU.turnCount = 0;
	
	/*ֱ�Ӷ�ȡһ��ʼ�ĵ����λ�ã���Ϊ������CAN�����ġ������ΪʲôҪ��ʱ��ԭ�򡿣�*/
	/*��֮ǰ�ĵ����ֵ��ͬ��֮ǰ����һ��ʼ��ֵ����ĳһ��������Ӷ�ʵ�ֳ�ʼ���ŷ��Ĺ���*/
	/*�����ֱ�Ӷ�ȡһ��ʼ�����ֵ��ʶ��ǰλ�õ�ֵ����������Ϊһ��ʼ��ֵ��Ū*/
	Cloud.yawRaw = Cloud.yawLPF = M6623s[0].totalAngle;
	Cloud.pitchRaw = Cloud.yawLPF = M6623s[1].totalAngle;
	Cloud.mode = Cloud_Mode_Normal;
	
	/*�����ʼ���������˳�ʼ�����������*/
//	Shoot_Init();
	
	//PID��ʼ��
	//��̨�����е�Ƕȱջ�
	//��̨pitch����pid
	PositionPID_paraReset(&M6623s[1].pid_speed, -8.0f, 0.0f, -12.0f, 4000, 0);
	PositionPID_paraReset(&M6623s[1].pid_angle, 1.5f, 0.0f, 0.0f, 500, 0);
	//��̨yaw����pid
	PositionPID_paraReset(&M6623s[0].pid_speed, -10.0f, 0.0f, 0.0f, 4000, 0);
	PositionPID_paraReset(&M6623s[0].pid_angle, 2.0f, 0.0f, 1.0f, 500, 0);
	
	//��̨���IMU�ջ�
	//��̨����ջ�
	Cloud.IMUYawRaw = Cloud.IMUYawLPF = Cloud_IMU.totalYaw;
	Cloud.IMUPitchRaw = Cloud.IMUPitchLPF = Cloud_IMU.eular.roll;
	/*��̨���̳�ʼ���Ƕ�*/
//	IMU_Yaw_Offset = Cloud_IMU.totalYaw - Chassis_IMU.totalYaw;
	//Yaw
	PositionPID_paraReset(&Cloud.YawAttitude_pid, -1.5f, 0.0f, 0.0f, 500, 0);
	PositionPID_paraReset(&Cloud.YawSpeed_pid, -80.0f, 0.0f, -60.0f, 4000, 0);
	//Pitch
	PositionPID_paraReset(&Cloud.RollAttitude_pid, -2.0f, 0.0f, 0.0f, 500, 0);
	PositionPID_paraReset(&Cloud.RollSpeed_pid, -60.0f, 0.0f, -40.0f, 4000, 0);
}

/**
  * @brief  ��̨���ƴ���-��ͨģʽ
  * @param[in]  delta_yaw		����Ǳ仯��
  *				delta_pitch		�����Ǳ仯��
  *				shoot	���ʹ��
  *				mode	ģʽ - ��Status_ControlOFF�⣬������������
  * @retval None
  */

void Cloud_processing_Normal(float delta_yaw, float delta_pitch, uint8_t mode)
{
	//��Ϊ�л���Ϊ��ͨģʽ�ˣ����ʱ��Ҫһֱ��������IMU��ֵ����ֹ��ը
	//����IMU�Ƕȸ��棬��ֹ�л���ʱ��ը��
	Cloud_setIMUPosForced(Cloud_IMU.totalYaw, Cloud_IMU.eular.roll);
	
	if(mode == ControlMode_OFF || Cloud_IMU.offLineFlag)
	{
		//�Ե�ǰλ��Ϊ�´�����λ�ã���ը
		Cloud_setAbsPosForced(M6623s[0].totalAngle, M6623s[1].totalAngle);
		Cloud_setCurrent(0, 0, 0, 0);
//		fric_turnOff();
		return;
	}
	
	//ң��������
	if(dr16_data.offLineFlag)
	{
		delta_yaw = delta_pitch = 0.0f;
//		fric_turnOff();
	}
	
	Cloud.yawRaw -= delta_yaw;
	Cloud.pitchRaw -= delta_pitch;
	
	//��̨�޷�begin
	if(Cloud.yawRaw > Cloud_Yaw_Max)
	{
		Cloud.yawRaw = Cloud_Yaw_Max;
	}
	if(Cloud.yawRaw < Cloud_Yaw_Min)
	{
		Cloud.yawRaw = Cloud_Yaw_Min;
	}
		
	if(Cloud.pitchRaw > Cloud_Pitch_Max)
	{
		Cloud.pitchRaw = Cloud_Pitch_Max;
	}
	if(Cloud.pitchRaw < Cloud_Pitch_Min) 
	{
		Cloud.pitchRaw = Cloud_Pitch_Min;
	}
	//��̨�޷�end
	
	//ƽ������begin
	Filter_IIRLPF(&Cloud.yawRaw, &Cloud.yawLPF, Cloud.LpfAttFactor);
	Filter_IIRLPF(&Cloud.pitchRaw, &Cloud.pitchLPF, Cloud.LpfAttFactor);
	//ƽ������end
	
	M6623_setTargetAngle(M6623_YAW, Cloud.yawLPF);
	M6623_setTargetAngle(M6623_PITCH, Cloud.pitchLPF);
	
//	Shoot_processing();
	
	
	/*************6623_BEGIN****************/

	if(!M6623s[0].offLineFlag)
	{
			//PID����
			//�Ƕ�PID����(�⻷)
			int M6623s_PIDOut = Position_PID(&M6623s[0].pid_angle, M6623s[0].targetAngle, M6623s[0].totalAngle);
			//�ٶ�PID����(�ڻ�)
			M6623s[0].outCurrent = Position_PID(&M6623s[0].pid_speed, M6623s_PIDOut, Cloud_IMU.gyro.z);
			//���־λ
			M6623s[0].infoUpdateFlag = 0;
	}
	
	if(!M6623s[1].offLineFlag)
	{
			//PID����
			//�Ƕ�PID����(�⻷)
			int M6623s_PIDOut = Position_PID(&M6623s[1].pid_angle, M6623s[1].targetAngle, M6623s[1].totalAngle);
			//�ٶ�PID����(�ڻ�)
			M6623s[1].outCurrent = Position_PID(&M6623s[1].pid_speed, M6623s_PIDOut, Cloud_IMU.gyro.y);
			//���־λ
			M6623s[1].infoUpdateFlag = 0;
	}
	
	/*************6623_END****************/
	
	//�趨�������ֵ
//	Cloud_setCurrent(M6623s[0].outCurrent, M6623s[1].outCurrent, M2006s[0].outCurrent, 0);
	Cloud_setCurrent(M6623s[0].outCurrent, M6623s[1].outCurrent, 1000, 0);

}

/**
  * @brief  ��̨���ƴ���-��IMUģʽ
  * @param[in]  delta_yaw		����Ǳ仯��
  *				delta_pitch		�����Ǳ仯��
  *				shoot	���ʹ��
  *				mode	ģʽ - ��Status_ControlOFF�⣬������������
  * @retval None
  */
void Cloud_processing_WithIMU(float delta_yaw,float delta_pitch, uint8_t mode)
{
	/*���־��Ի�еX��Ƕȵĸ���*/
	Cloud.yawLPF = Cloud.yawRaw = M6623s[0].totalAngle;
	/*���IMU�����ˣ��ͱ�������IMU*/
	if(mode == ControlMode_OFF || Cloud_IMU.offLineFlag)
	{
		//�Ե�ǰλ��Ϊ�´�����λ�ã���ը
		//���û���ԭ���ĽǶ�
		/*totalYaw�����ۻ��ĽǶȣ���M6623��CAN�������淵��*/
		Cloud_setIMUPosForced(Cloud_IMU.totalYaw, Cloud_IMU.eular.roll);
		//ͬ�����û���ԭ���ĽǶ�
		Cloud.pitchLPF = Cloud.pitchRaw = M6623s[1].totalAngle;
		Cloud_setCurrent(0, 0, 0, 0);
//		fric_turnOff();
		return;
	}
	
		//ң��������
	if(dr16_data.offLineFlag)
	{
		
		delta_yaw = delta_pitch = 0.0f;
//		fric_turnOff();
	}
	
	/*�ۼ�*/
	Cloud.IMUYawRaw += delta_yaw/30.0f;
	Cloud.pitchRaw -= delta_pitch;
	
	
	
	Cloud.IMUYawMax = Cloud_IMU.totalYaw + Get_Cloud_YAWAngle_withLeft();
	
	Cloud.IMUYawMin = Cloud_IMU.totalYaw - (M6623_AngleToDEG(Cloud_Yaw_delta) - Get_Cloud_YAWAngle_withLeft());
	
	Cloud.IMUPitchMax = Cloud_IMU.eular.roll + Get_Cloud_PITCHAngle_withDown();

	Cloud.IMUPitchMin = Cloud_IMU.eular.roll - (M6623_AngleToDEG(Cloud_Pitch_delta) - Get_Cloud_PITCHAngle_withDown());

	
	//��̨�޷�begin/���ص��趨��
	#if 0
	//yaw
	if(Cloud_IMU.totalYaw > Cloud.IMUYawMax)
	{
		if(delta_yaw < 0.0f)
		{
			Cloud.IMUYawRaw += delta_yaw/30.0f;
		}
		else
		{
			Cloud.IMUYawRaw = Cloud.IMUYawMax;
		}
	}
	else if(Cloud_IMU.totalYaw < Cloud.IMUYawMin)
	{
		if(delta_yaw > 0.0f)
		{
			Cloud.IMUYawRaw += delta_yaw/30.0f;
		}
		else
		{
			Cloud.IMUYawRaw = Cloud.IMUYawMin;
		}
	}
	
	#endif
	
	//pitch
	if(Cloud.pitchRaw > Cloud_Pitch_Max)
	{
		Cloud.pitchRaw = Cloud_Pitch_Max;
	}
	if(Cloud.pitchRaw < Cloud_Pitch_Min) 
	{
		Cloud.pitchRaw = Cloud_Pitch_Min;
	}
	
	/*�˲�����*/
	Filter_IIRLPF(&Cloud.IMUYawRaw, &Cloud.IMUYawLPF, 0.4);
	
	Filter_IIRLPF(&Cloud.pitchRaw, &Cloud.pitchLPF, 0.1);
	M6623_setTargetAngle(M6623_PITCH, Cloud.pitchLPF);
	
	/*˫��*/
	if(!M6623s[0].offLineFlag)
	{
			//PID����
			//�Ƕ�PID����(�⻷)
			float M6623s_YawOPIDOut = Position_PID(&Cloud.YawAttitude_pid, Cloud.IMUYawLPF, Cloud_IMU.totalYaw);
			//�ٶ�PID����(�ڻ�)
			M6623s[0].outCurrent = Position_PID(&Cloud.YawSpeed_pid, M6623s_YawOPIDOut, Cloud_IMU.gyro.z);
			//M6623s[0].outCurrent = Position_PID(&Cloud.YawAttitude_pid, Cloud.IMUtargetYawLPF, Cloud_IMU.totalYaw);
			//���־λ
			M6623s[0].infoUpdateFlag = 0;
	}
	
	if(!M6623s[1].offLineFlag)
	{
			//PID����
			//�Ƕ�PID����(�⻷)
			int M6623s_PIDOut = Position_PID(&M6623s[1].pid_angle, M6623s[1].targetAngle, M6623s[1].totalAngle);
			//�ٶ�PID����(�ڻ�)
			M6623s[1].outCurrent = Position_PID(&M6623s[1].pid_speed, M6623s_PIDOut, Cloud_IMU.gyro.y);
			//���־λ
			M6623s[1].infoUpdateFlag = 0;
	}
	
	Cloud_setCurrent(M6623s[0].outCurrent, M6623s[1].outCurrent, 0, 0);
//	Cloud_setCurrent(M6623s[0].outCurrent, M6623s[1].outCurrent, M2006s[0].outCurrent, 0);
}











#endif
/**
  * @brief  ��ȡ��̨Yaw��ת���ֵ
  * @param[in]  None
  * @retval ���ֵ
  */
float Cloud_getYawOverFlow(void)
{
	float temp = Cloud.yawOverflow;
	Cloud.yawOverflow = 0;
	return temp;
	
}

/**
* @brief  ��ȡ��̨Yaw��ת�Ƕȣ�������Ϊ0�㣩
  * @param[in]  None
  * @retval �Ƕ�
  */
float Cloud_getYawAngle(void)
{
	return (Cloud_Yaw_Center - Cloud.yawRaw)/22.75f;
	
}

/**
  * @brief  ��̨���ƴ���
  * @param[in]  delta_yaw		����Ǳ仯��
  *				delta_pitch		�����Ǳ仯��
  *				shoot	���ʹ��
  *				mode	ģʽ - ��Status_ControlOFF�⣬������������
  * @retval None
  */
