#include "shoot.h"

shootGun_t Gun;

/*步兵对应的数值*/

const uint16_t Shoot_HeatMax[4] = { 120,120,240,480,};		//每级步兵热量上限

const uint16_t Shoot_Freq[4] = { 6,6,7,8,};		//每级步兵射击频率

const uint16_t deltaHeat[3] = { 18, 30, 28, };		//不同射速热量增长
const uint16_t FricSpeed[3] = {  1600, 2000, 2000, };		//不同射速摩擦轮转速




/**
  * @brief  射击参数初始化
  * @param[in]  None
  * @retval None
  */
void Shoot_Init(void)
{
    /*初始化定义各种标志位*/
    Gun.fricReady = 0;
    Gun.shootFlag = 0;
    Gun.heatOverflowFlag = 0;
    /*初始化速度*/
    Gun.fricSpeedLevel = FricSpeedLevel_10MPS;
    Gun.fricTargetSpeedRaw = FricSpeed[Gun.fricSpeedLevel];


    /*射击频率初始化（计算1s子弹的射击的频率和多少）*/
    Gun.shootFreq = Shoot_Freq[1];

    /*激光初始化*/
    Laser_Init();

    //摩擦轮90M/90/20000=50HZ
    TIM12_PWMOutput(89, 19999,1000);


    //拨弹电机pid
    PositionPID_paraReset(&M2006s[0].pid_speed, 1.5f, 0.04f, 0.0f, 8000, 2000);
    PositionPID_paraReset(&M2006s[0].pid_angle, 0.3f, 0.0f, 0.8f, 4000, 500);

}


/**
  * @brief  设置摩擦轮电机速度
  * @param  speed 	电机速度，范围1000~2000
  * @retval None
  */
void fricMotor_setSpeed(uint16_t speed)
{
    /*速度限幅*/
    if(speed < FRICMOTOR_SPEEDMIN) speed = FRICMOTOR_SPEEDMIN;
    if(speed > FRICMOTOR_SPEEDMAX) speed = FRICMOTOR_SPEEDMAX;


    TIM_SetComparex[0](TIM12, speed);
    TIM_SetComparex[1](TIM12, speed);


}

/**
  * @brief  摩擦轮开
  * @param[in]  None
  * @retval None
  */
void friction_turnOn(void)
{
    static uint16_t temp = 1000;
    /*使能摩擦轮*/
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
  * @brief  关摩擦轮
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
  * @brief  射击处理
  * @param[in]  None
  * @retval None
  */
void Shoot_processing(void)
{
    /*定义一个储存射击频率的结构体*/
    static uint16_t FCount = 0;
    int begin_process = 1;
    if(ControlStatus.ControlMode == ControlMode_OFF ||ControlStatus.SpecialMode == SpecialMode_Supply)
    {
				
        /*圈数清零之后以上一次的角度*/
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

    /*射击频率过快保护（防止各种情况）*/
    if(FCount++ > 100/Gun.shootFreq)
    {
        Gun.shootReady = 1;
        FCount = Gun.shootFreq;

    }

    /*如果M20006的子弹装载标志位置1 且 枪的射击标志位置1*/
    if(M2006s[0].loadFinish && Gun.shootFlag)
    {

        /*通过后，先检查电机有没有打开*/
        if(!Gun.fricReady)
        {
            /*重新打开摩擦轮电机*/
            friction_turnOn();
        }

        else
        {
            /*设置摩擦轮的速度，然后进行拨弹*/
            fricMotor_setSpeed(Gun.fricTargetSpeedRaw);
            /*这里是还有一层裁判系统的判断的这里先不加上去*/
            /*&& Judge_PowerHeatData.infoUpdateFlag)*/
            /*成功的话就会进行拨弹*/
            if(!Gun.heatOverflowFlag && Gun.shootReady)
            {
                //没超热量则拨弹射击
                M2006s[0].targetAngle += M2006_LOADANGLE;
                FCount = 0;
                Gun.shootReady = 0;
//							Judge_PowerHeatData.infoUpdateFlag = 0;
            }
            /*枪的射击标志位置为0*/
            Gun.shootFlag = 0;
        }
    }


    /*如果没有离线*/
    if(M2006s[0].offLineFlag == 0)
    {
        /*定义一个卡子弹的标志位*/
        static uint8_t M2006s_blocking = 0;
        /*计算卡子弹的时间*/
        static int blockCounter = 0;
        /*载入成功标志位*/
        M2006s[0].loadFinish = 0;

        /*双环计算*/
        /*位置PID计算（外环）*/
        int M2006s_PIDOut = Position_PID(&M2006s[0].pid_angle, M2006s[0].targetAngle, M2006s[0].totalAngle);
        /*速度PID计算（内环）*/
        M2006s[0].outCurrent = Position_PID(&M2006s[0].pid_speed, M2006s_PIDOut, M2006s[0].realSpeed);
        /*卡弹处理*/
        /*卡弹的时候因为转盘会被卡住，这个时候真实值和目标值的差值会非常的大，所以会导致计算出来的outCurrent非常的大*/
        /*同时因为卡弹的问题这个时候电机的速度会非常的小，然后卡弹计时如果到达50的话，就判断为*/
        if(abs(M2006s[0].outCurrent)>6200 && abs(M2006s[0].realSpeed) < 50 && blockCounter++>50)
        {
            if(!M2006s_blocking)
            {
                /*反转*/
                M2006s[0].targetAngle -= M2006_LOADANGLE*2;
                M2006s_blocking = 1;
            }

        }


        /*拨弹完毕*/
        /*如果拨弹正常（机械差值正常，说明我确实的拨了一个弹丸）*/
        if(abs(M2006s[0].pid_angle.err) < 8000)
        {
            /*卡弹的所有的数值清零*/
            M2006s_blocking = 0;
            blockCounter = 0;

            /*拨弹完成*/
            M2006s[0].loadFinish = 1;
        }

        if(M2006s[0].turnCount > 100)
        {
            M2006s[0].targetAngle = M2006s[0].targetAngle - ((M2006s[0].turnCount)*8192);
            M2006s[0].turnCount = 0;
        }

    }


    //清标志位
    M2006s[0].infoUpdateFlag = 0;

}


