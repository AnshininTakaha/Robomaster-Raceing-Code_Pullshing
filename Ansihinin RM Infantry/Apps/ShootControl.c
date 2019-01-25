#include "ShootControl.h"

/*射击标志位的结构体初始化*/
Fire_st Fire;

/*摩擦轮标志位*/
firction_st Firction;

void Shoot_Init(void)
{
    Fire.Fire_ready = 0;
    Fire.Fire_shoot_Flag = 0;

    Firction.firction_ready = 0;
    Firction.firctionspeed_Raw = 1600;
   
    TIM12_PWMOutput(99,1999,1000);

    // TIM5_PWMOutput(99,1999,1000);


    PositionPID_Init(&RM2006s[0].pid_speed, 1.5f, 0.04f, 0.0f, 8000, 2000);
    PositionPID_Init(&RM2006s[0].pid_angle, 0.3f, 0.0f, 0.8f, 4000, 500);
}

void firction_speedSetting(uint16_t speed)
{
    if(speed > frictionSpeedMax)
    {
        speed = frictionSpeedMax;
    }
    if(speed < frictionSpeedMin)
    {
        speed = frictionSpeedMin;
    }

    TIM_SetComparex[0](TIM12, speed);
    TIM_SetComparex[1](TIM12, speed);

    // TIM_SetComparex[0](TIM5, speed);
    // TIM_SetComparex[1](TIM5, speed);
}

uint16_t ON_temp_s = 1000;

void firction_ON(void)
{
    
    ON_temp_s+=100;
    firction_speedSetting(ON_temp_s);

    
    if(ON_temp_s > Firction.firctionspeed_Raw)
    {
        firction_speedSetting(Firction.firctionspeed_Raw);
        ON_temp_s = Firction.firctionspeed_Raw;
        Firction.firction_ready = 1;
    }
}

void firction_OFF(void)
{
    
    ON_temp_s = 1000-100;
    firction_speedSetting(1000);
    Firction.firction_ready = 0;
}


void Shoot_process(void)
{
    static float Shooting_Conut = 0;
    
    if(Firction.firction_ready == 0)
    {
        firction_ON();
    }

    
    if(Fire.Fire_ready && Firction.firction_ready)
    {
        if(Shooting_Conut++ > Parting_Speed)
        {
            RM2006s[0].targetAngle += DA_ZE;
            Fire.Fire_out_number++;
            Shooting_Conut =0;
            Fire.loading_finish =1;
        }
    }

    if(RM2006s[0].OFFLINE_SET == 0)
    {
        static uint8_t Motor_blocking =0;
        static int Blocking_time = 0;

        int M2006s_PIDOut = PositionPID_Calculation(&RM2006s[0].pid_angle, RM2006s[0].targetAngle, RM2006s[0].totalAngle);
        RM2006s[0].outCurrent = PositionPID_Calculation(&RM2006s[0].pid_speed, M2006s_PIDOut, RM2006s[0].realSpeed);

        /*电机是否卡弹*/
        if(abs(RM2006s[0].outCurrent)>6200 && abs(RM2006s[0].realSpeed) < 50 && Blocking_time++>50)
        {
            if(Motor_blocking == 0)
            {
                
                RM2006s[0].targetAngle -= DA_ZE*2;
                Motor_blocking = 1;
            }
        }

        
        /*pid差值是否超过一定值*/
        if(abs(RM2006s[0].pid_angle.error) < 8000)
        {
            
            Motor_blocking = 0;
            Blocking_time = 0;

            
            Fire.loading_finish =0;
        }

        /*圈数清零*/
        if(RM2006s[0].turnCount > 100)
        {
            RM2006s[0].targetAngle = RM2006s[0].targetAngle - ((RM2006s[0].turnCount)*8192);
            RM2006s[0].turnCount = 0;
        }

    }

}








