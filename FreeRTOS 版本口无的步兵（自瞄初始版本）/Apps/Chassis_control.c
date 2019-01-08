#include "Chassis_control.h"

Chassis_st Chassis;


/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    Chassis_Init
  * @brief   底盘基本初始化
  * @param   None
  * @author  口无
  * @Data    2018-10-30
 **/
/* -------------------------------- end -------------------------------- */
void Chassis_Init(void)
{
    /*滤波系数设置*/
    Chassis.Filter_LPFfactor = Fif_Factor;


    /*底盘基本PID初始化*/
    IncrementalPID_Init(&RM3508s[0].pid_wheel, 2.5f, 1.5f, 0.0f, 8000, 1000);
    IncrementalPID_Init(&RM3508s[1].pid_wheel, 2.5f, 1.5f, 0.0f, 8000, 1000);
    IncrementalPID_Init(&RM3508s[2].pid_wheel, 2.5f, 1.5f, 0.0f, 8000, 1000);
    IncrementalPID_Init(&RM3508s[3].pid_wheel, 2.5f, 1.5f, 0.0f, 8000, 1000);


    PositionPID_Init(&Chassis.Fowllow_Attitude_pid, 3.1f, 0.0f, 13.5f, 4500, 500);
}



/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    Chassis_Process
  * @brief   底盘处理
  * @param   Vx: Vx的速度
**					 Vy: Vy的速度
**			 		 VOmega: 自旋的速度
**			 		 mode: 模式
  * @author  口无
  * @Data    2018-11-04
 **/
/* -------------------------------- end -------------------------------- */
int16_t speed[4];
void Chassis_Process(float Vx,float Vy,float VOmega,uint8_t switchmode)
{

    float tempVOmega = 0.0f;

    if(switchmode == Status_ControlOFF)
    {
        Chassis_CurrentSetting(0,0,0,0);
        return;
    }

    /*滤波处理*/
    Filter_IIRLPF(&Vx,&Chassis.xLPF,Chassis.Filter_LPFfactor);
    Filter_IIRLPF(&Vy,&Chassis.yLPF,Chassis.Filter_LPFfactor);
    Filter_IIRLPF(&VOmega,&Chassis.zLPF,Chassis.Filter_LPFfactor);


    /*底盘闭环（面对炮台归位）*/
    if(pc.PCMode != Mode_Chassiscal_NoneHead)
		{
			if(pc.PCMode == Mode_Cloud_PlatformFollowing)
			{
					Chassis.FollowYawRaw = 0.0f;
					if( (abs(RM6623s[0].totalAngle - Cloud_Yaw_Center) > 20 || ( abs(Vy)+abs(Vx) )> 5.0f))
					{
							/*相对于云台需要的跟随的角度*/
							Chassis.FollowYawRaw = PositionPID_Calculation(&Chassis.Fowllow_Attitude_pid, Cloud_Yaw_Center, RM6623s[0].totalAngle);
					}
					Filter_IIRLPF(&Chassis.FollowYawRaw, &Chassis.FollowYawLPF, 0.1);
					tempVOmega = Chassis.zLPF + Chassis.FollowYawLPF;
			}
			else
			{
					tempVOmega = Chassis.zLPF;
			}
			MecanumCalculation(Chassis.xLPF,Chassis.yLPF,tempVOmega,speed);
		}	
		else
		{
			MecanumCalculation(Chassis.xLPF,Chassis.yLPF,Chassis.zLPF,speed);
		}

		

    /*麦轮解算*/
    
		
    for(int i = 0; i<4; i++)
    {
        if(RM3508s[i].UpdateFlag == 1)
        {
            RM3508s[i].targetSpeed = speed[i];

            RM3508s[i].outCurrent = IncrementalPID_Calculation(&RM3508s[i].pid_wheel, RM3508s[i].targetSpeed, RM3508s[i].realSpeed);

            RM3508s[i].UpdateFlag = 0;
        }
    }


    Chassis_CurrentSetting(RM3508s[0].outCurrent, RM3508s[1].outCurrent, RM3508s[2].outCurrent, RM3508s[3].outCurrent);
}




/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    MecanumCalculation
  * @brief   麦轮解算
  * @param   Vx: Vx的速度
**			 		 Vy: Vy的速度
**			 		 VOmega: 自旋的速度
**			 		 Speed(st): 速度结构体
  * @author  口无
  * @Data    2018-11-04
 **/
/* -------------------------------- end -------------------------------- */

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

    for(uint8_t i = 0, MaxSpeed = 0; i < 4; i++)//计算四个轮子速度的最大值
    {
        if(abs(tempSpeed[i]) > MaxSpeed)//abs()为绝对值函数
        {
            MaxSpeed = abs(tempSpeed[i]);
        }
    }

    /*速度分配*/
    /*有点类似限制速度的作用，把速度限制在3500*/
    if(MaxSpeed > 3500/*WheelMaxSpeed*/)//WheelMaxSpeed 单轮最大速度
    {
        Param = (float)3500 / MaxSpeed;
    }

    Speed[0] = tempSpeed[0] * Param;
    Speed[1] = tempSpeed[1] * Param;
    Speed[2] = tempSpeed[2] * Param;
    Speed[3] = tempSpeed[3] * Param;

}



/**
  * @brief  功率限制
  * @param[in]  CurrentLimit
  * @param[out]	Speed	速度
  * @retval None
  */

void Chassis_powerLimit(RM3508_st *p_M3508s, float CurrentLimit)
{
    //float tempPowerMax = powerMax;
    float Param = 1;
    float MaxCurrent = 0;

    //计算最大电流
    for(uint8_t i = 0; i < 4; i++)
    {
        if(abs(p_M3508s[i].outCurrent) > MaxCurrent)
        {
            MaxCurrent = abs(p_M3508s[i].outCurrent);
        }
    }

    //电流分配
    if(MaxCurrent > CurrentLimit)
    {
        Param = CurrentLimit / MaxCurrent;
    }

    p_M3508s[0].outCurrent *= Param;
    p_M3508s[1].outCurrent *= Param;
    p_M3508s[2].outCurrent *= Param;
    p_M3508s[3].outCurrent *= Param;


}


