/**************************************************************************
���ߣ�ƽ��С��֮��
�Ա����̣�http://shop114407458.taobao.com/
**************************************************************************/

#ifndef __DATA_PRTOCOL_H
#define __DATA_PRTOCOL_H

#include "Users.h"

extern unsigned char DataScope_OutPut_Buffer[42];	   //������֡���ݻ�����


void DataScope_Get_Channel_Data(float Data,unsigned char Channel);    // дͨ�������� ������֡���ݻ�����
void DataScope(void);
unsigned char DataScope_Data_Generate(unsigned char Channel_Number);  // ����֡�������ɺ���


#endif



