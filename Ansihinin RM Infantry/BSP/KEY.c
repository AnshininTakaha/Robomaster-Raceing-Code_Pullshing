#include  "KEY.h"


void DR16_Key_Whether_Process(uint16_t KeyStatus, Key_st *key)
{
	key->key_up_point = 0;
	key->key_dowm_point = 0;
	
	/*��ȡ��λ��ֵ*/
	key->key_Status = KeyStatus;

	
	if(key->key_Status != key->last_key_Status)
	{
		if(key->key_Status)//�а�����ֵ����Ϊ0��
		{
			key->key_up_point = key->key_Status;
		}
		else
		{
			key->key_dowm_point = key->last_key_Status;
			key->key_longpress_point = 0;
			key->pointing_time = 0;
		}
	}
	
	/*��������ֵ*/
	if(key->key_Status)
	{
		key->pointing_time++;
		if(key->pointing_time > 50)
		{
			key->key_longpress_point = key->key_Status;
			key->pointing_time = 0;
		}
	}
	
	key->last_key_Status = key->key_Status;
	
}









