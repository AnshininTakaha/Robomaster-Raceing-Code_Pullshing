#include "PID.h"
/**
* @name IncrementalPID_Init
* @brief 初始化增量式PID
* @param [out] incrementalpid_t *pid 使用的增量式的PID
*        [in] float kp Kp的值
         [in] float ki Ki的值
         [in] float kd Kd的值
* @retval       必要说明
*/
void IncrementalPID_Init(incrementalpid_t *pid, float kp, float ki, float kd, uint32_t MaxOutput, uint32_t IntegralLimit)
{
    pid->Target_speed = 0;
    pid->Measured_speed = 0;
    pid->error = 0;
    pid->last_error = 0;
    pid->beforelast_error = 0;
    pid->Kp = kp;
    pid->Ki = ki;
    pid->Kd = kd;
    pid->MaxOutput = MaxOutput;
    pid->IntegralLimit = IntegralLimit;
    pid->PWM = 0;
}
/**
* @name 位置式PID初始化
* @brief 初始化位置式PID
* @param [out] positionpid_t *pid 使用的位置式PID
*        [in] float kp Kp的值
*        [in] float ki Ki的值
*        [in] float kd Kd的值
* @retval 
*/
void PositionPID_Init(positionpid_t *pid, float kp, float ki, float kd, uint32_t MaxOutput, uint32_t IntegralLimit)
{
    pid->Target = 0;
    pid->Measured = 0;
    pid->error = 0;
    pid->last_error = 0;
    pid->Kp = kp;
    pid->Ki = ki;
    pid->Kd = kd;
    pid->MaxOutput = MaxOutput;
    pid->IntegralLimit = IntegralLimit;
    pid->PWM = 0;
}

/**
* @name IncrementalPID_Calculation
* @brief 增量式PID计算
* @param [in] incrementalpid_t *pid 使用的PID的相关数据
*        [in] float target 目标值
         [in] float measured 测量值
* @retval 
*/
int IncrementalPID_Calculation(incrementalpid_t *pid, float target, float measured)
{
    float kp_output,ki_output,kd_output;
    float data_u,data_out,data_lastout;
    pid->Target_speed = target;
    pid->Measured_speed = measured;

    pid->error = pid->Target_speed - pid->Measured_speed;

    /*消除抖动*/
    if(abs_Calculation(pid->error) < 0.2f )
    {
        pid->error = 0.0f;
    }

    /*PID公式*/
    kp_output = pid->Kp * (pid->error - pid->last_error);
    ki_output = pid->Ki * (pid->error);
    kd_output = pid->Kd * (pid->error - 2*pid->last_error + pid->beforelast_error);


    /*Ki限幅*/
    Ki_Limiting(&ki_output,pid->IntegralLimit);

    /*Data累加*/
    pid->data_u = (kp_output + ki_output + kd_output);
    pid->data_out = pid->data_lastout + pid->data_u;

    pid->PWM = pid->data_out;
    pid->data_lastout = pid->data_out;

    /*输出限幅*/
    Output_Limting(&pid->PWM,pid->MaxOutput);

    /*递进*/
    pid->beforelast_error = pid->last_error;
    pid->last_error = pid->error;

    return pid->PWM;

}



/**
* @name PositionPID_Calculation
* @brief 位置式PID计算
* @param [in] positionpid_t *pid 位置式PID相对应数值
*        [in] float target 目标值
*        [in] float measured 测量值
* @retval       必要说明
*/
int PositionPID_Calculation(positionpid_t *pid, float target, float measured)
{
    float kp_output,ki_output,kd_output;

    pid->Target = (float)target;
    pid->Measured = (float)measured;
    pid->error = pid->Target - pid->Measured;


    /*积分分离*/
	if(abs(pid->error) < 20)
	{
		pid->Add_error += pid->error;
	}
    
    /*消除抖动*/
    if(abs_Calculation(pid->error) < 0.5f )
    {
        pid->error = 0.0f;
    }

    /*位置式PID计算公式*/
    kp_output = pid->Kp * pid->error;
    ki_output = pid->Ki * pid->Add_error;
    kd_output = pid->Kd * (pid->error - pid->last_error);

    /*Ki限幅*/
    Ki_Limiting(&ki_output,pid->IntegralLimit);

    pid->PWM = (kp_output + ki_output + kd_output);

    /*输出限幅*/
    Output_Limting(&pid->PWM,pid->MaxOutput);

    pid->last_error = pid ->error;

    return pid->PWM;
}