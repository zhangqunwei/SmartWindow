// Copyright (c) 张群伟. 
// All rights reserved.
//
// FileName: smoke.cpp
// Summary:  implementation of the CSmoke class 
//
// Author: 张群伟    Version: 1.0    Date: 2017/2/25
// History: 
//     Author:    Date:    Version:    Modification:
//  1. 张群伟     17/2/25   1.0         创建该模块 
//
/////////////////////////////////////////////////////////////////////////////

#include "smoke.h"

#define SMOKE_VALUE_MAX   150
/////////////////////////////////////////////////////////////////////////////
// CSmoke construction/destruction
CSmoke::CSmoke(int smoke_pin)
{
	m_pin = smoke_pin;
	pinMode(m_pin, INPUT);
}

CSmoke::~CSmoke()
{
	NULL;
}

// Function: show()
// Description: 显示
// Input: 无
// Output: 无
// Return: 无
void CSmoke::show()
{
	read();
	Serial.print("***|	Smoke:  ");
	Serial.print(m_value);
	Serial.print("\t");
	Serial.print("\t\tmax = 150 ");
	Serial.println();
	delay(50);
}

// Function: monitor()
// Description: 监测
// Input: 无
// Output: 无
// Return:	OPEN_WINDOW  开窗	有气体泄漏
//			SHUT_WINDOW  关窗	
int CSmoke::monitor()
{
	if (m_value > SMOKE_VALUE_MAX)
		return OPEN_WINDOW;
	else
		return KEEP_WINDOW;
}

// flame.cpp end
