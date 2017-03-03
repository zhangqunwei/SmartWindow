// Copyright (c) ��Ⱥΰ. 
// All rights reserved.
//
// FileName: smoke.cpp
// Summary:  implementation of the CSmoke class 
//
// Author: ��Ⱥΰ    Version: 1.0    Date: 2017/2/25
// History: 
//     Author:    Date:    Version:    Modification:
//  1. ��Ⱥΰ     17/2/25   1.0         ������ģ�� 
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
// Description: ��ʾ
// Input: ��
// Output: ��
// Return: ��
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
// Description: ���
// Input: ��
// Output: ��
// Return:	OPEN_WINDOW  ����	������й©
//			SHUT_WINDOW  �ش�	
int CSmoke::monitor()
{
	if (m_value > SMOKE_VALUE_MAX)
		return OPEN_WINDOW;
	else
		return KEEP_WINDOW;
}

// flame.cpp end
