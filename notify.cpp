// Copyright (c) ��Ⱥΰ. 
// All rights reserved.
//
// FileName: notify.cpp
// Summary:  implementation of the CNotify class 
//
// Author: ��Ⱥΰ    Version: 1.0    Date:2017/2/25
// History: 
//     Author:    Date:    Version:    Modification:
// 1.  ��Ⱥΰ     17/2/25   1.0         ������ģ�� 
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
// Description: ����,��m_pin �����������Ϊpulse_width�������Ϊpulse_num������
// Input:	pulse_width	������
//			pulse_num	�������
// Output: ��
// Return: ��
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
// Description: �ͷ� m_pin ����
// Input: ��
// Output: ��
// Return: ��
void CNotify::detach()
{
	pinMode(m_pin, OUTPUT);
	digitalWrite(m_pin, LOW);
	pinMode(m_pin, INPUT);
}

//
// notify.cpp end
//