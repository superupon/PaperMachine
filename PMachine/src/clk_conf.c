/**************************************************************************
 * File Name: clk_conf.c
 * Description : Clock Configuration Lib
 * Writer: supeurpon@126.com
 * Revision: 
****************************************************************************************/
#include "clk_conf.h"

/**************************************************************************
 * Function Name: Clk_conf 
 * Description: Clock configuration function
 * Input: No
 * Output: No
 * Return: No
 *************************************************************************/
void Clk_conf(void)
{
  CLK_CKDIVR&= (uint8_t)(~0x18); /*Clock Reset*/
  CLK_CKDIVR|= (uint8_t)0x00;    /*Clock is set to internal 16MHz High Speed Clock*/
}

