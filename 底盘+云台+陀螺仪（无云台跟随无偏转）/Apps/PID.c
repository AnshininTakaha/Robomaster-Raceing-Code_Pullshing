/**
  ******************************************************************************
  * @file    PID.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   PID���ݴ���
  ******************************************************************************
  */

#include "PID.h"

/*����˳��*/
void abs_limit(float *a, float ABS_MAX);



/**
  * @brief  ����ʽPID����
  * @param[in]	target Ŀ��ֵ
	*						  measured ʵ��ֵ
  *			
	* @param[out] *pid_t PIDһ�����ݽṹ��
  * @retval None
  */
/*����ʽPID���㺯��*/
int Incremental_PID(incrementalpid_t *pid_t, float target, float measured) 
{
	/*����p,i,d�Ĵ����*/
	float p_out, i_out, d_out;
	
	/*Ŀ���ٶ�*/
	pid_t->Target = target;
	
	/*Ŀǰ���ٶ�*/
	pid_t->Measured = measured;
	
	/*��ֵ*/
	pid_t->err = pid_t->Target - pid_t->Measured;
	
	/*�����ֵ���󣬿���ֱ�Ӻ��Բ�ֵ����������һ���̶��ϵı�֤�ٶȵ��ȶ���*/
	if(abs(pid_t->err)<0.2f)
		pid_t->err = 0.0f;
		//return 0;
	
	/*PID��ֵ�н�ֵ���㣨�ǳ�ʼֵ��*/
	/*void PID_paramInit(void)Ϊ����ֵ��������main�����ж���*/
	p_out = pid_t->Kp*(pid_t->err - pid_t->err_last);//Kp��һ���˻������ԣ���һ�εĲ�ֵ��ȥ��һ�εĲ�ֵ��
	i_out = pid_t->Ki*pid_t->err;//Ki��һ���˻���������һ�εĲ�ֵ
	d_out = pid_t->Kd*(pid_t->err - 2*pid_t->err_last + pid_t->err_beforeLast);//Kd���ԣ���ε�ƫ������������ϴε�ƫ���ȥ���ϴε�ƫ�
	
	//�����޷�
	abs_limit(&i_out, pid_t->IntegralLimit);
	
	/*��������ֵ�ó���һ��PWM��ֵ*/
	pid_t->pwm += (p_out + i_out + d_out);
	
	//����޷�
	abs_limit(&pid_t->pwm, pid_t->MaxOutput);
	
	//���ݵݽ�
	pid_t->err_beforeLast = pid_t->err_last;
	pid_t->err_last = pid_t->err;
	
	/*ת����Ϊint��*/
	return (int)pid_t->pwm;
}

/**
  * @brief  �����޷�
  * @param[in]	*a ��Ӧ��iֵ
	*						  ABS_MAX ��Ӧ��������ֵ
  *			
	* @param[out] *pid_t PIDһ�����ݽṹ��
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
  * @brief  ����ʽPID��ʼ��ֵ
  * @param[in]	kp ��Ӧ��Pֵ
								ki ��Ӧ��Iֵ
								kd ��Ӧ��Dֵ
								MaxOutput �������ֵ���޷����ã�
								IntegralLimit ���Ļ���ֵ���޷���
	* @param[out] *pid_t PIDһ�����ݽṹ��
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
  * @brief  λ��ʽPID��ʼ��ֵ
  * @param[in]	kp ��Ӧ��Pֵ
								ki ��Ӧ��Iֵ
								kd ��Ӧ��Dֵ
								MaxOutput �������ֵ���޷����ã�
								IntegralLimit ���Ļ���ֵ���޷���
	* @param[out] *pid_t PIDһ�����ݽṹ��
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
  * @brief  λ��ʽPID����
  * @param[in]	kp ��Ӧ��Pֵ
								ki ��Ӧ��Iֵ
								kd ��Ӧ��Dֵ
								MaxOutput �������ֵ���޷����ã�
								IntegralLimit ���Ļ���ֵ���޷���
	* @param[out] *pid_t PIDһ�����ݽṹ��
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
	
	//�����޷�
	abs_limit(&i_out, pid_t->IntegralLimit);
	
	pid_t->pwm = (p_out + i_out + d_out);
	
	//����޷�
	abs_limit(&pid_t->pwm, pid_t->MaxOutput);
	
	pid_t->err_last = pid_t->err;
	
    
	
	return (int)pid_t->pwm;
}




