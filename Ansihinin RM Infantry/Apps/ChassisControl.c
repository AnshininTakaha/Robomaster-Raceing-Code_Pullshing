#include "ChassisControl.h"

Chassis_t Chassis;
/**
* @name Chassis_Init
* @brief ���̳�ʼ��
* @param None
* @retval 
*/
void Chassis_Init(void)
{
    /*�˲�ϵ������*/
    Chassis.Filter_LPFfactor = Fif_Factor;


    /*���̻���PID��ʼ��*/
    IncrementalPID_Init(&RM3508s[0].pid_wheel, 2.5f, 1.5f, 0.0f, 8000, 1000);
    IncrementalPID_Init(&RM3508s[1].pid_wheel, 2.5f, 1.5f, 0.0f, 8000, 1000);
    IncrementalPID_Init(&RM3508s[2].pid_wheel, 2.5f, 1.5f, 0.0f, 8000, 1000);
    IncrementalPID_Init(&RM3508s[3].pid_wheel, 2.5f, 1.5f, 0.0f, 8000, 1000);


    PositionPID_Init(&Chassis.Fowllow_Attitude_pid, 3.1f, 0.0f, 13.5f, 4500, 500);
}


/**
* @name Chassis_Judgement
* @brief �����ٶȸ�ֵ�ж�
* @param None
* @retval 
*/
void Chassis_Judgement(void)
{
    float Chassis_Vx = 0.0f,Chassis_Vy = 0.0f,Chassis_VOmega = 0.0f;
    

    Chassis_Vx = rocket_Left.x /660 *Chassis_MaxSpeed_X;
    Chassis_Vy = rocket_Left.y /600 *Chassis_MaxSpeed_Y;
    
    
    Chassis_Process(Chassis_Vx,Chassis_Vy,Chassis_VOmega,GetSwitch_ModeChassis());
}

/**
* @name Chassis_Process
* @brief ���̴���
* @param [in] float Vx     Vx���ٶ�
*        [in] float Vy     Vy���ٶ�
*        [in] float VOmega �������ٶ�
*        [in] uint8_t switchmode ѡ���ģʽ
* @retval 
*/
int16_t s_speed[4];
void Chassis_Process(float Vx,float Vy,float VOmega,uint8_t switchmode)
{
    float tempVOmega = 0.0f;

    if(switchmode == Status_ControlOFF)
    {
        Chassis_CurrentSetting(0,0,0,0);
        return;
    }

    Filter_IIRLPF(&Vx,&Chassis.xLPF,Chassis.Filter_LPFfactor);
    Filter_IIRLPF(&Vy,&Chassis.yLPF,Chassis.Filter_LPFfactor);
    Filter_IIRLPF(&VOmega,&Chassis.zLPF,Chassis.Filter_LPFfactor);

    if(pc.PCMode != Mode_Chassiscal_NoneHead)
	{
		if(pc.PCMode == Mode_Cloud_PlatformFollowing)
		{
            Chassis.FollowYawRaw = 0.0f;
            if( (abs(RM6623s[0].totalAngle - Cloud_Yaw_Center) > 20 || ( abs(Vy)+abs(Vx) )> 5.0f)/*abs(RM6623s[0].totalAngle - Cloud_Yaw_Center) > 0 || ( abs(Vy)+abs(Vx) )> 0.0f)*/)
            {
                /*�������̨��Ҫ�ĸ���ĽǶ�*/
                Chassis.FollowYawRaw = PositionPID_Calculation(&Chassis.Fowllow_Attitude_pid, Cloud_Yaw_Center, RM6623s[0].totalAngle);
            }
            Filter_IIRLPF(&Chassis.FollowYawRaw, &Chassis.FollowYawLPF, 0.1);
            tempVOmega = Chassis.zLPF + Chassis.FollowYawLPF;
        }
        else
        {
            tempVOmega = Chassis.zLPF;
        }
        /*���ֽ���*/
        MecanumCalculation(Chassis.xLPF,Chassis.yLPF,tempVOmega,s_speed);
    }
    else
    {
        /*���ֽ���*/
        MecanumCalculation(Chassis.xLPF,Chassis.yLPF,tempVOmega,s_speed);
    }

    
   
    for(int i = 0; i<4; i++)
    {
        if(RM3508s[i].UpdateFlag == 1)
        {
            RM3508s[i].targetSpeed = s_speed[i];

            RM3508s[i].outCurrent = IncrementalPID_Calculation(&RM3508s[i].pid_wheel, RM3508s[i].targetSpeed, RM3508s[i].realSpeed);

            RM3508s[i].UpdateFlag = 0;
        }
    }

    /*��е�����趨*/
    Chassis_CurrentSetting(RM3508s[0].outCurrent, RM3508s[1].outCurrent, RM3508s[2].outCurrent, RM3508s[3].outCurrent);
}

/**
* @name MecanumCalculation
* @brief ����ģ�ͽ���
* @param [in] float Vx     Vx���ٶ�
*        [in] float Vy     Vy���ٶ�
*        [in] float VOmega �������ٶ�
*        [in] uint8_t switchmode ѡ���ģʽ
* @retval 
*/
void MecanumCalculation(float Vx, float Vy, float VOmega, int16_t *Speed)
{
    float tempSpeed[4];
    float Param = 1;
    float MaxSpeed = 0;

    VAL_LIMIT(Vx, -Chassis_MaxSpeed_X, Chassis_MaxSpeed_X);
    VAL_LIMIT(Vy, -Chassis_MaxSpeed_Y, Chassis_MaxSpeed_Y);
    VAL_LIMIT(VOmega, -Chassis_MaxSpeed_W, Chassis_MaxSpeed_W);

    tempSpeed[0] = Vx - Vy + VOmega;
    tempSpeed[1] = Vx + Vy + VOmega;
    tempSpeed[2] = -Vx + Vy + VOmega;
    tempSpeed[3] = -Vx - Vy + VOmega;

    for(uint8_t i = 0, MaxSpeed = 0; i < 4; i++)//�����ĸ������ٶȵ����ֵ
    {
        if(abs(tempSpeed[i]) > MaxSpeed)//abs()Ϊ����ֵ����
        {
            MaxSpeed = abs(tempSpeed[i]);
        }
    }

    /*�ٶȷ���*/
    /*�е����������ٶȵ����ã����ٶ�������3500*/
    if(MaxSpeed > 3500/*WheelMaxSpeed*/)//WheelMaxSpeed ��������ٶ�
    {
        Param = (float)3500 / MaxSpeed;
    }

    Speed[0] = tempSpeed[0] * Param;
    Speed[1] = tempSpeed[1] * Param;
    Speed[2] = tempSpeed[2] * Param;
    Speed[3] = tempSpeed[3] * Param;

}

