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



int FuzzyPID_PosCalculation(positionpid_t *pid,float target, float measured)
{
    float kp_output,ki_output,kd_output;

    pid->Target = (float)target;
    pid->Measured = (float)measured;
    pid->error = pid->Target - pid->Measured;
    pid->ec_error = pid->error - pid->last_error;
    /*ģ���Ƶ�*/
    pid->Kp = fuzzy_kp(pid->error,pid->ec_error);
    pid->Ki = fuzzy_ki(pid->error,pid->ec_error);
    pid->Kd = fuzzy_kd(pid->error,pid->ec_error);

    if(abs(pid->error) < 20)
	{
		pid->Add_error += pid->error;
	}
    
    /*��������*/
    if(abs_Calculation(pid->error) < 0.5f )
    {
        pid->error = 0.0f;
    }

    kp_output = pid->Kp * pid->error;
    ki_output = pid->Ki * pid->Add_error;
    kd_output = pid->Kd * pid->ec_error;
    
    Ki_Limiting(&ki_output,pid->IntegralLimit);

    pid->PWM = (kp_output + ki_output + kd_output);

    /*����޷�*/
    Output_Limting(&pid->PWM,pid->MaxOutput);

    pid->last_error = pid ->error;

    return pid->PWM;
}

int FuzzyPID_IncCalculation(incrementalpid_t *pid,float target, float measured)
{
    float kp_output,ki_output,kd_output;

    pid->Target_speed = (float)target;
    pid->Measured_speed = (float)measured;
    pid->error = pid->Target_speed - pid->Measured_speed;
    pid->ec_error = pid->error - pid->last_error;
    /*ģ���Ƶ�*/
    pid->Kp = fuzzy_kp(pid->error,pid->ec_error);
    pid->Ki = fuzzy_ki(pid->error,pid->ec_error);
    pid->Kd = fuzzy_kd(pid->error,pid->ec_error);
    
    /*��������*/
    if(abs_Calculation(pid->error) < 0.5f )
    {
        pid->error = 0.0f;
    }

    kp_output = pid->Kp * (pid->ec_error);
    ki_output = pid->Ki * (pid->error);
    kd_output = pid->Kd * (pid->error - 2*pid->last_error + pid->beforelast_error);
    
    Ki_Limiting(&ki_output,pid->IntegralLimit);

    pid->PWM = (kp_output + ki_output + kd_output);

    /*����޷�*/
    Output_Limting(&pid->PWM,pid->MaxOutput);

    pid->last_error = pid ->error;

    return pid->PWM;
}


float fuzzy_kp(float e, float ec) //e,ec����ʾ�����仯�� 
{ 
    /*����Kp�ļ���ֵ*/
    float Kp_calcu;

    /*����һ����ȡģ�����������ִ���num��e�������̶ȣ�ec�������̶�*/
    unsigned char  num,pe,pec; 

    /*e����ģ�����򣬿�ͨ����ʵ����������е��������ݵ����ʵ����*/
    float eRule[7]={-80.0,-50.0,-20.0,0.0,20.0,50.0,80.0};

    /*ec���仯�ʵ�ģ�����򣬿���ͨ����ʵ�����仯�������е��������ݵ����ʵ����*/
    float ecRule[7]={-7.0,-5.0,-3.0,0.0,3.0,5.0,7.0};

    /*Kp ��ģ���Ӽ�*/
    float kpRule[4]={0.486,0.648,0.729,0.7873}; 

    float eFuzzy[2]={0.0,0.0};//��������� E �������̶�
    float ecFuzzy[2]={0.0,0.0}; //���������仯�� EC �������̶�
    float KpFuzzy[4]={0.0,0.0,0.0,0.0}; //������ Kp �������̶�

    /*Kp��ģ�������*/
    int KpRule[7][7]= 
    {
        3,3,3,3,3,3,3, 
        2,2,2,2,1,2,2, 
        1,1,1,1,1,1,1, 
        1,1,0,1,0,1,1, 
        0,0,1,0,0,1,0, 
        0,1,0,1,0,0,2, 
        3,3,3,3,3,3,3 
    };

    /***** ��� E ������������ *****/ 
    /*��������һ�ߵ������̶ȵ�ģ��ֵ����ȷ����ֵ��Ӧ������*/
    if(e<eRule[0]) 
    { 
        eFuzzy[0] =1.0; pe = 0; 
    } 
    else if(eRule[0]<=e && e<eRule[1]) 
    { 
        eFuzzy[0] = (eRule[1]-e)/(eRule[1]-eRule[0]); pe = 0; 
    } 
    else if(eRule[1]<=e && e<eRule[2]) 
    { 
        eFuzzy[0] = (eRule[2] -e)/(eRule[2]-eRule[1]); pe = 1; 
    } 
    else if(eRule[2]<=e && e<eRule[3]) 
    {   
        eFuzzy[0] = (eRule[3] -e)/(eRule[3]-eRule[2]); pe = 2;
    } 
    else if(eRule[3]<=e && e<eRule[4]) 
    { 
        eFuzzy[0] = (eRule[4]-e)/(eRule[4]-eRule[3]); pe = 3; 
    } 
    else if(eRule[4]<=e && e<eRule[5]) 
    { 
        eFuzzy[0] = (eRule[5]-e)/(eRule[5]-eRule[4]); pe = 4; 
    } 
    else if(eRule[5]<=e && e<eRule[6]) 
    { 
        eFuzzy[0] = (eRule[6]-e)/(eRule[6]-eRule[5]); pe = 5; 
    } 
    else 
    { 
        eFuzzy[0] =0.0; pe =5; 
    } 

    /*�������һ�ߵ������̶Ⱥ����ͨ����Ӧ��ϵ�������һ�ߵ������̶�*/
    eFuzzy[1] =1.0 - eFuzzy[0]; 

    /*ͬ�����ec�������̶ȣ���ȷ����ֵ��Ӧ������*/
    if(ec<ecRule[0])  
    { 
        ecFuzzy[0] =1.0; pec = 0; 
    } 
    else if(ecRule[0]<=ec && ec<ecRule[1]) 
    { 
        ecFuzzy[0] = (ecRule[1] - ec)/(ecRule[1]-ecRule[0]); pec = 0 ; 
    } 
    else if(ecRule[1]<=ec && ec<ecRule[2]) 
    { 
        ecFuzzy[0] = (ecRule[2] - ec)/(ecRule[2]-ecRule[1]); pec = 1; 
    } 
    else if(ecRule[2]<=ec && ec<ecRule[3]) 
    { 
        ecFuzzy[0] = (ecRule[3] - ec)/(ecRule[3]-ecRule[2]); pec = 2 ; 
    } 
    else if(ecRule[3]<=ec && ec<ecRule[4]) 
    { 
        ecFuzzy[0] = (ecRule[4]-ec)/(ecRule[4]-ecRule[3]); pec=3; 
    } 
    else if(ecRule[4]<=ec && ec<ecRule[5]) 
    { 
        ecFuzzy[0] = (ecRule[5]-ec)/(ecRule[5]-ecRule[4]); pec=4; 
    } 
    else if(ecRule[5]<=ec && ec<ecRule[6]) 
    { 
        ecFuzzy[0] = (ecRule[6]-ec)/(ecRule[6]-ecRule[5]); pec=5; 
    } 
    else 
    { 
        ecFuzzy[0] =0.0; pec = 5; 
    } 
    
    /*�������һ�ߵ������̶Ⱥ����ͨ����Ӧ��ϵ�������һ�ߵ������̶�*/
    ecFuzzy[1] = 1.0 - ecFuzzy[0];

    /********* ��ѯģ������� *********/ 
    /*���ݶ���Ĺ��������ĸ�ֵ*/
    num =KpRule[pe][pec]; 
    KpFuzzy[num] += eFuzzy[0]*ecFuzzy[0]; 
    num =KpRule[pe][pec+1]; 
    KpFuzzy[num] += eFuzzy[0]*ecFuzzy[1]; 
    num =KpRule[pe+1][pec]; 
    KpFuzzy[num] += eFuzzy[1]*ecFuzzy[0]; 
    num =KpRule[pe+1][pec+1]; 
    KpFuzzy[num] += eFuzzy[1]*ecFuzzy[1]; 

    /*��Ȩƽ��������ģ��PID*/
    Kp_calcu=KpFuzzy[0]*kpRule[0]+KpFuzzy[1]*kpRule[1]+KpFuzzy[2]*kpRule[2] +KpFuzzy[3]*kpRule[3]; 

    return(Kp_calcu);
}

float fuzzy_ki(float e, float ec) 
{ 
    float Ki_calcu; 
    unsigned char num,pe,pec; 

    float eRule[7]={-120.0,-80.0,-40.0,0.0,40.0,80.0,120.0};

    float ecRule[7]={-7.0,-5.0,-3.0,0.0,3.0,5.0,7.0};

    float kiRule[4]={0.0,0.0,0.0,0.0}; 

    float eFuzzy[2]={0.0,0.0}; 
    float ecFuzzy[2]={0.0,0.0}; 
    
    float KiFuzzy[4]={0.0,0.0,0.0,0.0}; 
    int KiRule[7][7]= 
    { 
        0,0,0,0,0,0,0, 
        0,0,0,0,0,0,0, 
        0,0,0,0,0,0,0, 
        0,0,0,0,0,0,0, 
        0,0,0,0,0,0,0, 
        2,0,0,0,0,0,1, 
        3,3,3,3,3,3,3 
    }; 
        /***** ��������������� *****/ 
        if(e<eRule[0]) 
        { 
            eFuzzy[0] =1.0; pe = 0; 
        } 
        else if(eRule[0]<=e && e<eRule[1]) 
        { 
            eFuzzy[0] = (eRule[1]-e)/(eRule[1]-eRule[0]); pe = 0; 
        } 
        else if(eRule[1]<=e && e<eRule[2]) 
        { 
            eFuzzy[0] = (eRule[2] -e)/(eRule[2]-eRule[1]); pe = 1; 
        } 
        else if(eRule[2]<=e && e<eRule[3]) 
        { 
            eFuzzy[0] = (eRule[3] -e)/(eRule[3]-eRule[2]); pe = 2; 
        } 
        else if(eRule[3]<=e && e<eRule[4]) 
        { 
            eFuzzy[0] = (eRule[4]-e)/(eRule[4]-eRule[3]); pe = 3; 
        } 
        else if(eRule[4]<=e && e<eRule[5]) 
        { 
            eFuzzy[0] = (eRule[5]-e)/(eRule[5]-eRule[4]); pe = 4; 
        } 
        else if(eRule[5]<=e && e<eRule[6]) 
        { 
            eFuzzy[0] = (eRule[6]-e)/(eRule[6]-eRule[5]); pe = 5; 
        } 
        else 
        { 
            eFuzzy[0] =0.0; pe =5; 
        } 
        eFuzzy[1] =1.0 - eFuzzy[0]; 
        
        /***** ���仯������������ *****/  
        if(ec<ecRule[0])  
        { 
            ecFuzzy[0] =1.0; pec = 0; 
        } 
        else if(ecRule[0]<=ec && ec<ecRule[1])
        { 
            ecFuzzy[0] = (ecRule[1] - ec)/(ecRule[1]-ecRule[0]); pec = 0 ; 
        } 
        else if(ecRule[1]<=ec && ec<ecRule[2]) 
        { 
            ecFuzzy[0] = (ecRule[2] - ec)/(ecRule[2]-ecRule[1]); pec = 1; 
        } 
        else if(ecRule[2]<=ec && ec<ecRule[3]) 
        { 
            ecFuzzy[0] = (ecRule[3] - ec)/(ecRule[3]-ecRule[2]); pec = 2 ; 
        } 
        else if(ecRule[3]<=ec && ec<ecRule[4]) 
        { 
            ecFuzzy[0] = (ecRule[4]-ec)/(ecRule[4]-ecRule[3]); pec=3; 
        } 
        else if(ecRule[4]<=ec && ec<ecRule[5]) 
        { 
            ecFuzzy[0] = (ecRule[5]-ec)/(ecRule[5]-ecRule[4]); pec=4; 
        } 
        else if(ecRule[5]<=ec && ec<ecRule[6]) 
        { 
            ecFuzzy[0] = (ecRule[6]-ec)/(ecRule[6]-ecRule[5]); pec=5; 
        } 
        else 
        { 
            ecFuzzy[0] =0.0; pec = 5; 
        } 
        ecFuzzy[1] = 1.0 - ecFuzzy[0]; 
        /*********** ��ѯģ������� ***************/ 
        num =KiRule[pe][pec]; 
        KiFuzzy[num] += eFuzzy[0]*ecFuzzy[0]; 
        num =KiRule[pe][pec+1]; 
        KiFuzzy[num] += eFuzzy[0]*ecFuzzy[1]; 
        num =KiRule[pe+1][pec]; 
        KiFuzzy[num] += eFuzzy[1]*ecFuzzy[0]; 
        num =KiRule[pe+1][pec+1]; 
        KiFuzzy[num] += eFuzzy[1]*ecFuzzy[1]; 
        /******** �� Ȩ ƽ �� �� �� ģ �� ********/ 
        Ki_calcu=KiFuzzy[0]*kiRule[0]+KiFuzzy[1]*kiRule[1]+KiFuzzy[2]*kiRule[2] +KiFuzzy[3]*kiRule[3]; 
        return(Ki_calcu); 
} 



float fuzzy_kd(float e, float ec) 
{ 
    float Kd_calcu; 
    unsigned char num,pe,pec; 
    float eRule[7]={-80.0,-40.0,-20.0,0.0,20.0,40.0,80.0};

    float ecRule[7]={-7.0,-5.0,-3.0,0.0,3.0,5.0,7.0};

    float kdRule[4]={1.1289,1.101,1.4862,1.6035}; 
    
    float eFuzzy[2]={0.0,0.0}; 
    float ecFuzzy[2]={0.0,0.0}; 

    
    float KdFuzzy[4]={0.0,0.0,0.0,0.0}; 
    int KdRule[7][7]= 
    { 
        3,3,3,2,2,2,2, 
        2,2,2,1,1,1,1, 
        1,1,2,1,1,2,1, 
        1,1,0,1,0,1,1, 
        1,1,0,0,0,1,1, 
        2,2,1,0,1,1,1, 
        3,3,3,3,2,3,2  
    }; 
            /***** ��������������� *****/ 
    if(e<eRule[0]) 
    { 
        eFuzzy[0] =1.0; pe = 0; 
    } 
    else if(eRule[0]<=e && e<eRule[1]) 
    { 
        eFuzzy[0] = (eRule[1]-e)/(eRule[1]-eRule[0]); pe = 0; 
    } 
    else if(eRule[1]<=e && e<eRule[2]) 
    { 
        eFuzzy[0] = (eRule[2] -e)/(eRule[2]-eRule[1]); pe = 1; 
    } 
    else if(eRule[2]<=e && e<eRule[3]) 
    { 
        eFuzzy[0] = (eRule[3] -e)/(eRule[3]-eRule[2]); pe = 2; 
    } 
    else if(eRule[3]<=e && e<eRule[4]) 
    { 
        eFuzzy[0] = (eRule[4]-e)/(eRule[4]-eRule[3]); pe = 3; 
    } 
    else if(eRule[4]<=e && e<eRule[5]) 
    { 
        eFuzzy[0] = (eRule[5]-e)/(eRule[5]-eRule[4]); pe = 4; 
    } 
    else if(eRule[5]<=e && e<eRule[6]) 
    { 
        eFuzzy[0] = (eRule[6]-e)/(eRule[6]-eRule[5]); pe = 5; 
    } 
    else 
    { 
         eFuzzy[0] =0.0; pe =5; 
    } 
    eFuzzy[1] =1.0 - eFuzzy[0]; 
    /***** ���仯������������ *****/  
    if(ec<ecRule[0])  
    { 
        ecFuzzy[0] =1.0; pec = 0; 
    } 
    else if(ecRule[0]<=ec && ec<ecRule[1]) 
    { 
        ecFuzzy[0] = (ecRule[1] - ec)/(ecRule[1]-ecRule[0]); pec = 0 ; 
    } 
    else if(ecRule[1]<=ec && ec<ecRule[2]) 
    { 
        ecFuzzy[0] = (ecRule[2] - ec)/(ecRule[2]-ecRule[1]); pec = 1; 
    } 
    else if(ecRule[2]<=ec && ec<ecRule[3]) 
    { 
        ecFuzzy[0] = (ecRule[3] - ec)/(ecRule[3]-ecRule[2]); pec = 2 ; 
    } 
    else if(ecRule[3]<=ec && ec<ecRule[4]) 
    { 
        ecFuzzy[0] = (ecRule[4]-ec)/(ecRule[4]-ecRule[3]); pec=3; 
    } 
    else if(ecRule[4]<=ec && ec<ecRule[5]) 
    { 
        ecFuzzy[0] = (ecRule[5]-ec)/(ecRule[5]-ecRule[4]); pec=4; 
    } 
    else if(ecRule[5]<=ec && ec<ecRule[6]) 
    { 
        ecFuzzy[0] = (ecRule[6]-ec)/(ecRule[6]-ecRule[5]); pec=5; 
    } 
    else 
    { 
        ecFuzzy[0] =0.0; pec = 5; 
    } 
    ecFuzzy[1] = 1.0 - ecFuzzy[0];
     /*********** ��ѯģ������� *************/ 
    num =KdRule[pe][pec]; 
    KdFuzzy[num] += eFuzzy[0]*ecFuzzy[0]; 
    num =KdRule[pe][pec+1]; 
    KdFuzzy[num] += eFuzzy[0]*ecFuzzy[1]; 
    num =KdRule[pe+1][pec]; 
    KdFuzzy[num] += eFuzzy[1]*ecFuzzy[0]; 
    num =KdRule[pe+1][pec+1]; 
    KdFuzzy[num] += eFuzzy[1]*ecFuzzy[1]; 
    /******** ��Ȩƽ������ģ�� ********/ 
    Kd_calcu=KdFuzzy[0]*kdRule[0]+KdFuzzy[1]*kdRule[1]+KdFuzzy[2]*kdRule[2] +KdFuzzy[3]*kdRule[3]; 
    return(Kd_calcu); 
} 