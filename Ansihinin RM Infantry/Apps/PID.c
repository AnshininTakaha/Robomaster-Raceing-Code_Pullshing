#include "PID.h"
/**
* @name IncrementalPID_Init
* @brief ��ʼ������ʽPID
* @param [out] incrementalpid_t *pid ʹ�õ�����ʽ��PID
*        [in] float kp Kp��ֵ
         [in] float ki Ki��ֵ
         [in] float kd Kd��ֵ
* @retval       ��Ҫ˵��
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
* @name λ��ʽPID��ʼ��
* @brief ��ʼ��λ��ʽPID
* @param [out] positionpid_t *pid ʹ�õ�λ��ʽPID
*        [in] float kp Kp��ֵ
*        [in] float ki Ki��ֵ
*        [in] float kd Kd��ֵ
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
* @brief ����ʽPID����
* @param [in] incrementalpid_t *pid ʹ�õ�PID���������
*        [in] float target Ŀ��ֵ
         [in] float measured ����ֵ
* @retval 
*/
int IncrementalPID_Calculation(incrementalpid_t *pid, float target, float measured)
{
    float kp_output,ki_output,kd_output;
    float data_u,data_out,data_lastout;
    pid->Target_speed = target;
    pid->Measured_speed = measured;

    pid->error = pid->Target_speed - pid->Measured_speed;

    /*��������*/
    if(abs_Calculation(pid->error) < 0.2f )
    {
        pid->error = 0.0f;
    }

    /*PID��ʽ*/
    kp_output = pid->Kp * (pid->error - pid->last_error);
    ki_output = pid->Ki * (pid->error);
    kd_output = pid->Kd * (pid->error - 2*pid->last_error + pid->beforelast_error);


    /*Ki�޷�*/
    Ki_Limiting(&ki_output,pid->IntegralLimit);

    /*Data�ۼ�*/
    pid->data_u = (kp_output + ki_output + kd_output);
    pid->data_out = pid->data_lastout + pid->data_u;

    pid->PWM = pid->data_out;
    pid->data_lastout = pid->data_out;

    /*����޷�*/
    Output_Limting(&pid->PWM,pid->MaxOutput);

    /*�ݽ�*/
    pid->beforelast_error = pid->last_error;
    pid->last_error = pid->error;

    return pid->PWM;

}



/**
* @name PositionPID_Calculation
* @brief λ��ʽPID����
* @param [in] positionpid_t *pid λ��ʽPID���Ӧ��ֵ
*        [in] float target Ŀ��ֵ
*        [in] float measured ����ֵ
* @retval       ��Ҫ˵��
*/
int PositionPID_Calculation(positionpid_t *pid, float target, float measured)
{
    float kp_output,ki_output,kd_output;

    pid->Target = (float)target;
    pid->Measured = (float)measured;
    pid->error = pid->Target - pid->Measured;


    /*���ַ���*/
	if(abs(pid->error) < 20)
	{
		pid->Add_error += pid->error;
	}
    
    /*��������*/
    if(abs_Calculation(pid->error) < 0.5f )
    {
        pid->error = 0.0f;
    }

    /*λ��ʽPID���㹫ʽ*/
    kp_output = pid->Kp * pid->error;
    ki_output = pid->Ki * pid->Add_error;
    kd_output = pid->Kd * (pid->error - pid->last_error);

    /*Ki�޷�*/
    Ki_Limiting(&ki_output,pid->IntegralLimit);

    pid->PWM = (kp_output + ki_output + kd_output);

    /*����޷�*/
    Output_Limting(&pid->PWM,pid->MaxOutput);

    pid->last_error = pid ->error;

    return pid->PWM;
}