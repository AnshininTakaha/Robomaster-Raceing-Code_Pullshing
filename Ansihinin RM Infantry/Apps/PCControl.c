#include "PCControl.h"

pc_t pc;

void PC_MODE_Init(void)
{
    /*默认启动为云台跟随模式*/
    pc.PCMode = Mode_Cloud_PlatformFollowing;
    pc.NowStatus = 1;
}


