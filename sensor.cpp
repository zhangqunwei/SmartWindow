// Copyright (c) 张群伟. 
// All rights reserved.
//
// FileName: sensor.cpp
// Summary:  implementation of the CSensor class 
//
// Author: 张群伟    Version: 1.0    Date:2017/2/3
// History: 
//     Author:    Date:    Version:    Modification:
// 1.  张群伟     17/2/3   1.0         创建该模块 
//
/////////////////////////////////////////////////////////////////////////////

#include "sensor.h"

/////////////////////////////////////////////////////////////////////////////
// CSensor construction/destruction
CSensor::CSensor()
{
    pinMode(m_pin, INPUT);
    m_value = 0;
}

CSensor::~CSensor()
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
	m_value = analogRead(m_pin);
	return m_value;
}

// Function: detach()
// Description: 释放 m_pin 引脚
// Input: 无
// Output: 无
// Return: 无
void CSensor::detach()
{
    pinMode(m_pin, OUTPUT);
    digitalWrite(m_pin, LOW);
    pinMode(m_pin, INPUT);
}

//
// sensor.cpp end
//