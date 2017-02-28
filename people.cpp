// Copyright (c) 张群伟. 
// All rights reserved.
//
// FileName: people.cpp
// Summary:  implementation of the CPeople class 
//
// Author: 张群伟    Version: 1.0    Date: 2017/1/10
// History: 
//     Author:    Date:    Version:    Modification:
//  1. 张群伟     17/1/10  1.0         创建该模块 
//
/////////////////////////////////////////////////////////////////////////////

#include "people.h"

/////////////////////////////////////////////////////////////////////////////
// CPeople construction/destruction
CPeople::CPeople(int Pin)
{
	m_pin = Pin;
	pinMode(m_pin, INPUT);
}

CPeople::~CPeople()
{
	detach();
}
// hello

// Function: show()
// Description: 显示
// Input: 无
// Output: 无
// Return: 无
void CPeople::show()
{
	Serial.begin(9600);
	Serial.print("***|	People:\t");
	if (SHUT_WINDOW == monitor())
		Serial.print("Danger!");
	else
		Serial.print("Safety!");

	Serial.println();
	delay(50);
}

// Function: monitor()
// Description: 监测是否有人闯入
// Input: 无
// Output: 无
// Return:	SHUT_WINDOW   有人
//			OPEN_WINDOW   没人
int CPeople::monitor()
{
	if (true == digitalRead(m_pin))
		return SHUT_WINDOW;
	else
		return KEEP_WINDOW;
}

// people.cpp end
