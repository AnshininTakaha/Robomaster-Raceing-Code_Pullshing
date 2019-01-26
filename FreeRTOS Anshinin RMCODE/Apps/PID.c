
#include "PID.h"

/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    abs_Calculation
  * @brief   float myabs
  * @param   myabs 输入的�?
  * @author  口无
  * @Data    2018-10-30
 **/
/* -------------------------------- end -------------------------------- */
float abs_Calculation(float myabs)
{
    if(myabs >= 0)
    {
        myabs = myabs;
    }
    if(myabs < 0)
    {
        myabs = -myabs;
    }
    return myabs;
}


/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    Ki_Limiting
  * @brief   KI限幅
  * @param   KI_OUT: [输入
**			 		 MAXER: [输出]
  * @author  口无
  * @Data    2018-10-30
 **/
/* -------------------------------- end -------------------------------- */

void Ki_Limiting(float *KI_OUT,float MAXER)
{
    if(*KI_OUT > MAXER)
    {
        *KI_OUT = MAXER;
    }
    if(*KI_OUT < -MAXER)
    {
        *KI_OUT = -MAXER;
    }
}


/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    Output_Limting
  * @brief   输出限幅
  * @param   Output: [输入
**			 		 MAXER: [输出
  * @author  口无
  * @Data    2018-10-30
 **/
/* -------------------------------- end -------------------------------- */
void Output_Limting(float *Output, float MAXER)
{
    if(*Output > MAXER)
    {
        *Output = MAXER;
    }
    if(*Output < -MAXER)
    {
        *Output = -MAXER;
    }
}

/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    IncrementalPID_Init
  * @brief  ·增量式PID初�?�化
  * @param[out]   pid(st): pid的三�?�?
	* @param[in]		kp,ki,kd: 对应的三个pid的�?
		**			 			MaxOutput: 最大输出限�?
		**			 			IntegralLimit: �?分限�?
  * @author  口无
  * @Data    2018-10-30
 **/
/* -------------------------------- end -------------------------------- */

void IncrementalPID_Init(incrementalpid_st *pid, float kp, float ki, float kd, uint32_t MaxOutput, uint32_t IntegralLimit)
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


/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    PositionPID_Init
  * @brief   位置式PID初�?�化
  * @param[out]   pid(st): pid的三�?�?
  * @param[in]    kp,ki,kd: 三个对应的PID的�?
				 **			  MaxOutput: 最大输出限�?
				 **			  IntegralLimit: �?分限�?
  * @author  口无
  * @Data    2018-10-30
 **/
/* -------------------------------- end -------------------------------- */

void PositionPID_Init(positionpid_st *pid, float kp, float ki, float kd, uint32_t MaxOutput, uint32_t IntegralLimit)
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




/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    IncrementalPID_Calculation
  * @brief   增量式PID计算
  * @param[out]   pid(st): pid的三�?�?
  * @param[in]    target: �?标�?
				 **			  measured: 测量�?
  * @author  口无
  * @Data    2018-10-30
 **/
/* -------------------------------- end -------------------------------- */
int IncrementalPID_Calculation(incrementalpid_st *pid, float target, float measured)
{
    float kp_output,ki_output,kd_output;
    float data_u,data_out,data_lastout;
    pid->Target_speed = target;
    pid->Measured_speed = measured;

    pid->error = pid->Target_speed - pid->Measured_speed;
		
    /*抖动消除*/
    if(abs_Calculation(pid->error) < 0.2f )
    {
        pid->error = 0.0f;
    }

    /*增量式PID计算*/
    kp_output = pid->Kp * (pid->error - pid->last_error);
    ki_output = pid->Ki * (pid->error);
    kd_output = pid->Kd * (pid->error - 2*pid->last_error + pid->beforelast_error);


    /*�?分限�?*/
    Ki_Limiting(&ki_output,pid->IntegralLimit);

    /*输出PWM的值�?�算*/
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

/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    PositionPID_Calculation
  * @brief   位置式PID计算
  * @param[out]   pid(st): pid的三�?�?
  * @param[in]    target: �?标�?
				 **			  measured: 测量�?
  * @author  口无
  * @Data    2018-10-30
 **/
/* -------------------------------- end -------------------------------- */
float ec_error;

int PositionPID_Calculation(positionpid_st *pid, float target, float measured)
{
    float kp_output,ki_output,kd_output;
		

    pid->Target = (float)target;
    pid->Measured = (float)measured;
    pid->error = pid->Target - pid->Measured;
	
		ec_error = pid->error - pid->last_error;
	
		if(abs(pid->error) < 20)
		{
			pid->Add_error += pid->error;
		}
    /*抖动消除*/
    if(abs_Calculation(pid->error) < 0.5f )
    {
        pid->error = 0.0f;
    }

    

    /*位置式PID计算*/
    kp_output = pid->Kp * pid->error;
    ki_output = pid->Ki * pid->Add_error;
    kd_output = pid->Kd * (pid->error - pid->last_error);

    Ki_Limiting(&ki_output,pid->IntegralLimit);

    pid->PWM = (kp_output + ki_output + kd_output);

    Output_Limting(&pid->PWM,pid->MaxOutput);

    pid->last_error = pid ->error;

    return pid->PWM;
}
