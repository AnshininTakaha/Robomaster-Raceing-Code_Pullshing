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
    CAN_3510Moto_ALL_ID = 0x200,
    CAN_3510Moto1_ID = 0x201,
    CAN_3510Moto2_ID = 0x202,
    CAN_3510Moto3_ID = 0x203,
    CAN_3510Moto4_ID = 0x204,

    CAN_DriverPower_ID = 0x80,

    CAN_HeartBeat_ID = 0x156,

} CAN_Message_ID;

typedef struct
{
    float Target; 					        //设定目标值
    float Measured; 				    //测量值
    float err; 						            //本次偏差值
    float err_last; 				        //上一次偏差
    float err_beforeLast; 			//上上次偏差
    float Kp, Ki, Kd;				      //Kp, Ki, Kd控制系数
    float pwm; 						        //pwm输出
    uint32_t MaxOutput;				//输出限幅
    uint32_t IntegralLimit;		//积分限幅
} incrementalpid_t;

typedef struct
{
    float Target; 					//设定目标值
    float Measured; 				//测量值
    float err; 						//本次偏差值
    float err_last; 				//上一次偏差
    float integral_err; 			//所有偏差之和
    float Kp, Ki, Kd;				//Kp, Ki, Kd控制系数
    float pwm; 						//pwm输出
    uint32_t MaxOutput;				//输出限幅
    uint32_t IntegralLimit;			//积分限幅
} positionpid_t;


typedef struct
{

    uint16_t realAngle;			//读回来的机械角度
    int16_t realSpeed;			//读回来的速度
    int16_t realCurrent;		//读回来的实际电流
    uint8_t temperture;			//读回来的电机温度

    int16_t targetSpeed;			//目标速度
    uint16_t targetAngle;			//目标角度
    int16_t outCurrent;				//输出电流
    incrementalpid_t pid;		//电机pid
    uint8_t infoUpdateFlag;		//信息读取更新标志
    uint16_t infoUpdateFrame;	//帧率
    uint8_t offLineFlag;		//设备离线标志

} M3508s_t;

typedef struct
{
    int32_t totalAngle;     //读取回来的累加总角度
    uint16_t realAngle;			//读回来的机械角度
    int16_t realCurrent;		//读回来的实际电流
    int32_t targetAngle;			//目标角度
    int16_t outCurrent;				//输出电流
    uint16_t lastAngle;			//上次的角度
    int16_t turnCount;			//转过的圈数

    positionpid_t pid;			//电机pid

    positionpid_t pid_speed;		//电机速度pid
    positionpid_t pid_angle;		//角度电机pid

    uint8_t infoUpdateFlag;		//信息读取更新标志
    uint16_t infoUpdateFrame;	//帧率
    uint8_t offLineFlag;		//设备离线标志
} M6623s_t;



typedef struct
{

    uint16_t realAngle;			//读回来的机械角度
    int16_t realSpeed;			//读回来的速度
    int16_t realTorque;			//读回来的实际转矩
    uint16_t lastAngle;			//上次的角度
    int32_t totalAngle;			//累积的角度
    int16_t turnCount;			//转过的圈数


    int16_t targetSpeed;			//目标速度
    int32_t targetAngle;			//目标角度
    int16_t outCurrent;				//输出电流
    positionpid_t pid_speed;		//电机速度pid
    positionpid_t pid_angle;		//电机角度pid

    uint8_t infoUpdateFlag;		//信息读取更新标志
    uint8_t loadFinish;			//子弹加载完毕
    uint16_t infoUpdateFrame;	//帧率
    uint8_t offLineFlag;		//设备离线标志

} M2006s_t;

typedef struct
{
    float yawOverflow;			//云台yaw轴转向溢出值
    float pitchOverflow;		//云台pitch轴转向溢出值


    float yawRaw;				//云台yaw轴原始数据
    float pitchRaw;				//云台pitch轴原始数据
    float LpfAttFactor;			//云台滤波系数

    float yawLPF;				//云台yaw轴滤波后数据
    float pitchLPF;				//云台pitch轴滤波后数据

    float IMUYawRaw;   //IMU原始角度（横向轴）
    float IMUPitchRaw; //IMU原始角度（竖向轴）
    float IMUYawLPF;   //IMU滤波后角度（横向轴）
    float IMUPitchLPF; //IMU滤波后角度（竖向轴）

    float IMUYawMax;  //IMU横向轴最大角度
    float IMUYawMin;  //IMU横向轴最小角度
    float IMUPitchMax;//IMU竖向轴最大角度
    float IMUPitchMin;//IMU竖向轴最小角度

    positionpid_t YawAttitude_pid;			//云台yaw轴姿态pid
    positionpid_t YawSpeed_pid;			//云台yaw轴速度pid
    positionpid_t RollAttitude_pid;			//云台roll轴姿态pid
    positionpid_t RollSpeed_pid;			//云台roll轴速度pid
    uint8_t mode;						//云台控制模式
} Cloud_t;

typedef struct
{
    float xRaw;				//底盘x轴原始数据
    float yRaw;				//底盘y轴原始数据
    float zRaw;				//底盘z轴原始数据
    float LpfAttFactor;		//底盘滤波系数

    float xLPF;				//底盘x轴滤波后数据
    float yLPF;				//底盘y轴滤波后数据
    float zLPF;				//底盘z轴滤波后数据
    float speedlimit; //速度限制

    float followYawRaw;//底盘跟随云台的原始数据
    float followYawLPF;//底盘跟随云台的滤波之后的数据
    positionpid_t FollowYawAttitude_pid;		//底盘yaw轴跟随云台pid

    uint8_t mode;       //模式选择
    uint8_t swingFlag;  //摇动标志
    float swingspeed;   //摇动速度

    uint8_t Power_OverflowFlag;//超功率标志

} Chassis_t;



typedef struct
{
    uint8_t shootFlag;			//射击标志
    uint8_t fricReady;			//摩擦轮准备标志
    uint8_t fricSpeedLevel;			//摩擦轮速度等级
    uint16_t fricTargetSpeedRaw;	//摩擦轮目标速度
    uint8_t heatOverflowFlag;	//射击超热量标标志
    uint8_t shootReady;			//射击准备标志
    uint8_t shootFreq;			//射击频率
    uint8_t timeCount;			//时间计数
} shootGun_t;


typedef enum
{
    M3508_UL = 0,
    M3508_UR,
    M3508_DL,
    M3508_DR
} M3508Name_e;

typedef enum
{
    M6623_YAW = 0,
    M6623_PITCH,
} M6623Name_e;

typedef enum
{
    M2006_BulletLoad = 0,
} M2006Name_e;

typedef enum
{
    Status_ControlByRC = 3,
    Status_ControlByPC = 1,
    Status_ControlOFF = 2,
} StatusControlMode_e;

typedef struct
{
    uint8_t ControlMode;
} Status_t;



typedef struct
{
    uint16_t KeyStatus;
    uint16_t lastKeyStatus;
    uint16_t keyPressedJump;
    uint16_t keyReleaseJump;
    uint16_t longPressed;
    uint16_t timer;
} key_t;

typedef struct
{
    struct {
        int16_t ch0;
        int16_t ch1;
        int16_t ch2;
        int16_t ch3;

        uint8_t s_left;
        uint8_t s_right;
    } rc;

    struct
    {
        int16_t x;
        int16_t y;
        int16_t z;

        /**/
        uint8_t keyLeft;
        uint8_t keyRight;

    } mouse;

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

    uint16_t infoUpdateFrame;	//帧率
    uint8_t offLineFlag;		//设备离线标志
} DR16_DBUS_DATA_t;



typedef struct
{
    union
    {
        uint8_t dataBuff[2][8];
        struct {
            int16_t posX;		/* 定位坐标x （厘米） */
            int16_t posY;		/* 定位坐标y （厘米） */
            uint16_t angleYaw;		/* 航向角 */
            int16_t distance[6];		/* 标签到各个基站的距离 */
            uint16_t errANDsignel;		/* 错误类型与信号强度 */
            uint16_t reserved;			/* 保留 */
        };
    } data;
    uint8_t infoUpdateFlag;
} UWB_DATA_t;


typedef struct
{
    float x;
    float y;
    float radian;
    float degrees;
    float distance;
} rocker_t;


typedef struct
{
    float w;
    float x;
    float y;
    float z;
} quaternion_t;


/*GY_IMU和底盘运动模型储存结构体*/
typedef struct
{
    float x;
    float y;
    float z;
} vector_t;

typedef struct
{
    int16_t x;
    int16_t y;
    int16_t z;
} vector16_t;

typedef struct
{
    float yaw;
    float pitch;
    float roll;
} eular_t;


/*GY_IMU数据结构体，储存陀螺仪的数据*/
typedef struct
{
    vector_t gyro;
    eular_t eular;
    float lastYaw;
    float totalYaw;
    int16_t turnCount;
    uint8_t devStatus;
    uint8_t infoUpdateFlag;
    uint16_t infoUpdateFrame;
    uint8_t offLineFlag;
} GY_IMU_t;

//TIM6中断判断模式结构体
typedef struct
{
    uint8_t ControlMode;			//控制方式
    uint8_t SpecialMode;			//特殊模式
    uint8_t isCombineKey;			//使用组合键
} ControlStatus_t;

/*按键值*/
typedef enum
{
    SpecialMode_Normal = 0,
    SpecialMode_BigSymbol = 2,	//大符模式
    SpecialMode_UPBridge = 3,	//上桥模式
    SpecialMode_Supply = 4, 	//补给站模式
} SpecialMode_t;


//枚举结构体方便自己看而已
typedef enum {
    ControlMode_ByRC = 3,//右遥感在中
    ControlMode_ByPC = 1,//右遥感在上
    ControlMode_OFF = 2,
} ControlMode_e;

/*斜波储存结构*/
typedef struct
{
    int32_t count;
    int32_t scale;
    float   out;
} slope_t;

#endif /* __TYPEDEFS_H */
