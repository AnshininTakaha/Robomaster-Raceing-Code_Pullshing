#include "Cloud_control.h"

Cloud_t Cloud;

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


/**
  * @brief  ��̨��ʼ�������ò�������λ��̨
  * @param  None
  * @retval None
  */
void Cloud_Init(void)
{
	Cloud.LpfAttFactor = 0.05f;
	
	Cloud.yawRaw = Cloud.yawLPF = Cloud_Yaw_Center;
	Cloud.pitchRaw = Cloud.pitchLPF = Cloud_Pitch_Center;
	
	
	//Ħ����90M/90/20000=50HZ
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
			if(M6623s[i].infoUpdateFlag == 1){
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
