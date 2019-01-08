#ifndef __TYPEDEF_H
#define __TYPEDEF_H


/*������*/
#include "Users.h"

//#include <stdbool.h>
//#include <stdint.h>

//��������������
#pragma anon_unions

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;

/*CAN���ͻ��ǽ��յ�ID*/
typedef enum
{

//	CAN_TxPY12V_ID 	= 0x200,		//��̨12V����ID
//	CAN_TxPY24V_ID	= 0x1FF,		//��̨12V����ID
////	CAN_Pitch_ID 	= 0x201,			//��̨Pitch
////	CAN_Yaw_ID   	= 0x203,			//��̨Yaw
//	CAN_YAW_FEEDBACK_ID   = 0x205,		//��̨Yaw24v
//	CAN_PIT_FEEDBACK_ID  = 0x206,			//��̨Yaw24v
//	CAN_POKE_FEEDBACK_ID  = 0x207,
//	CAN_ZGYRO_RST_ID 			= 0x404,
//	CAN_ZGYRO_FEEDBACK_MSG_ID = 0x401,
//	CAN_MotorLF_ID 	= 0x041,    //��ǰ
//	CAN_MotorRF_ID 	= 0x042,		//��ǰ
//	CAN_MotorLB_ID 	= 0x043,    //���
//	CAN_MotorRB_ID 	= 0x044,		//�Һ�

//	CAN_EC60_four_ID	= 0x200,	//EC60���ճ���
//	CAN_backLeft_EC60_ID = 0x203, //ec60
//	CAN_frontLeft_EC60_ID = 0x201, //ec60
//	CAN_backRight_EC60_ID = 0x202, //ec60
//	CAN_frontRight_EC60_ID = 0x204, //ec60
	
	CAN_3510Moto_ALL_ID = 0x200,
	CAN_3510Moto1_ID = 0x201,
	CAN_3510Moto2_ID = 0x202,
	CAN_3510Moto3_ID = 0x203,
	CAN_3510Moto4_ID = 0x204,
	
	CAN_DriverPower_ID = 0x80,

	CAN_HeartBeat_ID = 0x156,
	
}CAN_Message_ID;

typedef struct{
	float Target; 					        //�趨Ŀ��ֵ
	float Measured; 				    //����ֵ
	float err; 						            //����ƫ��ֵ
	float err_last; 				        //��һ��ƫ��
	float err_beforeLast; 			//���ϴ�ƫ��
	float Kp, Ki, Kd;				      //Kp, Ki, Kd����ϵ��
	float pwm; 						        //pwm���
	uint32_t MaxOutput;				//����޷�
    uint32_t IntegralLimit;		//�����޷� 
}incrementalpid_t;

typedef struct{
	float Target; 					//�趨Ŀ��ֵ
	float Measured; 				//����ֵ
	float err; 						//����ƫ��ֵ
	float err_last; 				//��һ��ƫ��
	float integral_err; 			//����ƫ��֮��
	float Kp, Ki, Kd;				//Kp, Ki, Kd����ϵ��
	float pwm; 						//pwm���
	uint32_t MaxOutput;				//����޷�
  uint32_t IntegralLimit;			//�����޷� 
}positionpid_t;


typedef struct{
//	uint16_t motorInfoID;		//�õ�������ݵ�CAN ID
	uint16_t realAngle;			//�������Ļ�е�Ƕ�
	int16_t realSpeed;			//���������ٶ�
	int16_t realCurrent;		//��������ʵ�ʵ���
	uint8_t temperture;			//�������ĵ���¶�
//	int16_t targetCurrent;			//Ŀ�����
	int16_t targetSpeed;			//Ŀ���ٶ�
	uint16_t targetAngle;			//Ŀ��Ƕ�
	int16_t outCurrent;				//�������
	incrementalpid_t pid;		//���pid
	uint8_t infoUpdateFlag;		//��Ϣ��ȡ���±�־
	
}M3508s_t;

typedef struct{
//	uint16_t motorInfoID;		//�õ�������ݵ�CAN ID
	uint16_t realAngle;			//�������Ļ�е�Ƕ�
//	int16_t realSpeed;			//���������ٶ�
	int16_t realCurrent;		//��������ʵ�ʵ���
//	uint8_t temperture;			//�������ĵ���¶�
//	int16_t targetCurrent;			//Ŀ�����
//	int16_t targetSpeed;			//Ŀ���ٶ�
	int32_t targetAngle;			//Ŀ��Ƕ�
	int16_t outCurrent;				//�������
	uint16_t lastAngle;			//�ϴεĽǶ�
	int16_t turnCount;			//ת����Ȧ��
	positionpid_t pid;			//���pid
	uint8_t infoUpdateFlag;		//��Ϣ��ȡ���±�־
	
}M6623s_t;

typedef struct{
//	uint16_t motorInfoID;		//�õ�������ݵ�CAN ID
	uint16_t realAngle;			//�������Ļ�е�Ƕ�
	int16_t realSpeed;			//���������ٶ�
	int16_t realTorque;			//��������ʵ��ת��
	uint16_t lastAngle;			//�ϴεĽǶ�
	int32_t addAngle;			//�ۻ��ĽǶ�
	int16_t turnCount;			//ת����Ȧ��
//	uint8_t temperture;			//�������ĵ���¶�
//	int16_t targetCurrent;			//Ŀ�����
	int16_t targetSpeed;			//Ŀ���ٶ�
	int32_t targetAngle;			//Ŀ��Ƕ�
	int16_t outCurrent;				//�������
	incrementalpid_t pid_speed;		//����ٶ�pid
	positionpid_t pid_angle;		//����Ƕ�pid
	uint8_t infoUpdateFlag;		//��Ϣ��ȡ���±�־
	uint8_t loadFinish;			//�ӵ��������
	
}M2006s_t;

typedef struct{
	float yawRaw;				//��̨yaw��ԭʼ����
	float pitchRaw;				//��̨pitch��ԭʼ����
	float yawOverflow;			//��̨yaw��ת�����ֵ
	float pitchOverflow;		//��̨pitch��ת�����ֵ
	float LpfAttFactor;			//��̨�˲�ϵ��
	float yawLPF;				//��̨yaw���˲�������
	float pitchLPF;				//��̨pitch���˲�������
}Cloud_t;

typedef struct{
	float xRaw;				//����x��ԭʼ����
	float yRaw;				//����y��ԭʼ����
	float zRaw;				//����z��ԭʼ����
	float LpfAttFactor;		//�����˲�ϵ��
	float xLPF;				//����x���˲�������
	float yLPF;				//����y���˲�������
	float zLPF;				//����z���˲�������
}Chassis_t;


typedef enum{
	M3508_UL = 0,
	M3508_UR,
	M3508_DL,
	M3508_DR
}M3508Name_e;

typedef enum{
	M6623_YAW = 0,
	M6623_PITCH,
}M6623Name_e;

typedef enum{
	M2006_BulletLoad = 0,
}M2006Name_e;

typedef enum{
	Status_ControlByRC = 3,
	Status_ControlByPC = 2,
	Status_ControlOFF = 1,
}StatusControlMode_e;

typedef struct{
	uint8_t ControlMode;
}Status_t;

typedef struct{
	uint8_t KeyStatus;
	uint8_t lastKeyStatus;
	uint8_t keyPressedJump;
	uint8_t keyReleaseJump;
}key_t;



typedef struct {
	struct{
		int16_t ch0;
		int16_t ch1;
		int16_t ch2;
		int16_t ch3;

		uint8_t s_left;
		uint8_t s_right;
	}rc;
	
	struct{
		int16_t x;
		int16_t y;
		int16_t z;
	
		key_t keyLeft;
		key_t keyRight;
		
	}mouse;
	
	union {
		uint16_t key_code;
		struct{
			bool press_W:1;
			bool press_S:1;
			bool press_A:1;
			bool press_D:1;
			bool press_Shift:1;
			bool press_Ctrl:1;
			bool press_Q:1;
			bool press_E:1;
		};
	}keyBoard;
}DR16_DBUS_DATA_t;



typedef struct {
	union {
		uint8_t dataBuff[2][8];
		struct{
			int16_t posX;		/* ��λ����x �����ף� */
			int16_t posY;		/* ��λ����y �����ף� */
			uint16_t angleYaw;		/* ����� */
			int16_t distance[6];		/* ��ǩ��������վ�ľ��� */
			uint16_t errANDsignel;		/* �����������ź�ǿ�� */
			uint16_t reserved;			/* ���� */
		};
	}data;
	uint8_t infoUpdateFlag;
}UWB_DATA_t;


typedef struct {
	float x;
	float y;
	float radian;
	float degrees;
	float distance;
}rocker_t;


typedef struct {
		float w;
		float x;
		float y;
		float z;
}quaternion_t;

typedef struct {
		float x;
		float y;
		float z;
}vector_t;

typedef struct {
		int16_t x;
		int16_t y;
		int16_t z;
}vector16_t;

typedef struct {
		float yaw;
		float pitch;
		float roll;
}eular_t;



#endif /* __TYPEDEFS_H */
