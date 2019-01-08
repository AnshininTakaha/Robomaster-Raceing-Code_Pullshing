#include "Cloud_control.h"




Cloud_t Cloud;
float temp_Yaw,temp_Yaw_tc,temp_pitch,temp_pitch_tc,temp_eular_x = 0;
/*�ϵ�֮������������ʱ���ֵ*/
float savelife_point = 1;
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


/**
  * @brief  ��̨��ʼ�������ò�������λ��̨
  * @param  None
  * @retval None
  */
void Cloud_Init(void)
{
//    savelife_point = 0;
    Cloud.LpfAttFactor = Cloud_LpfAttFactor;
    /*Ȧ������*/
    /*���ǵ�����һ��ʼ���������Ȧ����Χ��*/
//		M6623s[0].turnCount = 0;
    M6623s[1].turnCount = 0;
    Cloud_IMU.turnCount = 0;

//		temp_Yaw = M6623s[0].totalAngle;
//		temp_Yaw_tc = M6623s[0].turnCount;
//
//		temp_pitch = M6623s[1].totalAngle;
//		temp_pitch_tc = M6623s[0].turnCount;
//		temp_eular_x = Cloud_IMU.eular.yaw;

    /*ֱ�Ӷ�ȡһ��ʼ�ĵ����λ�ã���Ϊ������CAN�����ġ������ΪʲôҪ��ʱ��ԭ�򡿣�*/
    /*��֮ǰ�ĵ����ֵ��ͬ��֮ǰ����һ��ʼ��ֵ����ĳһ��������Ӷ�ʵ�ֳ�ʼ���ŷ��Ĺ���*/
    /*�����ֱ�Ӷ�ȡһ��ʼ�����ֵ��ʶ��ǰλ�õ�ֵ����������Ϊһ��ʼ��ֵ��Ū*/


//    Cloud.yawRaw = Cloud.yawLPF = M6623s[0].totalAngle = Cloud_IMU.eular.yaw *22.75f;
    Cloud.yawRaw = Cloud.yawLPF = M6623s[0].totalAngle;
    Cloud.pitchRaw = Cloud.yawLPF = M6623s[1].totalAngle;
    Cloud.mode = Cloud_Mode_Normal;

    /*�����ʼ���������˳�ʼ�����������*/
    Shoot_Init();

    //˫���ز���
//    PositionPID_paraReset(&M6623s[0].pid, -4.3f, -0.0f, -20.3f, 4000, 1000);

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
        friction_turnOff();
        return;
    }

    //ң��������
    if(dr16_data.offLineFlag)
    {
        delta_yaw = delta_pitch = 0.0f;
        friction_turnOff();
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
		
    Shoot_processing();


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

    Cloud_setCurrent(M6623s[0].outCurrent, M6623s[1].outCurrent, M2006s[1].outCurrent, 0);

}

/**
  * @brief  ��̨���ƴ���-��IMUģʽ
  * @param[in]  delta_yaw		����Ǳ仯��
  *				delta_pitch		�����Ǳ仯��
  *				shoot	���ʹ��
  *				mode	ģʽ - ��Status_ControlOFF�⣬������������
  * @retval None
  */
int PID_point = 0;
float FirstM6623s_YawOPIDOut,FirstM6623sYaw_outCurrent;
float a =0, io = 0;
void Cloud_processing_WithIMU(float delta_yaw,float delta_pitch, uint8_t mode)
{
//		if(!savelife_point)
//		{
//			savelife_point = 1;
//			PID_point = 0;
//		}
    /*���ֻ�еX��Ƕȵĸ���*/
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
        friction_turnOff();
        return;
    }

    //ң��������
    if(dr16_data.offLineFlag)
    {

        delta_yaw = delta_pitch = 0.0f;
        friction_turnOff();
    }

    /*�ۼ�*/
    Cloud.IMUYawRaw += delta_yaw/30.0f;
    Cloud.pitchRaw -= delta_pitch;


    /*��̬IMU���߽�㣨�������ĸ��ط�������*/
    Cloud.IMUYawMax = Cloud_IMU.totalYaw + Get_Cloud_YAWAngle_withLeft();

    Cloud.IMUYawMin = Cloud_IMU.totalYaw - (M6623_AngleToDEG(Cloud_Yaw_delta) - Get_Cloud_YAWAngle_withLeft());

    Cloud.IMUPitchMax = Cloud_IMU.eular.roll + Get_Cloud_PITCHAngle_withDown();

    Cloud.IMUPitchMin = Cloud_IMU.eular.roll - (M6623_AngleToDEG(Cloud_Pitch_delta) - Get_Cloud_PITCHAngle_withDown());


    //yaw
    //����̨�޷��ͻص���
if(!IMU_changer)
	{
    if(Cloud_IMU.totalYaw > Cloud.IMUYawMax)
    {
        if(delta_yaw < 0.0f)
        {
            Cloud.IMUYawRaw += (delta_yaw/8)/30.0f;
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
            Cloud.IMUYawRaw += (delta_yaw/8)/30.0f;
        }
        else
        {
            Cloud.IMUYawRaw = Cloud.IMUYawMin;
        }
    }
	}

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

    /*����ж�*/
    Shoot_processing();

    /*˫�����㿪ʼ*/
    if(!M6623s[0].offLineFlag)
    {

        float M6623s_YawOPIDOut;
        //PID����

        //�Ƕ�PID����(�⻷)
        M6623s_YawOPIDOut = Position_PID(&Cloud.YawAttitude_pid, Cloud.IMUYawLPF, Cloud_IMU.totalYaw);
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

    if(!Cloud_and_shooting_ban)
    {
        Cloud_setCurrent(M6623s[0].outCurrent, M6623s[1].outCurrent, M2006s[0].outCurrent, 0);
    }
//		else if(!shooting_ban)
//		{
//			Cloud_setCurrent(M6623s[0].outCurrent, M6623s[1].outCurrent, 0, 0);
//		}


//	Cloud_setCurrent(M6623s[0].outCurrent, M6623s[1].outCurrent, M2006s[0].outCurrent, 0);
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


