// Copyright (c) 张群伟. 
// All rights reserved.
//
// FileName: Message.cpp
// Summary:  implementation of the CMessage class 
//
// Author: 张群伟    Version: 1.0    Date:2017/2/25
// History: 
//     Author:    Date:    Version:    Modification:
// 1.  张群伟     17/2/25   1.0         创建该模块 
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
// Description: 报警,从m_pin 引脚输出脉宽为pulse_width脉冲个数为pulse_num的脉冲
// Input:	pulse_width	脉冲宽度
//			pulse_num	脉冲个数
// Output: 无
// Return: 无
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
// Description: 释放 m_pin 引脚
// Input: 无
// Output: 无
// Return: 无
void CMessage::detach()
{
	pinMode(m_pin, OUTPUT);
	digitalWrite(m_pin, LOW);
	pinMode(m_pin, INPUT);
}

// Function: monitor()
// Description: 监测串口消息中是否有开窗或者关窗动作
// Input: 无
// Output: 无
// Return:	s	shut 关窗
//			o	open 开窗
//			n   NULL 空
char CMessage::monitor()
{
	if (Serial.available() > 0)
	{ // 接收消息并存到缓冲区
		rx_buffer = Serial.read();
	}
	Serial.print("***|  send:\t");
	Serial.print(rx_buffer);
	Serial.println();

	if ((rx_buffer == 's') && (WindowState == OPEN_WINDOW))
	{ // shut 关窗
		Serial.print("***|  ");
		Serial.print("Will shut window!"); 
		Serial.println();
		rx_buffer = 'N';
		return 's';
	}
	else if ((rx_buffer == 'o') && (WindowState == SHUT_WINDOW))
	{ // open 开窗
		Serial.print("***|  ");
		Serial.print("Will open window!");
		Serial.println();
		rx_buffer = 'N';
		return 'o';
	}
	else if (rx_buffer == 'c')
	{ // clear 清洗
		Serial.print("***|  ");
		Serial.print("Will clear window!");
		Serial.println();
		rx_buffer = 'N';
		return 'c';
	}
	else
	{ // no message 无消息
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