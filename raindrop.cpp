// Copyright (c) ��Ⱥΰ. 
// All rights reserved.
//
// FileName: raindrop.cpp
// Summary:  implementation of the CRaindrop class 
//
// Author: ��Ⱥΰ    Version: 1.0    Date: 2017/2/25
// History: 
//     Author:    Date:    Version:    Modification:
//  1. ��Ⱥΰ     17/2/25   1.0         ������ģ�� 
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

// Function: show()
// Description: ��ʾ ��Ӧ����û��ˮ��ʱ��DO���Ϊ�ߵ�ƽ������ָʾ���� ��
//				����һ��ˮ��DO���Ϊ�͵�ƽ������ָʾ����
// Input: ��
// Output: ��
// Return: ��
void CRaindrop::show()
{
	Serial.begin(9600);
	Serial.print("***|	Raindrop:  ");
	if (HIGH == digitalRead(m_pin))
		Serial.print("No Rain!");
	else
		Serial.print("Rain!");

	Serial.println();
	delay(50);
}

// Function: monitor()
// Description: ���
// Input: ��
// Output: ��
// Return:	SHUT_WINDOW   ����
//			OPEN_WINDOW   û����
int CRaindrop::monitor()
{
	if (true == digitalRead(m_pin))
		return SHUT_WINDOW;
	else
		return KEEP_WINDOW;
}

// raindrop.cpp end
