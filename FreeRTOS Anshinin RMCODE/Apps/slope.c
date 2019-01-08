#include "slope.h"

slope_st fb_slope = SLOPE_DAFAULT;
slope_st lr_slope = SLOPE_DAFAULT;
//slope_st qe_slope = SLOPE_DAFAULT;


/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    slope_calculation
  * @brief   б�����㺯��
  * @param   slope: [����/��] 
  * @author  ���� 
  * @Data    2018-11-19
 **/
/* -------------------------------- end -------------------------------- */

void slope_init(slope_st *slope, int32_t scale)
{
  slope->count = 0;
  slope->scale = scale;
}


/* -------------------------------- begin  -------------------------------- */
/**
  * @Name    slope_calculation
  * @brief   б�����㺯��
  * @param   slope: [����/��] 
  * @author  ���� 
  * @Data    2018-11-19
 **/
/* -------------------------------- end -------------------------------- */

float slope_calculation(slope_st *slope)
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
