// Copyright (c) 张群伟. 
// All rights reserved.
//
// FileName: raindrop.cpp
// Summary:  implementation of the CRaindrop class 
//
// Author: 张群伟    Version: 1.0    Date: 2017/2/25
// History: 
//     Author:    Date:    Version:    Modification:
//  1. 张群伟     17/2/25   1.0         创建该模块 
//
/////////////////////////////////////////////////////////////////////////////

#include "raindrop.h"

/////////////////////////////////////////////////////////////////////////////
// CRaindrop construction/destruction
CRaindrop::CRaindrop(int raindrop_pin)
{
	m_pin = raindrop_pin;
	pinMode(m_pin, INPUT);
}

CRaindrop::~CRaindrop()
{
	detach();
}

// Function: read()
// Description: 读取传感器的数据并返回
// Input: 无
// Output: m_value
// Return: m_value
int CSensor::read()
{
	m_value = digitalRead(m_pin);
	return m_value;
}

// Function: show()
// Description: 显示 感应板上没有水滴时，DO输出为高电平，开关指示灯灭 ，
//				滴上一滴水，DO输出为低电平，开关指示灯亮
// Input: 无
// Output: 无
// Return: 无
void CRaindrop::show()
{
	read();
	Serial.print("***|	Raindrop:  ");
	if (HIGH == m_value)
		Serial.print("No Rain!");
	else
		Serial.print("Rain!");

	Serial.println();
	delay(50);
}

// Function: monitor()
// Description: 监测
// Input: 无
// Output: 无
// Return:	SHUT_WINDOW   下雨
//			OPEN_WINDOW   没下雨
int CRaindrop::monitor()
{
	if (LOW == m_value)
		return SHUT_WINDOW;
	else
		return KEEP_WINDOW;
}

// raindrop.cpp end
