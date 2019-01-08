#include "PC_processing.h"

slope_t fb_slope = SLOPE_GEN_DAFAULT;
slope_t lr_slope = SLOPE_GEN_DAFAULT;

/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    PC_WASD_Dealing
  * @brief   PC上面的WASD按键处理
  * @param   None 
  * @author  口无 
  * @Data    2018-10-19
 **/
/* -------------------------------- end -------------------------------- */

/*这里的slope_calculation其实相当于根据按键时间来提升他的速度（有最高值）*/
/*根据按键时间的长短来决定加速强度*/
void MOPC_WASD_Dealing(rocker_t *rocker)
{
	/*WS*/
	if(dr16_keyboard_isPressedKey(KEYBOARD_PRESSED_W, KEY_HAVE_MATCH))
			{
				rocker->x =- Chassis.speedlimit *slope_calculation(&fb_slope);
			}
			else if(dr16_keyboard_isPressedKey(KEYBOARD_PRESSED_S, KEY_HAVE_MATCH))
			{
				rocker->x =  Chassis.speedlimit *slope_calculation(&fb_slope);
			}
			else
			{
				rocker->x = 0;
				slope_init(&fb_slope, KEY_ACC_TIME/10);
			}
			
	/*AD*/		
	if(dr16_keyboard_isPressedKey(KEYBOARD_PRESSED_D, KEY_HAVE_MATCH))
			{
				rocker->y = Chassis.speedlimit *slope_calculation(&lr_slope);
			}
			else if(dr16_keyboard_isPressedKey(KEYBOARD_PRESSED_A, KEY_HAVE_MATCH))
			{
				rocker->y = -Chassis.speedlimit *slope_calculation(&lr_slope);
			}
			else
			{
				rocker->y = 0;
				slope_init(&lr_slope, KEY_ACC_TIME/10);
			}
			
}

void MOPC_QE_Dealing(rocker_t *rocker)
{
	
	/*QE*/
	rocker->degrees = -(dr16_data.keyBoard.press_Q *Chassis.speedlimit)+ (dr16_data.keyBoard.press_E *Chassis.speedlimit);
//	printf("dr16_data.keyBoard.press_Q = %d\r\n",dr16_data.keyBoard.press_Q);

}





