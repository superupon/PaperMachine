/********************************************************************************
 * File Name: type_def.h
 * Author£ºsuperupon@126.com
 * Revision: 
**********************************************************************************/
#ifndef __type_def_h
#define __type_def_h

/*Header file for control chip*/
#include "iostm8s103f3.h"
/*bool header file*/
#include "stdbool.h"
/*Interrupt file*/
#include "intrinsics.h"
/*Usually Data type definition*/
typedef unsigned char     uint8_t;
typedef unsigned short    uint16_t;
typedef unsigned long     uint32_t;

#define FlagStatus     bool
#define u8  uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define EnableInterrupt  __enable_interrupt() 
#endif

