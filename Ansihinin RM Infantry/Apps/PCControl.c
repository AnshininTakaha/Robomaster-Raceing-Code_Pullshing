#include "PCControl.h"

pc_t pc;

void PC_MODE_Init(void)
{
    /*Ĭ������Ϊ��̨����ģʽ*/
    pc.PCMode = Mode_Cloud_PlatformFollowing;
    pc.NowStatus = 1;
}


