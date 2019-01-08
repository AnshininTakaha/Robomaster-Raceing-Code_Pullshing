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
Chassis_t Chassis = {.LpfAttFactor = 0.098f};

/*调整代码写的顺序，方便你们看*/
void MecanumCalculation(float Vx, float Vy, float VOmega, int16_t *Speed);
void Chassis_powerLimit(M3508s_t *p_M3508s, float CurrentLimit);



void Chassis_Init(void)
{
	for(int i = 0; i < 4; i++)
	{
		IncrementalPID_paraReset(&M3508s[i].pid, 2.8f, 0.4f, 0.0f, 16000, 5000);
	}
}


/**
  * @brief  底盘控制处理
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
	
	//平滑处理，作用是挤掉在数据发送过程中多余的尖波
	/*滤波的值是自己设置的*/
	Filter_IIRLPF(&Vx, &Chassis.xLPF, Chassis.LpfAttFactor);
	Filter_IIRLPF(&Vy, &Chassis.yLPF, Chassis.LpfAttFactor);
	Filter_IIRLPF(&VOmega, &Chassis.zLPF, Chassis.LpfAttFactor);
	/*通过滤波操作之后算出的值继续进行处理*/
	
	
	int16_t speed[4];
	//麦轮解算公式，把平滑处理后的速度赋值给麦轮的解算公式
	//通过模型分解给对应的四个轮子赋值速度（因为是麦轮，和之前的速度分解是有点不同的）
	//分解之后计算最大速度和单轮的比值
	//把所有的轮子的速度乘以这个比值就是最终这四个轮子的速度
	MecanumCalculation(Chassis.xLPF, Chassis.yLPF, Chassis.zLPF, speed);
	
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
	
	//功率缓冲即将GG，也就是功率即将超过限制
//	if(Judge_PowerHeatData.data.chassisPowerBuffer < 20)
//	{
//		/*功率限制*/
//		Chassis_powerLimit(M3508s, 80000.0f/24.0f);
//	}
	
	
	//设定电机电流值，需要经过裁判系统的计算之后才可以输出对应的电机值
	//对电机进行了所有的处理之后再进行赋值
	M3508_setCurrent(M3508s[0].outCurrent, M3508s[1].outCurrent, M3508s[2].outCurrent, M3508s[3].outCurrent);
	
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
