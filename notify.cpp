// Copyright (c) 张群伟. 
// All rights reserved.
//
// FileName: notify.cpp
// Summary:  implementation of the CNotify class 
//
// Author: 张群伟    Version: 1.0    Date:2017/2/25
// History: 
//     Author:    Date:    Version:    Modification:
// 1.  张群伟     17/2/25   1.0         创建该模块 
//
/////////////////////////////////////////////////////////////////////////////

#include "notify.h"

/////////////////////////////////////////////////////////////////////////////
// CNotify construction/destruction
CNotify::CNotify(int Pin)
{
	m_pin = Pin;
	pinMode(m_pin, OUTPUT);
}

CNotify::~CNotify()
{
	detach();
}

// Function: notify()
// Description: 报警,从m_pin 引脚输出脉宽为pulse_width脉冲个数为pulse_num的脉冲
// Input:	pulse_width	脉冲宽度
//			pulse_num	脉冲个数
// Output: 无
// Return: 无
void CNotify::notify(unsigned long pulse_width, int pulse_num)
{
	int count = pulse_num;
	while (count--)
	{
		digitalWrite(m_pin, HIGH);
		delay(pulse_width);
		digitalWrite(m_pin, LOW);
		delay(pulse_width);
	}
}

// Function: detach()
// Description: 释放 m_pin 引脚
// Input: 无
// Output: 无
// Return: 无
void CNotify::detach()
{
	pinMode(m_pin, OUTPUT);
	digitalWrite(m_pin, LOW);
	pinMode(m_pin, INPUT);
}

//
// notify.cpp end
//