/**
  ******************************************************************************
  * @file    Chassis_control.c
  * @author  Hare
  * @version V1.0
  * @date
  * @brief   底盘控制函数接口
  ******************************************************************************
  */

#include "Chassis_control.h"


//#define Chassis_LpfAttFactor 0.098f
Chassis_t Chassis;


/*调整代码写的顺序，方便你们看*/
void MecanumCalculation(float Vx, float Vy, float VOmega, int16_t *Speed);
void Chassis_powerLimit(M3508s_t *p_M3508s, float CurrentLimit);



/**
  * @brief  新底盘初始化
  * @retval None
  */

void Chassis_Init(void)
{
    Chassis.LpfAttFactor = Chassis_LpfAttFactor;
    Chassis.speedlimit = Chassis_SpeedNormal;
    Chassis.Power_OverflowFlag = 1;
    Chassis.swingspeed = Chassis_SwingSpeed_Normal;
    Chassis.mode = Chassis_Mode_Normal;

    for(int i =0; i<4; i++)
    {
        /*正常PID速度初始化*/
        IncrementalPID_paraReset(&M3508s[i].pid, 2.8f, 0.0f, 0.0f, 16000, 5000);
    }
    /*跟随PID初始化*/
    PositionPID_paraReset(&Chassis.FollowYawAttitude_pid, 3.1f, 0.0f, 13.5f, 4500, 500);

}


/**
  * @brief  旧/新底盘控制处理
  * @param[in]  Vx		x轴速度
  *				Vy		y轴速度
  *				Omega	偏向角
*				mode	模式 - 除Status_ControlOFF外，其他正常控制
  * @retval None
  */

void Chassis_processing(float Vx, float Vy, float VOmega, uint8_t mode)
{
    if(mode == Status_ControlOFF)
    {
        /*区分模式，如果处于第一种模式，就把轮子都停下来*/
        M3508_setCurrent(0, 0, 0, 0);
        return;
    }
//		printf("got");
//		printf("%f,%f,%f\r\n",Vx,Vy,VOmega);
    /*如果遥控器掉线*/
    if(dr16_data.offLineFlag)
    {
        Vx = Vy = VOmega;
    }
    int16_t speed[4];

    //平滑处理，作用是挤掉在数据发送过程中多余的尖波
    /*滤波的值是自己设置的*/
    Filter_IIRLPF(&Vx, &Chassis.xLPF, Chassis.LpfAttFactor);
    Filter_IIRLPF(&Vy, &Chassis.yLPF, Chassis.LpfAttFactor);
    Filter_IIRLPF(&VOmega, &Chassis.zLPF, Chassis.LpfAttFactor);
    /*通过滤波操作之后算出的值继续进行处理*/


    /*底盘方向闭环*/
    /*也是云台跟随的一个步骤*/
    float tempVOmega = 0.0f;
    /*在云台处于掉线状态且处于跟随模式的时候*/
    //【根据前面中断里面云台的赋予的值来进行计算之后赋值给速度】
    if((!M6623s[M6623_YAW].offLineFlag && Chassis.mode == Chassis_Mode_Follow))
    {
        /*那么就掉线*/
        Chassis.followYawRaw = 0.0f;
        /*只要前面两个中的一个成立且不在扭腰的状态*/
        if( (abs(M6623s[0].totalAngle - Cloud_Yaw_Center) > 682 || ( abs(Vy)+abs(Vx) )> 20.0f) && !Chassis.swingFlag)
        {
            /*相对于云台需要的跟随的角度*/
            Chassis.followYawRaw = Position_PID(&Chassis.FollowYawAttitude_pid, Cloud_Yaw_Center, M6623s[0].totalAngle);
            //Chassis_IMU.infoUpdateFlag = 0;
        }
        Filter_IIRLPF(&Chassis.followYawRaw, &Chassis.followYawLPF, 0.1);
        tempVOmega = Chassis.zLPF + Chassis.followYawLPF;


    }
    else
    {
        tempVOmega = Chassis.zLPF;
    }


    /*麦轮速度解算*/
    MecanumCalculation(Chassis.xLPF, Chassis.yLPF, tempVOmega, speed);





    /*计算出来的值在这里进行赋值（目标值），然后进行PID速度调整*/
    for(int i = 0; i<4; i++)
    {
        if(M3508s[i].infoUpdateFlag == 1)//判断他们的信息读取更新标志位置是否为1
        {
            /*如果是就写入他们的速度*/
            M3508s[i].targetSpeed = speed[i];

            /*增量式PID计算*/
            M3508s[i].outCurrent = Incremental_PID(&M3508s[i].pid, M3508s[i].targetSpeed, M3508s[i].realSpeed);
            //清除标志位
            M3508s[i].infoUpdateFlag = 0;
        }
    }

    if(Chassis.Power_OverflowFlag)
    {
        Chassis_powerLimit(M3508s, 3000.0f);
    }


    //设定电机电流值，需要经过裁判系统的计算之后才可以输出对应的电机值
    //对电机进行了所有的处理之后再进行赋值
    if(!Classical_ban)
    {
        M3508_setCurrent(M3508s[0].outCurrent, M3508s[1].outCurrent, M3508s[2].outCurrent, M3508s[3].outCurrent);
    }


}


/**
  * @brief  麦克纳姆轮速度解算
  * @param[in]  Vx		x轴速度
  *							Vy		y轴速度
  *							VOmega	自转速度
  * @param[out]	Speed	速度（定义一个结构数组让他的输出到这个数组里面）
  * @retval None
  */
void MecanumCalculation(float Vx, float Vy, float VOmega, int16_t *Speed)
{
    /*定义用于储存的结构体*/
    float tempSpeed[4];
    float Param = 1;
    float MaxSpeed = 0;

    /*速度限制*/
    VAL_LIMIT(Vx, -Chassis_MaxSpeed_X, Chassis_MaxSpeed_X);
    VAL_LIMIT(Vy, -Chassis_MaxSpeed_Y, Chassis_MaxSpeed_Y);
    VAL_LIMIT(VOmega, -Chassis_MaxSpeed_W, Chassis_MaxSpeed_W);

    /*四轮速度分解*/
    /*先要知道四个轮子的位置进行轮子建模*/
    /*轮子的位置在Readme里面自己去看*/
    /*通过模拟Vx，Vy，VOmega的量来对他进行判断*/
    /*实际上就是通过分解合力把速度分别分配在四个轮子上面*/
    /*最好用前进时候的模型为例子，直接看轮子的小轮朝向来判断出对应的力*/
    /*画出模型之后就可以模拟方向了*/
    tempSpeed[0] = Vx - Vy + VOmega;
    tempSpeed[1] = Vx + Vy + VOmega;
    tempSpeed[2] = -Vx + Vy + VOmega;
    tempSpeed[3] = -Vx - Vy + VOmega;


    /*计算出四个轮子中的最大速度*/
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

void Chassis_powerLimit(M3508s_t *p_M3508s, float CurrentLimit)
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
