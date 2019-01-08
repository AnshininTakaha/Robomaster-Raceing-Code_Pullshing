#ifndef __STURCTURE__
#define __STURCTURE__

#include "Users.h"

#pragma anon_unions

typedef struct 
{
		float x;
		float y;
		float z;
}vector_st;

typedef struct 
{
	float roll;
	float pitch;
	float yaw;
}eular_st;
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
	
/*֡�ʿ��ƣ��ж��Ƿ����ߣ�*/
	uint8_t UpdateFlag;
	uint16_t UpdateFrame;
	uint8_t OFFLINE_SET;
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
		uint8_t UpdateFlag;
		uint16_t UpdateFrame;
		uint8_t OFFLINE_SET;
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


/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    Cloud_st & GY_IMU_t
  * @brief   ��̨�������ݴ���ṹ��
  * @param[out] pc_control_CloudMode          ��ӦPCģʽѡ��
								Filter_LPFfactor              ����˲�ϵ��

								Yaw_Raw                       YAWĿ���
								Yaw_LPF                       YAW�˲����
								Pitch_Raw											PitchĿ���
								Pitch_LPF											Pitch�˲����
								IMUYaw_Raw										IMUĿ���
								IMUYaw_LPF                    IMU�˲����

								IMUYawAngleMax                ��̨IMU���Ƕȣ��ң�
								IMUYawAngleMin                ��̨IMU��С�Ƕȣ���
								IMUPitchAngleMax              ��̨IMU���Ƕ�(��)
								IMUPitchAngleMin              ��̨IMU��С�Ƕȣ��ϣ�
								
								YAW_Attitude_pid(st),YAW_Speed_pid(st)
								��̨λ��YAW�����̬PID
								
								Roll_Attitude_pid(st),Roll_Speed_pid(st)
								��̨λ��Pitch�����̬PID
							
							
							
	* @param[out]	gyro(st)                      ���ٶȽṹ��
								eular(st)                     ŷ���ǽṹ��
								
								lastYaw                       ��һ��YAW������������
								totalYaw                      �ܵ�YAW������������
								
  * @author  ���� 
  * @Data    2018-10-26
 **/
/* -------------------------------- end -------------------------------- */
typedef struct
{
	/*ң��ģʽ����ң����ң��*/
	uint8_t modeswitch;
	
	/*PC�Ŀ���ģʽ*/
	uint8_t pc_control_CloudMode;
	
	float Filter_LPFfactor;
	float Yaw_Raw;
	float Yaw_LPF;
	
	float Pitch_Raw;
	float Pitch_LPF;
	
	float IMUYaw_Raw;
	float IMUYaw_LPF;
	float IMUPitch_Raw;
	float IMUPitch_LPF;
	
	float IMUYawAngleMax;		//��̨IMU���Ƕ�(��)
	float IMUYawAngleMin;		//��̨IMU��С�Ƕ�(��)
	float IMUPitchAngleMax;		//��̨IMU���Ƕ�(��)
	float IMUPitchAngleMin;		//��̨IMU��С�Ƕ�(��)
	
	positionpid_st YAW_Attitude_pid;
	positionpid_st YAW_Speed_pid;
	
	positionpid_st Roll_Attitude_pid;
	positionpid_st Roll_Speed_pid;
	
	
}Cloud_st;
/*��Ӧ��modeswitchģʽ*/
//typedef enum
//{
//  Status_ControlByRC = 3,
//  Status_ControlByPC = 1,
//  Status_ControlOFF = 2,
//} MODE_st;
/*��Ӧ��pc_control_CloudMode����ģʽ*/
typedef enum
{
	Cloud_Normal = 1,//����ģʽ
	Cloud_Master = 2,//��̨������ģʽ
		
}PC_Cloud_Mode_st;



/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    GY_IMU_t
  * @brief   �����Ǵ��溯��
  * @param[out] gyro(st)                      ���ٶȴ���ṹ��
								eular(st)                     ����Ӧ���ݰ�
								keyBoard(st)                      ���̶�Ӧ�����ݰ�		
  * @author  ���� 
  * @Data    2018-10-26
 **/
/* -------------------------------- end -------------------------------- */
typedef struct
{
	vector_st gyro;
	eular_st eular;
	
	float lastYaw;
	float totalYaw;
	int16_t turnCount;
	uint8_t devStatus; 
	
	uint8_t UpdateFlag;
	uint16_t UpdateFrame;
	uint8_t OFFLINE_SET;
}GY_IMU_t;

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
/*DR16ң�ж�Ӧֵ���ң������λ����ͬ��*/
//typedef enum
//{
//  Status_ControlByPC = 1,
//  Status_ControlByRC = 3,
//  Status_ControlOFF = 2,
//} MODE_st;


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

/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    Fire_st & firction_st
  * @brief   ���������־λ��Ħ���ֱ�־λ����
  * @param[out] Fire_ready                    �Ƿ��⵽���İ��»���ң������ң��
								Fire_shoot_Flag               ׼�������־λ
								Fire_out_number   						����ӵ���
								loading_finish 								���ӵ���ɣ������Ƿ����ӵ���

								firction_ready                Ħ���ֿ�����ɱ�־λ
							  firctionspeed_Raw             Ħ����Ŀ���ٶ�
							  
  * @author  ���� 
  * @Data    2018-10-26
 **/
/* -------------------------------- end -------------------------------- */
typedef struct
{
	uint16_t Fire_ready;
	uint16_t Fire_shoot_Flag;
	uint16_t Fire_out_number;
	uint16_t loading_finish;
}Fire_st;


typedef struct
{
	uint16_t firction_ready;
	uint16_t firctionspeed_Raw;
	
}firction_st;


#endif
