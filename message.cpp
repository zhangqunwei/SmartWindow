// Copyright (c) ��Ⱥΰ. 
// All rights reserved.
//
// FileName: Message.cpp
// Summary:  implementation of the CMessage class 
//
// Author: ��Ⱥΰ    Version: 1.0    Date:2017/2/25
// History: 
//     Author:    Date:    Version:    Modification:
// 1.  ��Ⱥΰ     17/2/25   1.0         ������ģ�� 
//
/////////////////////////////////////////////////////////////////////////////

#include "Message.h"

/////////////////////////////////////////////////////////////////////////////
// CMessage construction/destruction
CMessage::CMessage()
{
	rx_buffer = 'n';
}

CMessage::CMessage(int Pin)
{
	m_pin = Pin;
	pinMode(m_pin, OUTPUT);
}

CMessage::~CMessage()
{
	detach();
}

// Function: Message()
// Description: ����,��m_pin �����������Ϊpulse_width�������Ϊpulse_num������
// Input:	pulse_width	������
//			pulse_num	�������
// Output: ��
// Return: ��
void CMessage::pulse(unsigned long pulse_width, int pulse_num)
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
void CMessage::detach()
{
	pinMode(m_pin, OUTPUT);
	digitalWrite(m_pin, LOW);
	pinMode(m_pin, INPUT);
}

// Function: monitor()
// Description: ��⴮����Ϣ���Ƿ��п������߹ش�����
// Input: ��
// Output: ��
// Return:	s	shut �ش�
//			o	open ����
//			n   NULL ��
char CMessage::monitor()
{
	if (Serial.available() > 0)
	{ // ������Ϣ���浽������
		rx_buffer = Serial.read();
	}
	Serial.print("***|  send:\t");
	Serial.print(rx_buffer);
	Serial.println();

	if ((rx_buffer == 's') && (WindowState == OPEN_WINDOW))
	{ // shut �ش�
		Serial.print("***|  ");
		Serial.print("Will shut window!"); 
		Serial.println();
		rx_buffer = 'N';
		return 's';
	}
	else if ((rx_buffer == 'o') && (WindowState == SHUT_WINDOW))
	{ // open ����
		Serial.print("***|  ");
		Serial.print("Will open window!");
		Serial.println();
		rx_buffer = 'N';
		return 'o';
	}
	else if (rx_buffer == 'c')
	{ // clear ��ϴ
		Serial.print("***|  ");
		Serial.print("Will clear window!");
		Serial.println();
		rx_buffer = 'N';
		return 'c';
	}
	else
	{ // no message ����Ϣ
		Serial.print("***|  ");
		Serial.print("No message!");
		Serial.println();
		rx_buffer = 'N';
		return 'n';
	}
}

//
// Message.cpp end
//