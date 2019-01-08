#ifndef __Chassis_control
#define __Chassis_control

/*总引导函数*/
#include "Users.h"
extern Chassis_t Chassis;
/*底盘速度限制（单向）*/
#define Chassis_MaxSpeed_Y	3300.0f		//底盘前后最快速度
#define Chassis_MaxSpeed_X	3300.0f		//底盘平移最快速度
#define Chassis_MaxSpeed_W	3300.0f		//底盘自旋最快速度

/*滤波系数*//*宏定义滤波系数，但是为了理解方便代码里面的宏定义已经被改成了初始定义了*/
#define Chassis_LpfAttFactor 0.04f

/*底盘自身最高速度限制*/
#define Chassis_SpeedNormal		4300.0f //正常速度
#define Chassis_SpeedFast		6600.0f
#define Chassis_SpeedSlow		3000.0f

/*摇动速度*/
#define Chassis_SwingSpeed_Normal		3900
#define Chassis_SwingSpeed_Slow			2200

/*底盘模式宏定义*/
#define Chassis_Mode_Normal			0
#define Chassis_Mode_Follow			1
/*底盘初始化*/
void Chassis_Init(void);



/*底盘控制处理*/
void Chassis_processing(float Vx, float Vy, float VOmega, uint8_t mode);

/*麦轮速度模型解算*/
void MecanumCalculation(float Vx, float Vy, float VOmega, int16_t *Speed);

/*电流限制*/
void Chassis_powerLimit(M3508s_t *p_M3508s, float CurrentLimit);


#endif

