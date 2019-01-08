#include "shoot.h"

shootGun_t Gun;

/*������Ӧ����ֵ*/

const uint16_t Shoot_HeatMax[4] = { 120,120,240,480,};		//ÿ��������������

const uint16_t Shoot_Freq[4] = { 6,6,7,8,};		//ÿ���������Ƶ��

const uint16_t deltaHeat[3] = { 18, 30, 28, };		//��ͬ������������
const uint16_t FricSpeed[3] = {  1600, 2000, 2000, };		//��ͬ����Ħ����ת��




/**
  * @brief  ���������ʼ��
  * @param[in]  None
  * @retval None
  */
void Shoot_Init(void)
{
    /*��ʼ��������ֱ�־λ*/
    Gun.fricReady = 0;
    Gun.shootFlag = 0;
    Gun.heatOverflowFlag = 0;
    /*��ʼ���ٶ�*/
    Gun.fricSpeedLevel = FricSpeedLevel_10MPS;
    Gun.fricTargetSpeedRaw = FricSpeed[Gun.fricSpeedLevel];


    /*���Ƶ�ʳ�ʼ��������1s�ӵ��������Ƶ�ʺͶ��٣�*/
    Gun.shootFreq = Shoot_Freq[1];

    /*�����ʼ��*/
    Laser_Init();

    //Ħ����90M/90/20000=50HZ
    TIM12_PWMOutput(89, 19999,1000);


    //�������pid
    PositionPID_paraReset(&M2006s[0].pid_speed, 1.5f, 0.04f, 0.0f, 8000, 2000);
    PositionPID_paraReset(&M2006s[0].pid_angle, 0.3f, 0.0f, 0.8f, 4000, 500);

}


/**
  * @brief  ����Ħ���ֵ���ٶ�
  * @param  speed 	����ٶȣ���Χ1000~2000
  * @retval None
  */
void fricMotor_setSpeed(uint16_t speed)
{
    /*�ٶ��޷�*/
    if(speed < FRICMOTOR_SPEEDMIN) speed = FRICMOTOR_SPEEDMIN;
    if(speed > FRICMOTOR_SPEEDMAX) speed = FRICMOTOR_SPEEDMAX;


    TIM_SetComparex[0](TIM12, speed);
    TIM_SetComparex[1](TIM12, speed);


}

/**
  * @brief  Ħ���ֿ�
  * @param[in]  None
  * @retval None
  */
void friction_turnOn(void)
{
    static uint16_t temp = 1000;
    /*ʹ��Ħ����*/
    fricMotor_setSpeed(temp);
    temp+=20;

    if(temp > Gun.fricTargetSpeedRaw)
    {
        fricMotor_setSpeed(Gun.fricTargetSpeedRaw);
        temp = 1000;
        Gun.fricReady = 1;
        Gun.shootFlag = 0;
    }


    // LASER_ON();
}

/**
  * @brief  ��Ħ����
  * @param[in]  None
  * @retval None
  */
void friction_turnOff(void)
{
    fricMotor_setSpeed(1000);
    Gun.fricReady = 0;
    Gun.shootFlag = 0;
//		M2006s[0].turnCount = 0;
//    M2006s[0].targetAngle = M2006s[0].totalAngle = M2006s[0].realAngle;
    //LASER_OFF();
}


/**
  * @brief  �������
  * @param[in]  None
  * @retval None
  */
void Shoot_processing(void)
{
    /*����һ���������Ƶ�ʵĽṹ��*/
    static uint16_t FCount = 0;
    int begin_process = 1;
    if(ControlStatus.ControlMode == ControlMode_OFF ||ControlStatus.SpecialMode == SpecialMode_Supply)
    {
				
        /*Ȧ������֮������һ�εĽǶ�*/
        M2006s[0].turnCount = 0;
        M2006s[0].targetAngle = M2006s[0].totalAngle = M2006s[0].realAngle;
        
				return;
    }
		
//		if(dr16_data.offLineFlag == 1)
//		{
//				M2006s[0].turnCount = 0;
//        M2006s[0].targetAngle = M2006s[0].totalAngle = M2006s[0].realAngle;
//        return;
//		}
//		printf("got it");
    if(begin_process == 1)
    {
			if(!dr16_data.offLineFlag)
			{
        begin_process = 0;
        M2006s[0].loadFinish =1;
			}
		}
//   M2006s[0].loadFinish =1;

    /*���Ƶ�ʹ��챣������ֹ���������*/
    if(FCount++ > 100/Gun.shootFreq)
    {
        Gun.shootReady = 1;
        FCount = Gun.shootFreq;

    }

    /*���M20006���ӵ�װ�ر�־λ��1 �� ǹ�������־λ��1*/
    if(M2006s[0].loadFinish && Gun.shootFlag)
    {

        /*ͨ�����ȼ������û�д�*/
        if(!Gun.fricReady)
        {
            /*���´�Ħ���ֵ��*/
            friction_turnOn();
        }

        else
        {
            /*����Ħ���ֵ��ٶȣ�Ȼ����в���*/
            fricMotor_setSpeed(Gun.fricTargetSpeedRaw);
            /*�����ǻ���һ�����ϵͳ���жϵ������Ȳ�����ȥ*/
            /*&& Judge_PowerHeatData.infoUpdateFlag)*/
            /*�ɹ��Ļ��ͻ���в���*/
            if(!Gun.heatOverflowFlag && Gun.shootReady)
            {
                //û�������򲦵����
                M2006s[0].targetAngle += M2006_LOADANGLE;
                FCount = 0;
                Gun.shootReady = 0;
//							Judge_PowerHeatData.infoUpdateFlag = 0;
            }
            /*ǹ�������־λ��Ϊ0*/
            Gun.shootFlag = 0;
        }
    }


    /*���û������*/
    if(M2006s[0].offLineFlag == 0)
    {
        /*����һ�����ӵ��ı�־λ*/
        static uint8_t M2006s_blocking = 0;
        /*���㿨�ӵ���ʱ��*/
        static int blockCounter = 0;
        /*����ɹ���־λ*/
        M2006s[0].loadFinish = 0;

        /*˫������*/
        /*λ��PID���㣨�⻷��*/
        int M2006s_PIDOut = Position_PID(&M2006s[0].pid_angle, M2006s[0].targetAngle, M2006s[0].totalAngle);
        /*�ٶ�PID���㣨�ڻ���*/
        M2006s[0].outCurrent = Position_PID(&M2006s[0].pid_speed, M2006s_PIDOut, M2006s[0].realSpeed);
        /*��������*/
        /*������ʱ����Ϊת�̻ᱻ��ס�����ʱ����ʵֵ��Ŀ��ֵ�Ĳ�ֵ��ǳ��Ĵ����Իᵼ�¼��������outCurrent�ǳ��Ĵ�*/
        /*ͬʱ��Ϊ�������������ʱ�������ٶȻ�ǳ���С��Ȼ�󿨵���ʱ�������50�Ļ������ж�Ϊ*/
        if(abs(M2006s[0].outCurrent)>6200 && abs(M2006s[0].realSpeed) < 50 && blockCounter++>50)
        {
            if(!M2006s_blocking)
            {
                /*��ת*/
                M2006s[0].targetAngle -= M2006_LOADANGLE*2;
                M2006s_blocking = 1;
            }

        }


        /*�������*/
        /*���������������е��ֵ������˵����ȷʵ�Ĳ���һ�����裩*/
        if(abs(M2006s[0].pid_angle.err) < 8000)
        {
            /*���������е���ֵ����*/
            M2006s_blocking = 0;
            blockCounter = 0;

            /*�������*/
            M2006s[0].loadFinish = 1;
        }

        if(M2006s[0].turnCount > 100)
        {
            M2006s[0].targetAngle = M2006s[0].targetAngle - ((M2006s[0].turnCount)*8192);
            M2006s[0].turnCount = 0;
        }

    }


    //���־λ
    M2006s[0].infoUpdateFlag = 0;

}


