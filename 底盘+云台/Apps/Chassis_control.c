/**
  ******************************************************************************
  * @file    Chassis_control.c
  * @author  Hare
  * @version V1.0
  * @date    
  * @brief   ���̿��ƺ����ӿ�
  ******************************************************************************
  */

#include "Chassis_control.h"

//#define Chassis_LpfAttFactor 0.098f
Chassis_t Chassis = {.LpfAttFactor = 0.098f};

/*��������д��˳�򣬷������ǿ�*/
void MecanumCalculation(float Vx, float Vy, float VOmega, int16_t *Speed);
void Chassis_powerLimit(M3508s_t *p_M3508s, float CurrentLimit);



void Chassis_Init(void)
{
	for(int i = 0; i < 4; i++)
	{
		IncrementalPID_paraReset(&M3508s[i].pid, 2.8f, 0.4f, 0.0f, 16000, 5000);
	}
}


/**
  * @brief  ���̿��ƴ���
  * @param[in]  Vx		x���ٶ�
  *				Vy		y���ٶ�
  *				Omega	ƫ���
*				mode	ģʽ - ��Status_ControlOFF�⣬������������
  * @retval None
  */

void Chassis_processing(float Vx, float Vy, float VOmega, uint8_t mode)
{
	
	if(mode == Status_ControlOFF)
	{    
		/*����ģʽ��������ڵ�һ��ģʽ���Ͱ����Ӷ�ͣ����*/
		M3508_setCurrent(0, 0, 0, 0);
		return;
	}
	
	//ƽ�����������Ǽ��������ݷ��͹����ж���ļⲨ
	/*�˲���ֵ���Լ����õ�*/
	Filter_IIRLPF(&Vx, &Chassis.xLPF, Chassis.LpfAttFactor);
	Filter_IIRLPF(&Vy, &Chassis.yLPF, Chassis.LpfAttFactor);
	Filter_IIRLPF(&VOmega, &Chassis.zLPF, Chassis.LpfAttFactor);
	/*ͨ���˲�����֮�������ֵ�������д���*/
	
	
	int16_t speed[4];
	//���ֽ��㹫ʽ����ƽ���������ٶȸ�ֵ�����ֵĽ��㹫ʽ
	//ͨ��ģ�ͷֽ����Ӧ���ĸ����Ӹ�ֵ�ٶȣ���Ϊ�����֣���֮ǰ���ٶȷֽ����е㲻ͬ�ģ�
	//�ֽ�֮���������ٶȺ͵��ֵı�ֵ
	//�����е����ӵ��ٶȳ��������ֵ�����������ĸ����ӵ��ٶ�
	MecanumCalculation(Chassis.xLPF, Chassis.yLPF, Chassis.zLPF, speed);
	
	/*���������ֵ��������и�ֵ��Ŀ��ֵ����Ȼ�����PID�ٶȵ���*/
	for(int i = 0; i<4; i++)
	{
		if(M3508s[i].infoUpdateFlag == 1)//�ж����ǵ���Ϣ��ȡ���±�־λ���Ƿ�Ϊ1
		{
			/*����Ǿ�д�����ǵ��ٶ�*/
			M3508s[i].targetSpeed = speed[i];
			
			/*����ʽPID����*/
			M3508s[i].outCurrent = Incremental_PID(&M3508s[i].pid, M3508s[i].targetSpeed, M3508s[i].realSpeed); 
			//�����־λ
			M3508s[i].infoUpdateFlag = 0;
		}
	}
	
	//���ʻ��弴��GG��Ҳ���ǹ��ʼ�����������
//	if(Judge_PowerHeatData.data.chassisPowerBuffer < 20)
//	{
//		/*��������*/
//		Chassis_powerLimit(M3508s, 80000.0f/24.0f);
//	}
	
	
	//�趨�������ֵ����Ҫ��������ϵͳ�ļ���֮��ſ��������Ӧ�ĵ��ֵ
	//�Ե�����������еĴ���֮���ٽ��и�ֵ
	M3508_setCurrent(M3508s[0].outCurrent, M3508s[1].outCurrent, M3508s[2].outCurrent, M3508s[3].outCurrent);
	
}


/**
  * @brief  �����ķ���ٶȽ���
  * @param[in]  Vx		x���ٶ�
  *							Vy		y���ٶ�
  *							VOmega	��ת�ٶ�
  * @param[out]	Speed	�ٶȣ�����һ���ṹ�������������������������棩
  * @retval None
  */
void MecanumCalculation(float Vx, float Vy, float VOmega, int16_t *Speed)
{
	/*�������ڴ���Ľṹ��*/
  float tempSpeed[4];
	float Param = 1;
	float MaxSpeed = 0;
	
	/*�����ٶȷֽ�*/
	/*��Ҫ֪���ĸ����ӵ�λ�ý������ӽ�ģ*/
	/*���ӵ�λ����Readme�����Լ�ȥ��*/
	/*ͨ��ģ��Vx��Vy��VOmega���������������ж�*/
	/*ʵ���Ͼ���ͨ���ֽ�������ٶȷֱ�������ĸ���������*/
	/*�����ǰ��ʱ���ģ��Ϊ���ӣ�ֱ�ӿ����ӵ�С�ֳ������жϳ���Ӧ����*/
	/*����ģ��֮��Ϳ���ģ�ⷽ����*/
	  tempSpeed[0] = Vx - Vy + VOmega;
    tempSpeed[1] = Vx + Vy + VOmega;
    tempSpeed[2] = -Vx + Vy + VOmega;
    tempSpeed[3] = -Vx - Vy + VOmega;
	

    /*������ĸ������е�����ٶ�*/
    for(uint8_t i = 0, MaxSpeed = 0; i < 4; i++)//�����ĸ������ٶȵ����ֵ
    {
			if(abs(tempSpeed[i]) > MaxSpeed)//abs()Ϊ����ֵ����
        {
            MaxSpeed = abs(tempSpeed[i]);
        }
    }
	
		/*�ٶȷ���*/
		/*�е����������ٶȵ����ã����ٶ�������3500*/
    if(MaxSpeed > 3500/*WheelMaxSpeed*/)//WheelMaxSpeed ��������ٶ�
    {
        Param = (float)3500 / MaxSpeed;
    }
	
	Speed[0] = tempSpeed[0] * Param;
	Speed[1] = tempSpeed[1] * Param;
	Speed[2] = tempSpeed[2] * Param;
	Speed[3] = tempSpeed[3] * Param;
	
}

/**
  * @brief  ��������
  * @param[in]  CurrentLimit
  * @param[out]	Speed	�ٶ�
  * @retval None
  */

void Chassis_powerLimit(M3508s_t *p_M3508s, float CurrentLimit)
{
	//float tempPowerMax = powerMax;
	float Param = 1;
	float MaxCurrent = 0;
	
	//����������
    for(uint8_t i = 0; i < 4; i++)
    {
        if(abs(p_M3508s[i].outCurrent) > MaxCurrent)
        {
            MaxCurrent = abs(p_M3508s[i].outCurrent);
        }
    }
	
	//��������
    if(MaxCurrent > CurrentLimit)
    {
        Param = CurrentLimit / MaxCurrent;
    }
	
	p_M3508s[0].outCurrent *= Param;
	p_M3508s[1].outCurrent *= Param;
	p_M3508s[2].outCurrent *= Param;
	p_M3508s[3].outCurrent *= Param;
	
	
}
