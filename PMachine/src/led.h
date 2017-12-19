#ifndef __LED_CONF_H
#define __LED_CONF_H
#include "type_def.h"

/*Define bit operation, precondition should be setting IO port to output*/
#define PD0_out  PD_ODR_ODR0  
#define PD1_out  PD_ODR_ODR1  
#define PD2_out  PD_ODR_ODR2  
#define PD3_out  PD_ODR_ODR3  

/* LED Function Definition*/
void LED_Conf(void);
void LED_On(void);
void LED_Off(void);
void Delay(u32 nCount);
void Blink(u8 speed);

#endif




