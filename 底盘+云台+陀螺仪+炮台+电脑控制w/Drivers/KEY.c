#include "KEY.h"

key_t userKeyList[KEY_COUNT];



/**
  * @brief  ������ʼ��
  * @param  None
  * @retval None
  */
void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure; //����ṹ��
    RCC_AHB1PeriphClockCmd(KEY_GPIO_CLK, ENABLE); 	//��ʼ��GPIOʱ��

    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;   //����ģʽ
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;	//����
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz; //�ٶ�ѡ��
    GPIO_InitStructure.GPIO_Pin   = KEY_PIN;

    GPIO_Init(KEY_GPIO_PORT, &GPIO_InitStructure);

}
/**
  * @brief  ��������ˢ��
  * @param  None
  * @retval None
  */
void Key_point(void)
{
    userKeyList[0].lastKeyStatus = userKeyList[0].KeyStatus;//��ǰһ�������������ֵ��������������������ֵ
    userKeyList[0].KeyStatus = GPIO_ReadInputDataBit (KEY_GPIO_PORT,KEY_PIN);//��ȡ���ĵ�ƽ�ĸߵ�PD10
}

/**
  * @brief  ɨ�����õİ���
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
            userKeyList[0].keyReleaseJump = 1;//����ǰ��Σ����£�
        else
            userKeyList[0].keyPressedJump = 1;//�������Σ�������
    }
}
