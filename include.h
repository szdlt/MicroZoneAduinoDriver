/*****************************************************************************
 ** File			: include.h
 ** Author			: Zheng23
 ** Date			: 20150608			
 ** Function		: 锟斤拷锟斤拷头锟侥硷拷
/*****************************************************************************/
#ifndef _INCLUDE_H_
#define _INCLUDE_H_

//锟斤拷锟矫碉拷锟斤拷锟酵讹拷锟斤拷
//typedef unsigned char	bool;

typedef unsigned char	u8, U8, uint8, UINT8, BYTE;
typedef signed char		s8, S8, int8, INT8;

typedef unsigned short	u16, U16, uint16, UINT16, WORD;
typedef signed short	s16, S16, int16, INT16;

typedef unsigned long	u32, U32, uint32, UINT32, DWORD;
typedef signed long		s32, S32, int32, INT32;

//typedef unsigned short	string;

#define BIT(n) (1<<(n))

#define     BYTE0(n)            ((unsigned char)((unsigned short)(n)))
#define     BYTE1(n)            ((unsigned char)(((unsigned short)(n))>>8))
#define     BYTE2(n)            ((unsigned char)(((unsigned short)(((unsigned long)(n))>>8))>>8))
#define     BYTE3(n)            ((unsigned char)(((unsigned short)(((unsigned long)(n))>>16))>>8))

#define TRUE   1
#define FALSE  0
#define true   1
#define false  0
#define  BRK    4
#define  EN     5
#define  DIR    6
#define  PWM0   7
#define  ALAM   8
#define  SPEED  9
#define Mega2560   1

#include <Arduino.h>
#include "App.h"
#include "PS2X_lib.h"
#include "PCMsg.h"
#endif

