#ifndef __STURCTURE__
#define __STURCTURE__

#include "Users.h"

#pragma anon_unions

/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    incrementalpid_st
  * @brief   增量式PID
	* @param   Target_speed     目标速度
						 Measured_speed   测量速度
						 error            当前偏差值（差值）
						 last_error       上一次的偏差值（上一次差值）
						 beforelast_error 上上次的偏差值（上上次差值）
						 Kp,Ki,Kd         积分对应的三个量
						 PWM              计算得出的PWM的值
						 MaxOutput        最大输出限幅
						 IntegralLimit    积分限幅
						 
						 data_u           本次得出的PWM值
						 data_out         总输出的PWM的值
						 data_lastout     上一次输出的PWM的值
						 
  * @author  口无 
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
  * @brief   位置式PID
	* @param   Target     目标速度
						 Measured   测量速度
						 error            当前偏差值（差值）
						 last_error       上一次的偏差值（上一次差值）
						 Add_error        累积的偏差值
						 Kp,Ki,Kd         积分对应的三个量
						 PWM              计算得出的PWM的值
						 MaxOutput        最大输出限幅
						 IntegralLimit    积分限幅
  * @author  口无 
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
  * @brief   3508电机数据储存结构体
	* @param[in]  realAngle      读取的实际角度
							  realSpeed      读取的实际速度
							  realCurrent    读取的实际电流
							  realTempeture  读取的实际的温度

  * @param[out] pid_wheel(st)  轮子速度pid结构体
								targetSpeed    轮子的目标速度
								targetAngle    轮子的目标角度
								outCurrent     输出的电流
							
  * @author  口无 
  * @Data    2018-10-26
 **/
/* -------------------------------- end -------------------------------- */
typedef	struct
{
	/*反馈（输入）部分*/
	int16_t realAngle;
	int16_t realSpeed;
	int16_t realCurrent;
	int16_t realTempeture;
	
	/*赋值（输出）部分*/
	incrementalpid_st pid_wheel;
	int16_t targetSpeed;
	int16_t targetAngle;
	int16_t outCurrent;
	
	/*帧率控制（判断是否离线）*/
	uint8_t UpdateFlag;
	uint16_t UpdateFrame;
	uint8_t OFFLINE_SET;
	
}RM3508_st;


/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    RM6623_st
  * @brief   6623电机数据储存结构体
	* @param[in]  realAngle        读取的实际角度
							  realCurrent      读取的实际电流
							  feedbackCurrent  反馈电流的赋值

  * @param[out] pid_speed(st)  电机速度pid结构体
								pid_angle(st)  电机的位置pid结构体
								totalAngle     电机总的角度
								turnCount      转过的圈数
								targetAngle    电机的目标角度
								lastAngle			 电机上一次的角度
								outCurrent     电机输出的电流
							
  * @author  口无 
  * @Data    2018-10-26
 **/
/* -------------------------------- end -------------------------------- */
typedef struct
{
	/*反馈（输入）部分*/
	int16_t realAngle;
	int16_t realCurrent;
	int16_t feedbackCurrent;
	
	/*赋值（输出）部分*/
	positionpid_st pid_speed;		
  positionpid_st pid_angle;
	int32_t totalAngle;
	int16_t turnCount;
	
	int32_t targetAngle;
	int32_t lastAngle;
	int16_t outCurrent;
	
//	/*帧率控制（判断是否离线）*/
//	uint8_t infoUpdateFlag;		//信息读取更新标志
//	uint16_t infoUpdateFrame;	//帧率
//	uint8_t offLineFlag;		//设备离线标志
}RM6623_st;


/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    RM2006_st
  * @brief   2006电机数据储存结构体
	* @param[in]  realAngle        读取的实际角度
								realSpeed        读取的实际速度
							  realTorque       读取的实际转矩

  * @param[out] pid_speed(st)  电机速度pid结构体
								pid_angle(st)  电机的位置pid结构体
								totalAngle     电机总的角度
								turnCount      转过的圈数
								targetAngle    电机的目标角度
								lastAngle			 电机上一次的角度
								outCurrent     电机输出的电流
							
  * @author  口无 
  * @Data    2018-10-26
 **/
/* -------------------------------- end -------------------------------- */
typedef struct
{
	/*反馈（输入）部分*/
	int16_t realAngle;
	int16_t realSpeed;
	int16_t realTorque;
	
	/*赋值（输出）部分*/
	positionpid_st pid_speed;		
  positionpid_st pid_angle;
	int32_t totalAngle;
	int16_t turnCount;
	
	int32_t targetSpeed;
	int32_t targetAngle;
	int32_t lastAngle;
	int16_t outCurrent;
	
//	/*帧率控制（判断是否离线）*/
//	uint8_t infoUpdateFlag;		//信息读取更新标志
//	uint16_t infoUpdateFrame;	//帧率
//	uint8_t offLineFlag;		//设备离线标志
}RM2006_st;


/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    Chassis_st
  * @brief   底盘完整数据储存结构体
  * @param[out] modeswitch                    模式选择(通过DR16的右边的遥感进行控制)
								xRaw,yRaw,zRaw                对应的x.y.z轴的数据
								Filter_LPFfactor              电机滤波系数
								xLPF,yLPF,zLPF                滤波之后的x,y,z轴的数据
								Fowllow_Attitude_pid(st)      底盘跟随姿态PID
								FollowYawRaw                  跟随云台Yaw值
								FollowYawLPF			            跟随云台滤波之后的Yaw值
							
  * @author  口无 
  * @Data    2018-10-26
 **/
/* -------------------------------- end -------------------------------- */
typedef struct
{
	/*遥控模式，用遥控右遥杆*/
	uint8_t modeswitch;
	
	/*PC的控制模式*/
	uint8_t pc_control_ChassisMode;

	float Filter_LPFfactor;
	float xLPF;
	float yLPF;
	float zLPF;
	
	positionpid_st Fowllow_Attitude_pid;
	float FollowYawRaw;
	float FollowYawLPF;
	
	/*标志位*/
	uint8_t Power_OverflowFlag;//超功率标志位
	
}Chassis_st;

/*对应的modeswitch模式*/
typedef enum
{
  Status_ControlByRC = 3,
  Status_ControlByPC = 1,
  Status_ControlOFF = 2,
} MODE_st;

/*对应的pc_control_ChassisMode模式*/
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
  * @brief   遥控数据包储存
  * @param[out] rc(st)                        遥控器对应数据包
								mouse(st)                     鼠标对应数据包
								keyBoard(st)                      键盘对应的数据包		
  * @author  口无 
  * @Data    2018-10-26
 **/
/* -------------------------------- end -------------------------------- */
typedef struct
{
		/*遥控器变量*/
    struct 
		{
        int16_t ch0;
        int16_t ch1;
        int16_t ch2;
        int16_t ch3;

        uint8_t s_left;
        uint8_t s_right;
    } rc;
		
		/*电脑变量*/
    struct
    {
        int16_t x;
        int16_t y;
        int16_t z;

        uint8_t keyLeft;
        uint8_t keyRight;

    } mouse;

		/*键盘变量*/
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
   
					/*功能性组合键*/
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
		
	/*帧率控制（判断是否离线）*/
	uint16_t UpdateFrame;
	uint8_t OFFLINE_SET;
		
} DR16_DBUS_DATA_st;



/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    rocker_st
  * @brief   遥控器对应数据包解析
  * @param[out] x,y                        对应的x，y轴的坐标
								mouse(st)                     鼠标对应数据包
								keyBoard(st)                      键盘对应的数据包		
  * @author  口无 
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
  * @brief   按键状态储存数组
  * @param[out] key_Status                    键位的值
								last_key_Status               上一个键位的值
								key_dowm_point                键位按下的键位值
							  key_up_point                  键位弹起来的键位值
							  key_longpress_point           键位长按的键位值
							  pointing_time                 长按的时间计算
  * @author  口无 
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
