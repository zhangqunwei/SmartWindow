/**************************************************************************************
 * Copyright (c) ��Ⱥΰ. 
 * All rights reserved.	
 * �ļ���	��message.cpp
 * ժҪ		����Ϣ���ʵ��
 * ����		����Ⱥΰ	�ϲ����մ�ѧ��Ϣ����ѧԺ�Զ���ϵ
 * ����		��[3/29/2017]
 * ��ʷ��¼	��
 *		�޸��ߣ�   ���ڣ�	 �汾��	   �޸����ݣ�
 *	1.  ��Ⱥΰ     17/2/25   1.0       ������ģ�� 	
 **************************************************************************************/

#include "Message.h"

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
// CMessage ����/����
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


/**************************************************************************************
 * ������	��Message()
 * ����		������,��m_pin �����������Ϊpulse_width�������Ϊpulse_num������
 * ����		��pulse_width	������
 *			  pulse_num	�������
 * ����ֵ   : void
 * ˵��  	��
 * ����		����Ⱥΰ	�ϲ����մ�ѧ��Ϣ����ѧԺ�Զ���ϵ
 * ����		��[3/29/2017]
 **************************************************************************************/
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

/**************************************************************************************
 * ������	��detach()
 * ����		���ͷ� m_pin ����
 * ����		��void
 * ����ֵ   : void
 * ˵��  	��
 * ����		����Ⱥΰ	�ϲ����մ�ѧ��Ϣ����ѧԺ�Զ���ϵ
 * ����		��[3/29/2017]
 **************************************************************************************/
void CMessage::detach(void)
{
	pinMode(m_pin, OUTPUT);
	digitalWrite(m_pin, LOW);
	pinMode(m_pin, INPUT);
}
		
/**************************************************************************************
 * ������	��monitor()
 * ����		����⴮����Ϣ���Ƿ��п������߹ش�����
 * ����		��
 * ����ֵ   : s	shut �ش�	
 *			  o	open ����
 *			  n   NULL ��
 * ˵��  	��
 * ����		����Ⱥΰ	�ϲ����մ�ѧ��Ϣ����ѧԺ�Զ���ϵ
 * ����		��[3/29/2017]
 **************************************************************************************/
char CMessage::monitor()
{
	if (Serial.available() > 0)
	{ // ������Ϣ���浽������
		rx_buffer = Serial.read();
	}
	Serial.print("***|  PC	 send:\t");
	Serial.print(rx_buffer);
	Serial.println();

	if ((rx_buffer == 's') && (WindowState == OPEN_WINDOW))
	{ // shut �ش�
		Serial.print("***|  ");
		Serial.print("Arduino receive:	Will shut window!"); 
		Serial.println();
		rx_buffer = 'N';
		return 's';
	}
	else if ((rx_buffer == 'o') && (WindowState == SHUT_WINDOW))
	{ // open ����
		Serial.print("***|  ");
		Serial.print("Arduino receive:	Will open window!");
		Serial.println();
		rx_buffer = 'N';
		return 'o';
	}
	else if (rx_buffer == 'c')
	{ // clear ��ϴ
		Serial.print("***|  ");
		Serial.print("Arduino receive:	Will clear window!");
		Serial.println();
		rx_buffer = 'N';
		return 'c';
	}
	else if (rx_buffer == 'k')
	{ // clear �ر���ϴ
		Serial.print("***|  ");
		Serial.print("Arduino receive:	Will shut clear!");
		Serial.println();
		rx_buffer = 'N';
		return 'k';
	}
	else if (rx_buffer == 'f')
	{ // f �򿪷���
		Serial.print("***|  ");
		Serial.print("Arduino receive:	Will open fan!");
		Serial.println();
		rx_buffer = 'N';
		return 'f';
	}
	else if (rx_buffer == 'g')
	{ // g �رշ���
		Serial.print("***|  ");
		Serial.print("Arduino receive:	Will shut fan!");
		Serial.println();
		rx_buffer = 'N';
		return 'g';
	}
	else
	{ // no message ����Ϣ
		Serial.print("***|  ");
		Serial.print("Arduino receive:	No message!");
		Serial.println();
		rx_buffer = 'N';
		return 'n';
	}
}

//
// Message.cpp end
//