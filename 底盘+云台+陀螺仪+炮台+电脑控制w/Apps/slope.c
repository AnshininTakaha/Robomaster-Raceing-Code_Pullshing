#include "slope.h"





/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    slope_init
  * @brief  	斜坡缓冲默认初始化函数
  * @param   *slope: 斜波储存结构
**			 			scale: 大小
  * @author  口无 
  * @Data    2018-10-19
 **/
/* -------------------------------- end -------------------------------- */

void slope_init(slope_t *slope, int32_t scale)
{
  slope->count = 0;
  slope->scale = scale;
}



/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    slope_calculation
  * @brief   斜坡缓冲函数计算接口
  * @param   *slope: 斜波储存结构
  * @author  口无 
  * @Data    2018-10-19
 **/

float slope_calculation(slope_t *slope)
{
	if (slope->scale <= 0)
	{
		return 0;
	}
    
  
  if (slope->count++ >= slope->scale)
	{
		slope->count = slope->scale;
	}
    
  slope->out = slope->count / ((float)slope->scale);
  
	return slope->out;
}

