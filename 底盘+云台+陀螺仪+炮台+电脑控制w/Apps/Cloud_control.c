#include "Cloud_control.h"




Cloud_t Cloud;
float temp_Yaw,temp_Yaw_tc,temp_pitch,temp_pitch_tc,temp_eular_x = 0;
/*断电之后重新启动的时候的值*/
float savelife_point = 1;
/**
  * @brief  获取云台Yaw和Pitch的旋转角度（分别以中间和以底下为零点）
  * @param[in]  None
  * @retval 角度
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
  * @brief  强制设置云台IMU坐标（绕过缓冲）
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
  * @brief  强制设置云台机械坐标（绕过缓冲区）
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
//    savelife_point = 0;
    Cloud.LpfAttFactor = Cloud_LpfAttFactor;
    /*圈数归零*/
    /*考虑到由于一开始电机可能在圈数范围外*/
//		M6623s[0].turnCount = 0;
    M6623s[1].turnCount = 0;
    Cloud_IMU.turnCount = 0;

//		temp_Yaw = M6623s[0].totalAngle;
//		temp_Yaw_tc = M6623s[0].turnCount;
//
//		temp_pitch = M6623s[1].totalAngle;
//		temp_pitch_tc = M6623s[0].turnCount;
//		temp_eular_x = Cloud_IMU.eular.yaw;

    /*直接读取一开始的电机的位置（因为是先跑CAN函数的【这就是为什么要延时的原因】）*/
    /*和之前的电机赋值不同，之前的是一开始把值定到某一个点上面从而实现初始化伺服的功能*/
    /*这次是直接读取一开始电机的值（识别当前位置的值）并把他作为一开始的值来弄*/


//    Cloud.yawRaw = Cloud.yawLPF = M6623s[0].totalAngle = Cloud_IMU.eular.yaw *22.75f;
    Cloud.yawRaw = Cloud.yawLPF = M6623s[0].totalAngle;
    Cloud.pitchRaw = Cloud.yawLPF = M6623s[1].totalAngle;
    Cloud.mode = Cloud_Mode_Normal;

    /*射击初始化，包含了初始化点数的相加*/
    Shoot_Init();

    //双调控测试
//    PositionPID_paraReset(&M6623s[0].pid, -4.3f, -0.0f, -20.3f, 4000, 1000);

    //PID初始化
    //云台电机机械角度闭环
    //云台pitch轴电机pid
    PositionPID_paraReset(&M6623s[1].pid_speed, -8.0f, 0.0f, -12.0f, 4000, 0);
    PositionPID_paraReset(&M6623s[1].pid_angle, 1.5f, 0.0f, 0.0f, 500, 0);
    //云台yaw轴电机pid
    PositionPID_paraReset(&M6623s[0].pid_speed, -10.0f, 0.0f, 0.0f, 4000, 0);
    PositionPID_paraReset(&M6623s[0].pid_angle, 2.0f, 0.0f, 1.0f, 500, 0);

    //云台电机IMU闭环
    //云台方向闭环
    Cloud.IMUYawRaw = Cloud.IMUYawLPF = Cloud_IMU.totalYaw;
    Cloud.IMUPitchRaw = Cloud.IMUPitchLPF = Cloud_IMU.eular.roll;
    /*云台底盘初始相差角度*/
//	IMU_Yaw_Offset = Cloud_IMU.totalYaw - Chassis_IMU.totalYaw;
    //Yaw
    PositionPID_paraReset(&Cloud.YawAttitude_pid, -1.5f, 0.0f, 0.0f, 500, 0);
    PositionPID_paraReset(&Cloud.YawSpeed_pid, -80.0f, 0.0f, -60.0f, 4000, 0);
    //Pitch
    PositionPID_paraReset(&Cloud.RollAttitude_pid, -2.0f, 0.0f, 0.0f, 500, 0);
    PositionPID_paraReset(&Cloud.RollSpeed_pid, -60.0f, 0.0f, -40.0f, 4000, 0);
}

/**
  * @brief  云台控制处理-普通模式
  * @param[in]  delta_yaw		航向角变化量
  *				delta_pitch		俯仰角变化量
  *				shoot	射击使能
  *				mode	模式 - 除Status_ControlOFF外，其他正常控制
  * @retval None
  */

void Cloud_processing_Normal(float delta_yaw, float delta_pitch, uint8_t mode)
{
    //因为切换成为普通模式了，这个时候要一直保持最后的IMU的值，防止爆炸
    //保持IMU角度跟随，防止切换的时候炸鸡
    Cloud_setIMUPosForced(Cloud_IMU.totalYaw, Cloud_IMU.eular.roll);

    if(mode == ControlMode_OFF || Cloud_IMU.offLineFlag)
    {
        //以当前位置为下次启动位置，防炸
        Cloud_setAbsPosForced(M6623s[0].totalAngle, M6623s[1].totalAngle);
        Cloud_setCurrent(0, 0, 0, 0);
        friction_turnOff();
        return;
    }

    //遥控器离线
    if(dr16_data.offLineFlag)
    {
        delta_yaw = delta_pitch = 0.0f;
        friction_turnOff();
    }

    Cloud.yawRaw -= delta_yaw;
    Cloud.pitchRaw -= delta_pitch;

    //云台限幅begin
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
    //云台限幅end

    //平滑处理begin
    Filter_IIRLPF(&Cloud.yawRaw, &Cloud.yawLPF, Cloud.LpfAttFactor);
    Filter_IIRLPF(&Cloud.pitchRaw, &Cloud.pitchLPF, Cloud.LpfAttFactor);
    //平滑处理end

    M6623_setTargetAngle(M6623_YAW, Cloud.yawLPF);
    M6623_setTargetAngle(M6623_PITCH, Cloud.pitchLPF);
		
    Shoot_processing();


    /*************6623_BEGIN****************/

    if(!M6623s[0].offLineFlag)
    {
        //PID计算
        //角度PID计算(外环)
        int M6623s_PIDOut = Position_PID(&M6623s[0].pid_angle, M6623s[0].targetAngle, M6623s[0].totalAngle);
        //速度PID计算(内环)
        M6623s[0].outCurrent = Position_PID(&M6623s[0].pid_speed, M6623s_PIDOut, Cloud_IMU.gyro.z);
        //清标志位
        M6623s[0].infoUpdateFlag = 0;


    }

    if(!M6623s[1].offLineFlag)
    {
        //PID计算
        //角度PID计算(外环)
        int M6623s_PIDOut = Position_PID(&M6623s[1].pid_angle, M6623s[1].targetAngle, M6623s[1].totalAngle);
        //速度PID计算(内环)
        M6623s[1].outCurrent = Position_PID(&M6623s[1].pid_speed, M6623s_PIDOut, Cloud_IMU.gyro.y);
        //清标志位
        M6623s[1].infoUpdateFlag = 0;
    }

    /*************6623_END****************/

    //设定电机电流值

    Cloud_setCurrent(M6623s[0].outCurrent, M6623s[1].outCurrent, M2006s[1].outCurrent, 0);

}

/**
  * @brief  云台控制处理-带IMU模式
  * @param[in]  delta_yaw		航向角变化量
  *				delta_pitch		俯仰角变化量
  *				shoot	射击使能
  *				mode	模式 - 除Status_ControlOFF外，其他正常控制
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
    /*保持机械X轴角度的跟随*/
    Cloud.yawLPF = Cloud.yawRaw = M6623s[0].totalAngle;
    /*如果IMU掉线了，就保持最后的IMU*/
    if(mode == ControlMode_OFF || Cloud_IMU.offLineFlag)
    {
        //以当前位置为下次启动位置，防炸
        //设置回他原来的角度
        /*totalYaw是他累积的角度，在M6623的CAN函数里面返回*/
        Cloud_setIMUPosForced(Cloud_IMU.totalYaw, Cloud_IMU.eular.roll);
        //同理，设置回他原来的角度
        Cloud.pitchLPF = Cloud.pitchRaw = M6623s[1].totalAngle;
        Cloud_setCurrent(0, 0, 0, 0);
        friction_turnOff();
        return;
    }

    //遥控器离线
    if(dr16_data.offLineFlag)
    {

        delta_yaw = delta_pitch = 0.0f;
        friction_turnOff();
    }

    /*累加*/
    Cloud.IMUYawRaw += delta_yaw/30.0f;
    Cloud.pitchRaw -= delta_pitch;


    /*动态IMU定边界点（无论是哪个地方启动）*/
    Cloud.IMUYawMax = Cloud_IMU.totalYaw + Get_Cloud_YAWAngle_withLeft();

    Cloud.IMUYawMin = Cloud_IMU.totalYaw - (M6623_AngleToDEG(Cloud_Yaw_delta) - Get_Cloud_YAWAngle_withLeft());

    Cloud.IMUPitchMax = Cloud_IMU.eular.roll + Get_Cloud_PITCHAngle_withDown();

    Cloud.IMUPitchMin = Cloud_IMU.eular.roll - (M6623_AngleToDEG(Cloud_Pitch_delta) - Get_Cloud_PITCHAngle_withDown());


    //yaw
    //【云台限幅和回弹】
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

    /*滤波处理*/
    Filter_IIRLPF(&Cloud.IMUYawRaw, &Cloud.IMUYawLPF, 0.4);

    Filter_IIRLPF(&Cloud.pitchRaw, &Cloud.pitchLPF, 0.1);
    M6623_setTargetAngle(M6623_PITCH, Cloud.pitchLPF);

    /*射击判定*/
    Shoot_processing();

    /*双环计算开始*/
    if(!M6623s[0].offLineFlag)
    {

        float M6623s_YawOPIDOut;
        //PID计算

        //角度PID计算(外环)
        M6623s_YawOPIDOut = Position_PID(&Cloud.YawAttitude_pid, Cloud.IMUYawLPF, Cloud_IMU.totalYaw);
        //速度PID计算(内环)
        M6623s[0].outCurrent = Position_PID(&Cloud.YawSpeed_pid, M6623s_YawOPIDOut, Cloud_IMU.gyro.z);

        //M6623s[0].outCurrent = Position_PID(&Cloud.YawAttitude_pid, Cloud.IMUtargetYawLPF, Cloud_IMU.totalYaw);
        //清标志位
        M6623s[0].infoUpdateFlag = 0;


    }

    if(!M6623s[1].offLineFlag)
    {
        //PID计算
        //角度PID计算(外环)
        int M6623s_PIDOut = Position_PID(&M6623s[1].pid_angle, M6623s[1].targetAngle, M6623s[1].totalAngle);
        //速度PID计算(内环)
        M6623s[1].outCurrent = Position_PID(&M6623s[1].pid_speed, M6623s_PIDOut, Cloud_IMU.gyro.y);
        //清标志位
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


