#include "Analysis.h"


/*��Ӧ���ĸ�����*/
RM3508_st RM3508s[4];
/*��Ӧ��������̨*/
RM6623_st RM6623s[2];
/*��Ӧ�Ĳ������*/
RM2006_st RM2006s[1];

void Analysis_getinfo(CanRxMsg RxMessage)
{
	switch(RxMessage.StdId)
	{
		//wheel
		case 0x201://��Ӧ��Ϊ0������
			RM3508s[0].realAngle = (RxMessage.Data[0]<<8|RxMessage.Data[1]);
			RM3508s[0].realSpeed = (RxMessage.Data[2]<<8|RxMessage.Data[3]);
			RM3508s[0].realCurrent = (RxMessage.Data[4]<<8|RxMessage.Data[5]);
			RM3508s[0].realTempeture = (RxMessage.Data[6]);
			RM3508s[0].UpdateFlag = 1;
			RM3508s[0].UpdateFrame++;
		break;
		
		case 0x202://��Ӧ��Ϊ1������
			RM3508s[1].realAngle = (RxMessage.Data[0]<<8|RxMessage.Data[1]);
			RM3508s[1].realSpeed = (RxMessage.Data[2]<<8|RxMessage.Data[3]);
			RM3508s[1].realCurrent = (RxMessage.Data[4]<<8|RxMessage.Data[5]);
			RM3508s[1].realTempeture = (RxMessage.Data[6]);
			RM3508s[1].UpdateFlag = 1;
			RM3508s[1].UpdateFrame++;
		break;
		
		case 0x203://��ӦΪ2������
			RM3508s[2].realAngle = (RxMessage.Data[0]<<8|RxMessage.Data[1]);
			RM3508s[2].realSpeed = (RxMessage.Data[2]<<8|RxMessage.Data[3]);
			RM3508s[2].realCurrent = (RxMessage.Data[4]<<8|RxMessage.Data[5]);
			RM3508s[2].realTempeture = (RxMessage.Data[6]);
			RM3508s[2].UpdateFlag = 1;
			RM3508s[2].UpdateFrame++;
		break;
		
		case 0x204://��ӦΪ3������
			RM3508s[3].realAngle = (RxMessage.Data[0]<<8|RxMessage.Data[1]);
			RM3508s[3].realSpeed = (RxMessage.Data[2]<<8|RxMessage.Data[3]);
			RM3508s[3].realCurrent = (RxMessage.Data[4]<<8|RxMessage.Data[5]);
			RM3508s[3].realTempeture = (RxMessage.Data[6]);
			RM3508s[3].UpdateFlag = 1;
			RM3508s[3].UpdateFrame++;
		break;
		
		//platform
		case 0x205://��Ӧ��Yaw����̨
			RM6623s[0].realAngle = (RxMessage.Data[0]<<8|RxMessage.Data[1]);
			RM6623s[0].realCurrent = (RxMessage.Data[2]<<8|RxMessage.Data[3]);
			RM6623s[0].feedbackCurrent = (RxMessage.Data[4]<<8|RxMessage.Data[5]);
			M6623_ZeroDealing_platform(0);
			RM6623s[0].totalAngle = RM6623s[0].realAngle +(PLATFORM_A_TURN*RM6623s[0].turnCount);
//			RM6623s[0].infoUpdateFlag = 1;
//			RM6623s[0].infoUpdateFrame++;
		break;
		
		case 0x206://��Ӧ��Pitch����̨
			RM6623s[1].realAngle = (RxMessage.Data[0]<<8|RxMessage.Data[1]);
			RM6623s[1].realCurrent = (RxMessage.Data[2]<<8|RxMessage.Data[3]);
			RM6623s[1].feedbackCurrent = (RxMessage.Data[4]<<8|RxMessage.Data[5]);
			M6623_ZeroDealing_platform(1);
			RM6623s[1].totalAngle = RM6623s[1].realAngle +(PLATFORM_A_TURN*RM6623s[1].turnCount);
//			RM6623s[1].infoUpdateFlag = 1;
//			RM6623s[1].infoUpdateFrame++;
		break;
		
		case 0x207://��Ӧ�������
			RM2006s[0].realAngle = (RxMessage.Data[0]<<8|RxMessage.Data[1]);
			RM2006s[0].realSpeed = (RxMessage.Data[2]<<8|RxMessage.Data[3]);
			RM2006s[0].realTorque = (RxMessage.Data[4]<<8|RxMessage.Data[5]);
			M2006_ZeroDealing_platform(0);
			RM2006s[0].totalAngle = RM2006s[0].realAngle +(UNDULATION_A_TURN*RM2006s[0].turnCount);
//			RM2006s[0].infoUpdateFlag = 1;
//			RM2006s[0].infoUpdateFrame++;
	}
}


/*��ƫ����*/
void M6623_ZeroDealing_platform(int8_t id)
{
	if(RM6623s[id].realAngle - RM6623s[id].lastAngle < -6000)
	{
		RM6623s[id].turnCount++;
	}
	
	if(RM6623s[id].lastAngle - RM6623s[id].realAngle < -6000)
	{
		RM6623s[id].turnCount--;
	}
	RM6623s[id].lastAngle =  RM6623s[id].realAngle;
	
}

void M2006_ZeroDealing_platform(int8_t id)
{
	if(RM2006s[id].realAngle - RM2006s[id].lastAngle < -6000)
	{
		RM2006s[id].turnCount++;
	}
	if(RM2006s[id].lastAngle - RM2006s[id].realAngle < -6000)
	{
		RM2006s[id].turnCount--;
	}
	RM2006s[id].lastAngle =  RM2006s[id].realAngle;
}


