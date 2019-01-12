#include "CurrentSetting.h"


void Chassis_CurrentSetting(int16_t I1,int16_t I2,int16_t I3,int16_t I4)
{
    uint8_t RM3508_Sending[8];

    RM3508_Sending[0] = I1 >> 8;
    RM3508_Sending[1] = I1;

    RM3508_Sending[2] = I2 >> 8;
    RM3508_Sending[3] = I2;

    RM3508_Sending[4] = I3 >> 8;
    RM3508_Sending[5] = I3;

    RM3508_Sending[6] = I4 >> 8;
    RM3508_Sending[7] = I4;

    CAN_SendData(CAN1,CAN_ID_STD,0x200,RM3508_Sending);
}

void Cloud_And_Emitter_CurrentSetting(int16_t I_Yaw, int16_t I_Pitch, int16_t I_Emitter, int16_t OVER)
{
    uint8_t Cloud_Sending[8];

    Cloud_Sending[0] = I_Yaw >> 8;
    Cloud_Sending[1] = I_Yaw;

    Cloud_Sending[2] = I_Pitch >> 8;
    Cloud_Sending[3] = I_Pitch;

    Cloud_Sending[4] = I_Emitter >> 8;
    Cloud_Sending[5] = I_Emitter;

    Cloud_Sending[6] = OVER >> 8;
    Cloud_Sending[7] = OVER;

    CAN_SendData(CAN1,CAN_ID_STD,0x1FF,Cloud_Sending);
}


void CAN_Cylinder(void)
{
    int setting_point;
    if(DR16.rc.s_left == 1)
    {
        setting_point = 3;
    }
    else
    {
        setting_point = 0;
    }
    uint8_t Sending[8];

    Sending[0] = setting_point;
    Sending[1] = 0;

    Sending[2] = 0;
    Sending[3] = 0;

    Sending[4] = 0;
    Sending[5] = 0;

    Sending[6] = 0;
    Sending[7] = 0;

    CAN_SendData(CAN1,CAN_ID_STD,0x500,Sending);
}