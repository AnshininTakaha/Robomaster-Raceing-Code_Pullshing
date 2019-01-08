/**
  ******************************************************************************
  * @file    Control_param.c
  * @author  Hare
  * @version V1.0
  * @date
  * @brief   ���Ʋ�����ʼ�������ӿ�
  ******************************************************************************
  */

#include "Control_param.h"


ControlStatus_t ControlStatus;

/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    ControlMode_paramInit
  * @brief   ��ʼ�����ӵ�ǰģʽ
  * @param   None
  * @author  ���� 
  * @Data    2018-10-19
 **/
/* -------------------------------- end -------------------------------- */

void ControlMode_paramInit(void)
{
	/*��ͨģʽ����*/ 
	ControlStatus.ControlMode = 0;
}


/**
  * @brief  ��ϼ��жϴ��� 
  * @param  None
  * @retval None
  */
void CombinatorialKey_Process(void)
{
	/*���һ��ʼ�Ȱ�����CTRL������SHIFT����ô���ж�Ϊ��ϼ�*/
	if(dr16_keyboard_isJumpKey(KEYBOARD_PRESSED_CTRL, KEY_FULL_MATCH) 
		|| dr16_keyboard_isJumpKey(KEYBOARD_PRESSED_SHIFT, KEY_FULL_MATCH))
	{
		/*��ϼ��ı�־λ��Ϊ1*/
		ControlStatus.isCombineKey = 1;
	}
	/*���û�а�CTRL������SHIFT���Ǿ;�û����ϼ�λ*/
	if(dr16_keyBorad.KeyStatus == KEYBOARD_PRESSED_NONE)
	{
		ControlStatus.isCombineKey = 0;
	}
}



/**
  * @brief  ��ȡ�Ƿ�����ϼ�
  * @param  None
  * @retval None
  * @Using 	��ʼ������PID��Ϣ
  */

uint8_t Control_isCombineKey(void)
{
	return ControlStatus.isCombineKey;
}


/**
  * @brief  ��ȡ��ǰģʽ��ʲô
  * @param  None
  * @retval None
  * @Using 	��ʼ������PID��Ϣ
  */

uint8_t Control_getMode(void)
{
    return ControlStatus.ControlMode;
}
