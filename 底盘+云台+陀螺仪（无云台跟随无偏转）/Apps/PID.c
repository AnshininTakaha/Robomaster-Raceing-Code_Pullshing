/**
  ******************************************************************************
  * @file    PID.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   PID数据处理
  ******************************************************************************
  */

#include "PID.h"

/*调整顺序*/
void abs_limit(float *a, float ABS_MAX);



/**
  * @brief  增量式PID计算
  * @param[in]	target 目标值
	*						  measured 实际值
  *			
	* @param[out] *pid_t PID一套数据结构体
  * @retval None
  */
/*增量式PID计算函数*/
int Incremental_PID(incrementalpid_t *pid_t, float target, float measured) 
{
	/*定义p,i,d的储存点*/
	float p_out, i_out, d_out;
	
	/*目标速度*/
	pid_t->Target = target;
	
	/*目前的速度*/
	pid_t->Measured = measured;
	
	/*差值*/
	pid_t->err = pid_t->Target - pid_t->Measured;
	
	/*如果差值不大，可以直接忽略差值，这样可以一定程度上的保证速度的稳定性*/
	if(abs(pid_t->err)<0.2f)
		pid_t->err = 0.0f;
		//return 0;
	
	/*PID数值承接值计算（非初始值）*/
	/*void PID_paramInit(void)为赋初值函数，在main里面有定义*/
	p_out = pid_t->Kp*(pid_t->err - pid_t->err_last);//Kp是一个乘积，乘以（这一次的差值减去上一次的差值）
	i_out = pid_t->Ki*pid_t->err;//Ki是一个乘积，乘以这一次的差值
	d_out = pid_t->Kd*(pid_t->err - 2*pid_t->err_last + pid_t->err_beforeLast);//Kd乘以（这次的偏差加上两倍的上次的偏差减去上上次的偏差）
	
	//积分限幅
	abs_limit(&i_out, pid_t->IntegralLimit);
	
	/*这三个的值得出下一个PWM的值*/
	pid_t->pwm += (p_out + i_out + d_out);
	
	//输出限幅
	abs_limit(&pid_t->pwm, pid_t->MaxOutput);
	
	//数据递进
	pid_t->err_beforeLast = pid_t->err_last;
	pid_t->err_last = pid_t->err;
	
	/*转换成为int型*/
	return (int)pid_t->pwm;
}

/**
  * @brief  积分限幅
  * @param[in]	*a 对应的i值
	*						  ABS_MAX 对应的最大积分值
  *			
	* @param[out] *pid_t PID一套数据结构体
  * @retval None
  */
void abs_limit(float *a, float ABS_MAX)
{
    if(*a > ABS_MAX)
        *a = ABS_MAX;
    if(*a < -ABS_MAX)
        *a = -ABS_MAX;
}

/**
  * @brief  增量式PID初始赋值
  * @param[in]	kp 对应的P值
								ki 对应的I值
								kd 对应的D值
								MaxOutput 最大的输出值（限幅作用）
								IntegralLimit 最大的积分值（限幅）
	* @param[out] *pid_t PID一套数据结构体
  * @retval None
  */


void IncrementalPID_paraReset(incrementalpid_t *pid_t, float kp, float ki, float kd, uint32_t MaxOutput, uint32_t IntegralLimit)
{
	pid_t->Target = 0;
	pid_t->Measured = 0;
	pid_t->err = 0;
	pid_t->err_last = 0;
	pid_t->err_beforeLast = 0;
	pid_t->Kp = kp;
	pid_t->Ki = ki;
	pid_t->Kd = kd;
	pid_t->MaxOutput = MaxOutput;
	pid_t->IntegralLimit = IntegralLimit;
	pid_t->pwm = 0; 			
}

/**
  * @brief  位置式PID初始赋值
  * @param[in]	kp 对应的P值
								ki 对应的I值
								kd 对应的D值
								MaxOutput 最大的输出值（限幅作用）
								IntegralLimit 最大的积分值（限幅）
	* @param[out] *pid_t PID一套数据结构体
  * @retval None
  */
void PositionPID_paraReset(positionpid_t *pid_t, float kp, float ki, float kd, uint32_t MaxOutput, uint32_t IntegralLimit)
{
	pid_t->Target = 0;
	pid_t->Measured = 0;
	pid_t->MaxOutput = MaxOutput;
	pid_t->IntegralLimit = IntegralLimit;
	pid_t->err = 0;
	pid_t->err_last = 0;
	pid_t->integral_err = 0;
	pid_t->Kp = kp;
	pid_t->Ki = ki;
	pid_t->Kd = kd;
	pid_t->pwm = 0; 			
}

/**
  * @brief  位置式PID计算
  * @param[in]	kp 对应的P值
								ki 对应的I值
								kd 对应的D值
								MaxOutput 最大的输出值（限幅作用）
								IntegralLimit 最大的积分值（限幅）
	* @param[out] *pid_t PID一套数据结构体
  * @retval None
  */
int Position_PID(positionpid_t *pid_t, float target, float measured) 
{
	float p_out, i_out, d_out;
	pid_t->Target = (float)target;
	pid_t->Measured = (float)measured;
	pid_t->err = pid_t->Target - pid_t->Measured;
	
	if(abs(pid_t->err)<0.2f)
		pid_t->err = 0.0f;
		//return 0;
	
	pid_t->integral_err += pid_t->err;
	
	p_out = pid_t->Kp*pid_t->err;
	i_out = pid_t->Ki*pid_t->integral_err;
	d_out = pid_t->Kd*(pid_t->err - pid_t->err_last);
	
	//积分限幅
	abs_limit(&i_out, pid_t->IntegralLimit);
	
	pid_t->pwm = (p_out + i_out + d_out);
	
	//输出限幅
	abs_limit(&pid_t->pwm, pid_t->MaxOutput);
	
	pid_t->err_last = pid_t->err;
	
    
	
	return (int)pid_t->pwm;
}




