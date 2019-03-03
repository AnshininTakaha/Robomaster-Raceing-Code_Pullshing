#include "CloudControl.h"

Cloud_t Cloud;


void Cloud_Init(void)
{
    /*滤波系数设置*/
    Cloud.Filter_LPFfactor = Cloud_LpfAttFactor;

    /*机械角度闭环初始化*/
    Cloud.Yaw_Raw = Cloud.Yaw_LPF = RM6623s[0].totalAngle;
    Cloud.Pitch_Raw = Cloud.Pitch_LPF = RM6623s[1].totalAngle;
    // Cloud.Pitch_Raw = Cloud.Pitch_LPF = Cloud_Pitch_Center;

    /*YAW轴PID初始化*/
    PositionPID_Init(&RM6623s[0].pid_speed,-10.0f, 0.0f, 0.0f, 4000, 0);
    PositionPID_Init(&RM6623s[0].pid_angle,2.0f, 0.0f, 1.0f, 500, 0);

    /*PITCH轴PID初始化*//**/
    PositionPID_Init(&RM6623s[1].pid_speed,-20.0f, 0.0f, -10.5f, 4000, 0);
    PositionPID_Init(&RM6623s[1].pid_angle, 0.23f, 0.0f, 0.5f, 500, 0);

    /*云台角度闭环初始化*/
    Cloud.IMUYaw_Raw = Cloud.IMUYaw_LPF = Cloud_IMU.totalYaw;
    Cloud.IMUPitch_Raw = Cloud.IMUPitch_LPF = Cloud_IMU.eular.roll;

    /*Yaw*//**/
    PositionPID_Init(&Cloud.YAW_Attitude_pid,  -1.3f, -2.5f, -0.5f, 500, 0);
    // PositionPID_Init(&Cloud.YAW_Attitude_pid,  -1.3f, -0.31f, -1.6f, 500, 0);
		
    PositionPID_Init(&Cloud.YAW_Speed_pid, -60.0f, 0.0f, -48.0, 4000, 0);
		

    
		
	
}


void Cloud_Judgement(void)
{
    float Cloud_delta_Yaw = 0.0f,Cloud_delta_Pitch = 0.0f;

    Cloud_delta_Yaw = rocket_Right.x/8;
		Cloud_delta_Pitch = rocket_Right.y/7;
		
    Double_Cloud_process(Cloud_delta_Yaw,Cloud_delta_Pitch,GetSwitch_ModeCloud());
}


void Double_Cloud_process(float Delta_YAW,float Delta_Ptich,uint8_t switchmode)
{
    /*YAW轴机械角度跟随*/
    Cloud.Yaw_LPF = Cloud.Yaw_Raw = RM6623s[0].totalAngle;


    if(switchmode == Status_ControlOFF || Cloud_IMU.OFFLINE_SET)
    {
        ForceSetting_YAWIMUCloudpointing(Cloud_IMU.totalYaw,Cloud_IMU.eular.yaw);
        Cloud.Pitch_LPF = Cloud.Pitch_Raw = Cloud_Pitch_Center;
        Cloud_And_Emitter_CurrentSetting(0,0,0,0);
        return;
    }


    if(DR16.OFFLINE_SET ==1)
    {
        Delta_YAW =0;
        Delta_Ptich =0;
    }
		
    Cloud.IMUYaw_Raw += Delta_YAW/30.0f;
    Cloud.Pitch_Raw -= Delta_Ptich;
    
    // Shoot_process();

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
        //清标志位
        RM6623s[0].UpdateFlag = 0;


    }

    if(!RM6623s[1].OFFLINE_SET)
    {
        //PID计算
        //角度PID计算(外环)
        int M6623s_PIDOut = FuzzyPID_PosCalculation(&RM6623s[1].pid_angle, RM6623s[1].targetAngle, RM6623s[1].totalAngle);
        //速度PID计算(内环)
        RM6623s[1].outCurrent = PositionPID_Calculation(&RM6623s[1].pid_speed, M6623s_PIDOut, Cloud_IMU.gyro.y);
        //清标志位
        RM6623s[1].UpdateFlag = 0;
    }


    Cloud_And_Emitter_CurrentSetting(RM6623s[0].outCurrent,RM6623s[1].outCurrent,RM2006s[0].outCurrent,0);

}

void ForceSetting_YAWIMUCloudpointing(float YAW_setting,float PITCH_setting)
{
    Cloud.IMUYaw_LPF = Cloud.IMUYaw_Raw = YAW_setting;
    Cloud.IMUPitch_LPF = Cloud.IMUPitch_Raw = PITCH_setting;
}

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

void M6623_setTargetAngle(int id, int32_t angle)
{
    RM6623s[id].targetAngle = angle;
}

