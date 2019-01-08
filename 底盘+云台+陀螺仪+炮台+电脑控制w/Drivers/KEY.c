#include "KEY.h"

key_t userKeyList[KEY_COUNT];



/**
  * @brief  按键初始化
  * @param  None
  * @retval None
  */
void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure; //定义结构体
    RCC_AHB1PeriphClockCmd(KEY_GPIO_CLK, ENABLE); 	//初始化GPIO时钟

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;   //输入模式
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	//上拉
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; //速度选择
    GPIO_InitStructure.GPIO_Pin   = KEY_PIN;

    GPIO_Init(KEY_GPIO_PORT, &GPIO_InitStructure);

}
/**
  * @brief  按键更新刷新
  * @param  None
  * @retval None
  */
void Key_point(void)
{
    userKeyList[0].lastKeyStatus = userKeyList[0].KeyStatus;//把前一个按键的情况赋值给现在这个按键的情况的值
    userKeyList[0].KeyStatus = GPIO_ReadInputDataBit (KEY_GPIO_PORT,KEY_PIN);//读取他的电平的高低PD10
}

/**
  * @brief  扫描有用的按键
  * @param  None
  * @retval None
  */
void Key_Scan(void)
{
    Key_point();
    userKeyList[0].keyPressedJump = 0;
    userKeyList[0].keyReleaseJump = 0;

    if (userKeyList[0].KeyStatus != userKeyList[0].lastKeyStatus)
    {
        if(userKeyList[0].KeyStatus)
            userKeyList[0].keyReleaseJump = 1;//按键前半段（按下）
        else
            userKeyList[0].keyPressedJump = 1;//按键后半段（返跳）
    }
}
