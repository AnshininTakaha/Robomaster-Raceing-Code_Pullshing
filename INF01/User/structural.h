#ifndef __STURCTURE__
#define __STURCTURE__

#include "Users.h"

#pragma anon_unions

/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    incrementalpid_st
  * @brief   ����ʽPID
	* @param   Target_speed     Ŀ���ٶ�
						 Measured_speed   �����ٶ�
						 error            ��ǰƫ��ֵ����ֵ��
						 last_error       ��һ�ε�ƫ��ֵ����һ�β�ֵ��
						 beforelast_error ���ϴε�ƫ��ֵ�����ϴβ�ֵ��
						 Kp,Ki,Kd         ���ֶ�Ӧ��������
						 PWM              ����ó���PWM��ֵ
						 MaxOutput        �������޷�
						 IntegralLimit    �����޷�
						 
						 data_u           ���εó���PWMֵ
						 data_out         �������PWM��ֵ
						 data_lastout     ��һ�������PWM��ֵ
						 
  * @author  ���� 
  * @Data    2018-10-26
 **/
/* -------------------------------- end -------------------------------- */

typedef struct
{
	float Target_speed;       
	float Measured_speed;
	float error;
	float last_error;
	float beforelast_error;
	float Kp,Ki,Kd;
	float PWM;
	
	float data_u;
	float data_out;
	float data_lastout;
	
	uint32_t MaxOutput;
	uint32_t IntegralLimit;
	
}incrementalpid_st;



/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    positionpid_st
  * @brief   λ��ʽPID
	* @param   Target     Ŀ���ٶ�
						 Measured   �����ٶ�
						 error            ��ǰƫ��ֵ����ֵ��
						 last_error       ��һ�ε�ƫ��ֵ����һ�β�ֵ��
						 Add_error        �ۻ���ƫ��ֵ
						 Kp,Ki,Kd         ���ֶ�Ӧ��������
						 PWM              ����ó���PWM��ֵ
						 MaxOutput        �������޷�
						 IntegralLimit    �����޷�
  * @author  ���� 
  * @Data    2018-10-26
 **/
/* -------------------------------- end -------------------------------- */

typedef struct
{
	float Target;
	float Measured;
	float error;
	float last_error;
	float Add_error;
	float Kp,Ki,Kd;
	float PWM;
	uint32_t MaxOutput;
	uint32_t IntegralLimit;
}positionpid_st;



/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    RM3508_st
  * @brief   3508������ݴ���ṹ��
	* @param[in]  realAngle      ��ȡ��ʵ�ʽǶ�
							  realSpeed      ��ȡ��ʵ���ٶ�
							  realCurrent    ��ȡ��ʵ�ʵ���
							  realTempeture  ��ȡ��ʵ�ʵ��¶�

  * @param[out] pid_wheel(st)  �����ٶ�pid�ṹ��
								targetSpeed    ���ӵ�Ŀ���ٶ�
								targetAngle    ���ӵ�Ŀ��Ƕ�
								outCurrent     ����ĵ���
							
  * @author  ���� 
  * @Data    2018-10-26
 **/
/* -------------------------------- end -------------------------------- */
typedef	struct
{
	/*���������룩����*/
	int16_t realAngle;
	int16_t realSpeed;
	int16_t realCurrent;
	int16_t realTempeture;
	
	/*��ֵ�����������*/
	incrementalpid_st pid_wheel;
	int16_t targetSpeed;
	int16_t targetAngle;
	int16_t outCurrent;
	
	/*֡�ʿ��ƣ��ж��Ƿ����ߣ�*/
	uint8_t UpdateFlag;
	uint16_t UpdateFrame;
	uint8_t OFFLINE_SET;
	
}RM3508_st;


/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    RM6623_st
  * @brief   6623������ݴ���ṹ��
	* @param[in]  realAngle        ��ȡ��ʵ�ʽǶ�
							  realCurrent      ��ȡ��ʵ�ʵ���
							  feedbackCurrent  ���������ĸ�ֵ

  * @param[out] pid_speed(st)  ����ٶ�pid�ṹ��
								pid_angle(st)  �����λ��pid�ṹ��
								totalAngle     ����ܵĽǶ�
								turnCount      ת����Ȧ��
								targetAngle    �����Ŀ��Ƕ�
								lastAngle			 �����һ�εĽǶ�
								outCurrent     �������ĵ���
							
  * @author  ���� 
  * @Data    2018-10-26
 **/
/* -------------------------------- end -------------------------------- */
typedef struct
{
	/*���������룩����*/
	int16_t realAngle;
	int16_t realCurrent;
	int16_t feedbackCurrent;
	
	/*��ֵ�����������*/
	positionpid_st pid_speed;		
  positionpid_st pid_angle;
	int32_t totalAngle;
	int16_t turnCount;
	
	int32_t targetAngle;
	int32_t lastAngle;
	int16_t outCurrent;
	
//	/*֡�ʿ��ƣ��ж��Ƿ����ߣ�*/
//	uint8_t infoUpdateFlag;		//��Ϣ��ȡ���±�־
//	uint16_t infoUpdateFrame;	//֡��
//	uint8_t offLineFlag;		//�豸���߱�־
}RM6623_st;


/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    RM2006_st
  * @brief   2006������ݴ���ṹ��
	* @param[in]  realAngle        ��ȡ��ʵ�ʽǶ�
								realSpeed        ��ȡ��ʵ���ٶ�
							  realTorque       ��ȡ��ʵ��ת��

  * @param[out] pid_speed(st)  ����ٶ�pid�ṹ��
								pid_angle(st)  �����λ��pid�ṹ��
								totalAngle     ����ܵĽǶ�
								turnCount      ת����Ȧ��
								targetAngle    �����Ŀ��Ƕ�
								lastAngle			 �����һ�εĽǶ�
								outCurrent     �������ĵ���
							
  * @author  ���� 
  * @Data    2018-10-26
 **/
/* -------------------------------- end -------------------------------- */
typedef struct
{
	/*���������룩����*/
	int16_t realAngle;
	int16_t realSpeed;
	int16_t realTorque;
	
	/*��ֵ�����������*/
	positionpid_st pid_speed;		
  positionpid_st pid_angle;
	int32_t totalAngle;
	int16_t turnCount;
	
	int32_t targetSpeed;
	int32_t targetAngle;
	int32_t lastAngle;
	int16_t outCurrent;
	
//	/*֡�ʿ��ƣ��ж��Ƿ����ߣ�*/
//	uint8_t infoUpdateFlag;		//��Ϣ��ȡ���±�־
//	uint16_t infoUpdateFrame;	//֡��
//	uint8_t offLineFlag;		//�豸���߱�־
}RM2006_st;


/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    Chassis_st
  * @brief   �����������ݴ���ṹ��
  * @param[out] modeswitch                    ģʽѡ��(ͨ��DR16���ұߵ�ң�н��п���)
								xRaw,yRaw,zRaw                ��Ӧ��x.y.z�������
								Filter_LPFfactor              ����˲�ϵ��
								xLPF,yLPF,zLPF                �˲�֮���x,y,z�������
								Fowllow_Attitude_pid(st)      ���̸�����̬PID
								FollowYawRaw                  ������̨Yawֵ
								FollowYawLPF			            ������̨�˲�֮���Yawֵ
							
  * @author  ���� 
  * @Data    2018-10-26
 **/
/* -------------------------------- end -------------------------------- */
typedef struct
{
	/*ң��ģʽ����ң����ң��*/
	uint8_t modeswitch;
	
	/*PC�Ŀ���ģʽ*/
	uint8_t pc_control_ChassisMode;

	float Filter_LPFfactor;
	float xLPF;
	float yLPF;
	float zLPF;
	
	positionpid_st Fowllow_Attitude_pid;
	float FollowYawRaw;
	float FollowYawLPF;
	
	/*��־λ*/
	uint8_t Power_OverflowFlag;//�����ʱ�־λ
	
}Chassis_st;

/*��Ӧ��modeswitchģʽ*/
typedef enum
{
  Status_ControlByRC = 3,
  Status_ControlByPC = 1,
  Status_ControlOFF = 2,
} MODE_st;

/*��Ӧ��pc_control_ChassisModeģʽ*/
typedef enum
{
	Chassis_Normal = 1,
	Chassis_Fellow = 2,
		
}PC_Mode_st;



typedef struct
{
	float Filter_LPFfactor;
	float Yaw_Raw;
	float Pitch_Raw;
	float Yaw_LPF;
	float Pitch_LPF;
	
	
	
	
}Cloud_st;
















/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    DR16_DBUS_DATA_st
  * @brief   ң�����ݰ�����
  * @param[out] rc(st)                        ң������Ӧ���ݰ�
								mouse(st)                     ����Ӧ���ݰ�
								keyBoard(st)                      ���̶�Ӧ�����ݰ�		
  * @author  ���� 
  * @Data    2018-10-26
 **/
/* -------------------------------- end -------------------------------- */
typedef struct
{
		/*ң��������*/
    struct 
		{
        int16_t ch0;
        int16_t ch1;
        int16_t ch2;
        int16_t ch3;

        uint8_t s_left;
        uint8_t s_right;
    } rc;
		
		/*���Ա���*/
    struct
    {
        int16_t x;
        int16_t y;
        int16_t z;

        uint8_t keyLeft;
        uint8_t keyRight;

    } mouse;

		/*���̱���*/
    union
    {
        uint16_t key_code;
        struct 
				{
					
					 
					//WASDQE
            bool press_W:1;
            bool press_S:1;
            bool press_A:1;
            bool press_D:1;
						bool press_Shift:1;
            bool press_Ctrl:1;
            bool press_Q:1;
            bool press_E:1;
   
					/*��������ϼ�*/
            bool press_R:1;
            bool press_F:1;
            bool press_G:1;
            bool press_Z:1;
            bool press_X:1;
            bool press_C:1;
            bool press_V:1;
            bool press_B:1;
           
        };
    } keyBoard;
		
	/*֡�ʿ��ƣ��ж��Ƿ����ߣ�*/
	uint16_t UpdateFrame;
	uint8_t OFFLINE_SET;
		
} DR16_DBUS_DATA_st;



/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    rocker_st
  * @brief   ң������Ӧ���ݰ�����
  * @param[out] x,y                        ��Ӧ��x��y�������
								mouse(st)                     ����Ӧ���ݰ�
								keyBoard(st)                      ���̶�Ӧ�����ݰ�		
  * @author  ���� 
  * @Data    2018-10-26
 **/
/* -------------------------------- end -------------------------------- */
typedef struct
{
    float x;
    float y;
    float radian;
    float degrees;
    float distance;
} rocker_st;



/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    Key_st
  * @brief   ����״̬��������
  * @param[out] key_Status                    ��λ��ֵ
								last_key_Status               ��һ����λ��ֵ
								key_dowm_point                ��λ���µļ�λֵ
							  key_up_point                  ��λ�������ļ�λֵ
							  key_longpress_point           ��λ�����ļ�λֵ
							  pointing_time                 ������ʱ�����
  * @author  ���� 
  * @Data    2018-10-26
 **/
/* -------------------------------- end -------------------------------- */
typedef struct
{
	uint16_t key_Status;
	uint16_t last_key_Status;
	uint16_t key_dowm_point;
	uint16_t key_up_point;
	uint16_t key_longpress_point;
	uint16_t pointing_time;
}Key_st;




#endif
