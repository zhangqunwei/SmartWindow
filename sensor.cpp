// Copyright (c) ��Ⱥΰ. 
// All rights reserved.
//
// FileName: sensor.cpp
// Summary:  implementation of the CSensor class 
//
// Author: ��Ⱥΰ    Version: 1.0    Date:2017/2/3
// History: 
//     Author:    Date:    Version:    Modification:
// 1.  ��Ⱥΰ     17/2/3   1.0         ������ģ�� 
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
// Description: ��ȡ�����������ݲ�����
// Input: ��
// Output: m_value
// Return: m_value
int CSensor::read()
{
	m_value = analogRead(m_pin);
	return m_value;
}

// Function: detach()
// Description: �ͷ� m_pin ����
// Input: ��
// Output: ��
// Return: ��
void CSensor::detach()
{
    pinMode(m_pin, OUTPUT);
    digitalWrite(m_pin, LOW);
    pinMode(m_pin, INPUT);
}

//
// sensor.cpp end
//