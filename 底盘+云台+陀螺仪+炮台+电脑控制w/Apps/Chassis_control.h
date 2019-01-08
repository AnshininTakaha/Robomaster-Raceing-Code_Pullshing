#ifndef __Chassis_control
#define __Chassis_control

/*����������*/
#include "Users.h"
extern Chassis_t Chassis;
/*�����ٶ����ƣ�����*/
#define Chassis_MaxSpeed_Y	3300.0f		//����ǰ������ٶ�
#define Chassis_MaxSpeed_X	3300.0f		//����ƽ������ٶ�
#define Chassis_MaxSpeed_W	3300.0f		//������������ٶ�

/*�˲�ϵ��*//*�궨���˲�ϵ��������Ϊ����ⷽ���������ĺ궨���Ѿ����ĳ��˳�ʼ������*/
#define Chassis_LpfAttFactor 0.04f

/*������������ٶ�����*/
#define Chassis_SpeedNormal		4300.0f //�����ٶ�
#define Chassis_SpeedFast		6600.0f
#define Chassis_SpeedSlow		3000.0f

/*ҡ���ٶ�*/
#define Chassis_SwingSpeed_Normal		3900
#define Chassis_SwingSpeed_Slow			2200

/*����ģʽ�궨��*/
#define Chassis_Mode_Normal			0
#define Chassis_Mode_Follow			1
/*���̳�ʼ��*/
void Chassis_Init(void);



/*���̿��ƴ���*/
void Chassis_processing(float Vx, float Vy, float VOmega, uint8_t mode);

/*�����ٶ�ģ�ͽ���*/
void MecanumCalculation(float Vx, float Vy, float VOmega, int16_t *Speed);

/*��������*/
void Chassis_powerLimit(M3508s_t *p_M3508s, float CurrentLimit);


#endif

