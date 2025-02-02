#include "Cloud_control.h"

Cloud_st Cloud;
GY_IMU_t Cloud_IMU;


/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    Cloud_Init
  * @brief   云台初始化
  * @param   None
  * @author  口无
  * @Data    2018-11-06
 **/
/* -------------------------------- end -------------------------------- */

void Cloud_Init(void)
{
    /*滤波系数设置*/
    Cloud.Filter_LPFfactor = Cloud_LpfAttFactor;

    /*防止圈数读取的时候出问题*/
//	RM6623s[0].turnCount = 0;
//	RM6623s[1].turnCount = 0;
    Cloud_IMU.turnCount = 0;


    /**************************机械控制***************************/

    /*机械角度闭环初始化*/
    Cloud.Yaw_Raw = Cloud.Yaw_LPF = RM6623s[0].totalAngle;
    Cloud.Pitch_Raw = Cloud.Pitch_LPF = RM6623s[1].totalAngle;


    /*YAW轴PID初始化*/
    PositionPID_Init(&RM6623s[0].pid_speed,-10.0f, 0.0f, 0.0f, 4000, 0);
    PositionPID_Init(&RM6623s[0].pid_angle,2.0f, 0.0f, 1.0f, 500, 0);

    /*PITCH轴PID初始化*/
    PositionPID_Init(&RM6623s[1].pid_speed,-6.0f, 0.0f, -20.0f, 4000, 0);
    PositionPID_Init(&RM6623s[1].pid_angle,2.0f, 0.0f, 0.0f, 500, 0);

    /**************************陀螺仪控制***************************/

    /*云台角度闭环初始化*/
    Cloud.IMUYaw_Raw = Cloud.IMUYaw_LPF = Cloud_IMU.totalYaw;
    Cloud.IMUPitch_Raw = Cloud.IMUPitch_LPF = Cloud_IMU.eular.roll;

    /*Yaw*/
    PositionPID_Init(&Cloud.YAW_Attitude_pid, -1.5f, 0.0f, 0.0f, 500, 0);
    PositionPID_Init(&Cloud.YAW_Speed_pid, -75.0f, 0.0f, -49.5f, 4000, 0);

    /*Pitch*/
    PositionPID_Init(&Cloud.Roll_Attitude_pid,-2.0f, 0.0f, 0.0f, 500, 0);
    PositionPID_Init(&Cloud.Roll_Speed_pid, -60.0f, 0.0f, -40.0f, 4000, 0);
}

float Cloud_shift_point;
void Double_Cloud_process(float Delta_YAW,float Delta_Ptich,uint8_t switchmode)
{
    /*YAW轴机械角度跟随*/
    Cloud.Yaw_LPF = Cloud.Yaw_Raw = RM6623s[0].totalAngle;


    if(switchmode == Status_ControlOFF || Cloud_IMU.OFFLINE_SET)
    {
        Cloud_shift_point = 1;
        ForceSetting_YAWIMUCloudpointing(Cloud_IMU.totalYaw,Cloud_IMU.eular.roll);
        Cloud.Pitch_LPF = Cloud.Pitch_Raw = Cloud_Pitch_Center;
        Cloud_And_Emitter_CurrentSetting(0,0,0,0);
        return;
    }


    if(DR16.OFFLINE_SET ==1)
    {
        Delta_YAW =0;
        Delta_Ptich =0;
    }

    Shoot_process();

    /*遥控器赋值转换*/
    Cloud.IMUYaw_Raw += Delta_YAW/30.0f;
    Cloud.Pitch_Raw -= Delta_Ptich;

    /*动态IMU极值点控制*/
    Cloud.IMUYawAngleMax = Cloud_IMU.totalYaw + Get_Cloud_YAWAngle_withLeft();
    Cloud.IMUYawAngleMin = Cloud_IMU.totalYaw - (M6623_AngleToDEG(Cloud_Yaw_delta) - Get_Cloud_YAWAngle_withLeft());
    Cloud.IMUPitchAngleMax = Cloud_IMU.eular.roll + Get_Cloud_PITCHAngle_withDown();
    Cloud.IMUPitchAngleMin =  Cloud_IMU.eular.roll - (M6623_AngleToDEG(Cloud_Pitch_delta) - Get_Cloud_PITCHAngle_withDown());

    /*云台限幅和回弹*/
    /*无头模式的时候不限幅*/
    if(pc.PCMode == Mode_Cloud_PlatformFollowing)
    {
        if(Cloud_IMU.totalYaw > Cloud.IMUYawAngleMax)
        {
            if(Delta_YAW < 0.0f)
            {
                Cloud.IMUYaw_Raw += (Delta_YAW/8)/30.0f;
            }
            else
            {
                Cloud.IMUYaw_Raw = Cloud.IMUYawAngleMax;
            }
        }

        if(Cloud_IMU.totalYaw < Cloud.IMUYawAngleMin)
        {
            if(Delta_YAW > 0.0f)
            {
                Cloud.IMUYaw_Raw -= (Delta_YAW/8)/30.0f;
            }
            else
            {
                Cloud.IMUYaw_Raw = Cloud.IMUYawAngleMin;
            }
        }
    }

    if(Cloud.Pitch_Raw > Cloud_Pitch_Max)
    {
        Cloud.Pitch_Raw = Cloud_Pitch_Max;
    }
    if(Cloud.Pitch_Raw < Cloud_Pitch_Min)
    {
        Cloud.Pitch_Raw = Cloud_Pitch_Min;
    }

    Filter_IIRLPF(&Cloud.IMUYaw_Raw,&Cloud.IMUYaw_LPF,0.4);
    Filter_IIRLPF(&Cloud.Pitch_Raw,&Cloud.Pitch_LPF,0.1);

    M6623_setTargetAngle(1,Cloud.Pitch_LPF);

    if(!RM6623s[0].OFFLINE_SET)
    {

        float M6623s_YawOPIDOut;
        //PID计算

        //角度PID计算(外环)
        M6623s_YawOPIDOut = PositionPID_Calculation(&Cloud.YAW_Attitude_pid, Cloud.IMUYaw_LPF, Cloud_IMU.totalYaw);
        //速度PID计算(内环)
        RM6623s[0].outCurrent = PositionPID_Calculation(&Cloud.YAW_Speed_pid, M6623s_YawOPIDOut, Cloud_IMU.gyro.z);

        //M6623s[0].outCurrent = Position_PID(&Cloud.YawAttitude_pid, Cloud.IMUtargetYawLPF, Cloud_IMU.totalYaw);
        //清标志位
        RM6623s[0].UpdateFlag = 0;


    }

    if(!RM6623s[1].OFFLINE_SET)
    {
        //PID计算
        //角度PID计算(外环)
        int M6623s_PIDOut = PositionPID_Calculation(&RM6623s[1].pid_angle, RM6623s[1].targetAngle, RM6623s[1].totalAngle);
        //速度PID计算(内环)
        RM6623s[1].outCurrent = PositionPID_Calculation(&RM6623s[1].pid_speed, M6623s_PIDOut, Cloud_IMU.gyro.y);
        //清标志位
        RM6623s[1].UpdateFlag = 0;
    }

    Cloud_And_Emitter_CurrentSetting(RM6623s[0].outCurrent,RM6623s[1].outCurrent,RM2006s[0].outCurrent,0);

}



/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    ForceSetting_YAWIMUCloudpointing
  * @brief   强制设置云台YAW轴的IMU目标值
  * @param   YAW_setting: 对应的YAW轴的值
						 PITCH_setting:对应的Pitch的值
  * @author  口无
  * @Data    2018-11-06
 **/
/* -------------------------------- end -------------------------------- */

void ForceSetting_YAWIMUCloudpointing(float YAW_setting,float PITCH_setting)
{
    Cloud.IMUYaw_LPF = Cloud.IMUYaw_Raw = YAW_setting;
    Cloud.IMUPitch_LPF = Cloud.IMUPitch_Raw = PITCH_setting;
}


/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    ForceSetting_YAWABSCloudpointing
  * @brief   强制设置云台YAW轴的机械角度的目标值
  * @param   YAW_setting: 对应的YAW轴的值
						 PITCH_Setting：对应的PITCH轴的值
  * @author  口无
  * @Data    2018-11-06
 **/
/* -------------------------------- end -------------------------------- */
void ForceSetting_YAWABSCloudpointing(float YAW_Setting,float PITCH_Setting)
{
    Cloud.Yaw_LPF = Cloud.Yaw_Raw = YAW_Setting;
    Cloud.Pitch_LPF = Cloud.Pitch_Raw = PITCH_Setting;

}

/**
  * @brief  获取云台Yaw和Pitch的旋转角度（分别以中间和以底下为零点）
  * @param[in]  None
  * @retval 角度
  */
float Get_Cloud_YAWAngle_withCenter(void)
{
    return(RM6623s[0].totalAngle - Cloud_Yaw_Center) / 22.75f;
}

float Get_Cloud_YAWAngle_withLeft(void)
{
    return(RM6623s[0].totalAngle - Cloud_Yaw_Min) / 22.75f;
}

float Get_Cloud_PITCHAngle_withCenter(void)
{
    return(RM6623s[1].totalAngle - Cloud_Pitch_Center);
}

float Get_Cloud_PITCHAngle_withDown(void)
{
    return(RM6623s[1].totalAngle - Cloud_Pitch_Min);
}


/**
  * @brief  设定M6623电机的目标角度
  * @param  motorName 	电机名字 @ref M6623Name_e
  *			angle		电流值，范围 0~8191 由于设置0和8191会导致电机振荡，要做个限幅
  * @retval None
  */
void M6623_setTargetAngle(int id, int32_t angle)
{
    RM6623s[id].targetAngle = angle;
}
