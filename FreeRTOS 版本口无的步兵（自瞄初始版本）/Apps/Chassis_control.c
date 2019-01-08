#include "Chassis_control.h"

Chassis_st Chassis;


/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    Chassis_Init
  * @brief   ���̻�����ʼ��
  * @param   None
  * @author  ����
  * @Data    2018-10-30
 **/
/* -------------------------------- end -------------------------------- */
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



/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    Chassis_Process
  * @brief   ���̴���
  * @param   Vx: Vx���ٶ�
**					 Vy: Vy���ٶ�
**			 		 VOmega: �������ٶ�
**			 		 mode: ģʽ
  * @author  ����
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

    /*�˲�����*/
    Filter_IIRLPF(&Vx,&Chassis.xLPF,Chassis.Filter_LPFfactor);
    Filter_IIRLPF(&Vy,&Chassis.yLPF,Chassis.Filter_LPFfactor);
    Filter_IIRLPF(&VOmega,&Chassis.zLPF,Chassis.Filter_LPFfactor);


    /*���̱ջ��������̨��λ��*/
    if(pc.PCMode != Mode_Chassiscal_NoneHead)
		{
			if(pc.PCMode == Mode_Cloud_PlatformFollowing)
			{
					Chassis.FollowYawRaw = 0.0f;
					if( (abs(RM6623s[0].totalAngle - Cloud_Yaw_Center) > 20 || ( abs(Vy)+abs(Vx) )> 5.0f))
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
			MecanumCalculation(Chassis.xLPF,Chassis.yLPF,tempVOmega,speed);
		}	
		else
		{
			MecanumCalculation(Chassis.xLPF,Chassis.yLPF,Chassis.zLPF,speed);
		}

		

    /*���ֽ���*/
    
		
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
  * @brief   ���ֽ���
  * @param   Vx: Vx���ٶ�
**			 		 Vy: Vy���ٶ�
**			 		 VOmega: �������ٶ�
**			 		 Speed(st): �ٶȽṹ��
  * @author  ����
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



/**
  * @brief  ��������
  * @param[in]  CurrentLimit
  * @param[out]	Speed	�ٶ�
  * @retval None
  */

void Chassis_powerLimit(RM3508_st *p_M3508s, float CurrentLimit)
{
    //float tempPowerMax = powerMax;
    float Param = 1;
    float MaxCurrent = 0;

    //����������
    for(uint8_t i = 0; i < 4; i++)
    {
        if(abs(p_M3508s[i].outCurrent) > MaxCurrent)
        {
            MaxCurrent = abs(p_M3508s[i].outCurrent);
        }
    }

    //��������
    if(MaxCurrent > CurrentLimit)
    {
        Param = CurrentLimit / MaxCurrent;
    }

    p_M3508s[0].outCurrent *= Param;
    p_M3508s[1].outCurrent *= Param;
    p_M3508s[2].outCurrent *= Param;
    p_M3508s[3].outCurrent *= Param;


}


