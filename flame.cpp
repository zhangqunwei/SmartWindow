// Copyright (c) 张群伟. 
// All rights reserved.
//
// FileName: flame.cpp
// Summary:  implementation of the CFlame class 
//
// Author: 张群伟    Version: 1.0    Date: 2017/1/10
// History: 
//     Author:    Date:    Version:    Modification:
//  1. 张群伟     17/1/10  1.0         创建该模块 
//
/////////////////////////////////////////////////////////////////////////////

#include "flame.h"

#define FLAME_VALUE_MAX  600

/////////////////////////////////////////////////////////////////////////////
// CFlame construction/destruction
CFlame::CFlame(int flame_pin) 
{
	m_pin = flame_pin;
	NULL;
}

CFlame::~CFlame()
{
  NULL;
}

// Function: show()
// Description: 显示
// Input: 无
// Output: 无
// Return: 无
void CFlame::show()
{
	read();
	Serial.print("***|	Flame:\t");
	Serial.print( m_value );
	Serial.print("\t");
	Serial.print("\t\tmax = 600");
	Serial.println();
	delay(50);
}

// Function: monitor()
// Description: 监测火焰值
// Input: 无
// Output: 无
// Return:	OPEN_WINDOW  开窗
//			SHUT_WINDOW  关窗
int CFlame::monitor()
{
	if (m_value > FLAME_VALUE_MAX)
		return OPEN_WINDOW;
	else
		return KEEP_WINDOW;
}

// flame.cpp end
