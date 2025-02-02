#ifndef __TYPEDEF_H
#define __TYPEDEF_H


/*总引导*/
#include "Users.h"

//#include <stdbool.h>
//#include <stdint.h>

//允许匿名共用体
#pragma anon_unions

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;

/*CAN发送或是接收的ID*/
typedef enum
{

//	CAN_TxPY12V_ID 	= 0x200,		//云台12V发送ID
//	CAN_TxPY24V_ID	= 0x1FF,		//云台12V发送ID
////	CAN_Pitch_ID 	= 0x201,			//云台Pitch
////	CAN_Yaw_ID   	= 0x203,			//云台Yaw
//	CAN_YAW_FEEDBACK_ID   = 0x205,		//云台Yaw24v
//	CAN_PIT_FEEDBACK_ID  = 0x206,			//云台Yaw24v
//	CAN_POKE_FEEDBACK_ID  = 0x207,
//	CAN_ZGYRO_RST_ID 			= 0x404,
//	CAN_ZGYRO_FEEDBACK_MSG_ID = 0x401,
//	CAN_MotorLF_ID 	= 0x041,    //左前
//	CAN_MotorRF_ID 	= 0x042,		//右前
//	CAN_MotorLB_ID 	= 0x043,    //左后
//	CAN_MotorRB_ID 	= 0x044,		//右后

//	CAN_EC60_four_ID	= 0x200,	//EC60接收程序
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
	float Target; 					        //设定目标值
	float Measured; 				    //测量值
	float err; 						            //本次偏差值
	float err_last; 				        //上一次偏差
	float err_beforeLast; 			//上上次偏差
	float Kp, Ki, Kd;				      //Kp, Ki, Kd控制系数
	float pwm; 						        //pwm输出
	uint32_t MaxOutput;				//输出限幅
    uint32_t IntegralLimit;		//积分限幅 
}incrementalpid_t;

typedef struct{
	float Target; 					//设定目标值
	float Measured; 				//测量值
	float err; 						//本次偏差值
	float err_last; 				//上一次偏差
	float integral_err; 			//所有偏差之和
	float Kp, Ki, Kd;				//Kp, Ki, Kd控制系数
	float pwm; 						//pwm输出
	uint32_t MaxOutput;				//输出限幅
  uint32_t IntegralLimit;			//积分限幅 
}positionpid_t;


typedef struct{
//	uint16_t motorInfoID;		//该电机读数据的CAN ID
	uint16_t realAngle;			//读回来的机械角度
	int16_t realSpeed;			//读回来的速度
	int16_t realCurrent;		//读回来的实际电流
	uint8_t temperture;			//读回来的电机温度
//	int16_t targetCurrent;			//目标电流
	int16_t targetSpeed;			//目标速度
	uint16_t targetAngle;			//目标角度
	int16_t outCurrent;				//输出电流
	incrementalpid_t pid;		//电机pid
	uint8_t infoUpdateFlag;		//信息读取更新标志
	
}M3508s_t;

typedef struct{
//	uint16_t motorInfoID;		//该电机读数据的CAN ID
	uint16_t realAngle;			//读回来的机械角度
//	int16_t realSpeed;			//读回来的速度
	int16_t realCurrent;		//读回来的实际电流
//	uint8_t temperture;			//读回来的电机温度
//	int16_t targetCurrent;			//目标电流
//	int16_t targetSpeed;			//目标速度
	int32_t targetAngle;			//目标角度
	int16_t outCurrent;				//输出电流
	uint16_t lastAngle;			//上次的角度
	int16_t turnCount;			//转过的圈数
	positionpid_t pid;			//电机pid
	uint8_t infoUpdateFlag;		//信息读取更新标志
	
}M6623s_t;

typedef struct{
//	uint16_t motorInfoID;		//该电机读数据的CAN ID
	uint16_t realAngle;			//读回来的机械角度
	int16_t realSpeed;			//读回来的速度
	int16_t realTorque;			//读回来的实际转矩
	uint16_t lastAngle;			//上次的角度
	int32_t addAngle;			//累积的角度
	int16_t turnCount;			//转过的圈数
//	uint8_t temperture;			//读回来的电机温度
//	int16_t targetCurrent;			//目标电流
	int16_t targetSpeed;			//目标速度
	int32_t targetAngle;			//目标角度
	int16_t outCurrent;				//输出电流
	incrementalpid_t pid_speed;		//电机速度pid
	positionpid_t pid_angle;		//电机角度pid
	uint8_t infoUpdateFlag;		//信息读取更新标志
	uint8_t loadFinish;			//子弹加载完毕
	
}M2006s_t;

typedef struct{
	float yawRaw;				//云台yaw轴原始数据
	float pitchRaw;				//云台pitch轴原始数据
	float yawOverflow;			//云台yaw轴转向溢出值
	float pitchOverflow;		//云台pitch轴转向溢出值
	float LpfAttFactor;			//云台滤波系数
	float yawLPF;				//云台yaw轴滤波后数据
	float pitchLPF;				//云台pitch轴滤波后数据
}Cloud_t;

typedef struct{
	float xRaw;				//底盘x轴原始数据
	float yRaw;				//底盘y轴原始数据
	float zRaw;				//底盘z轴原始数据
	float LpfAttFactor;		//底盘滤波系数
	float xLPF;				//底盘x轴滤波后数据
	float yLPF;				//底盘y轴滤波后数据
	float zLPF;				//底盘z轴滤波后数据
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
			int16_t posX;		/* 定位坐标x （厘米） */
			int16_t posY;		/* 定位坐标y （厘米） */
			uint16_t angleYaw;		/* 航向角 */
			int16_t distance[6];		/* 标签到各个基站的距离 */
			uint16_t errANDsignel;		/* 错误类型与信号强度 */
			uint16_t reserved;			/* 保留 */
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
