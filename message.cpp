/**************************************************************************************
 * Copyright (c) 张群伟. 
 * All rights reserved.	
 * 文件名	：message.cpp
 * 摘要		：消息类的实现
 * 作者		：张群伟	南昌航空大学信息工程学院自动化系
 * 日期		：[3/29/2017]
 * 历史记录	：
 *		修改者：   日期：	 版本：	   修改内容：
 *	1.  张群伟     17/2/25   1.0       创建该模块 	
 **************************************************************************************/

#include "Message.h"

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
// CMessage 构造/析构
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
 * 函数名	：Message()
 * 功能		：报警,从m_pin 引脚输出脉宽为pulse_width脉冲个数为pulse_num的脉冲
 * 参数		：pulse_width	脉冲宽度
 *			  pulse_num	脉冲个数
 * 返回值   : void
 * 说明  	：
 * 作者		：张群伟	南昌航空大学信息工程学院自动化系
 * 日期		：[3/29/2017]
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
 * 函数名	：detach()
 * 功能		：释放 m_pin 引脚
 * 参数		：void
 * 返回值   : void
 * 说明  	：
 * 作者		：张群伟	南昌航空大学信息工程学院自动化系
 * 日期		：[3/29/2017]
 **************************************************************************************/
void CMessage::detach(void)
{
	pinMode(m_pin, OUTPUT);
	digitalWrite(m_pin, LOW);
	pinMode(m_pin, INPUT);
}
		
/**************************************************************************************
 * 函数名	：monitor()
 * 功能		：监测串口消息中是否有开窗或者关窗动作
 * 参数		：
 * 返回值   : s	shut 关窗	
 *			  o	open 开窗
 *			  n   NULL 空
 * 说明  	：
 * 作者		：张群伟	南昌航空大学信息工程学院自动化系
 * 日期		：[3/29/2017]
 **************************************************************************************/
char CMessage::monitor()
{
	if (Serial.available() > 0)
	{ // 接收消息并存到缓冲区
		rx_buffer = Serial.read();
	}
	Serial.print("***|  PC	 send:\t");
	Serial.print(rx_buffer);
	Serial.println();

	if ((rx_buffer == 's') && (WindowState == OPEN_WINDOW))
	{ // shut 关窗
		Serial.print("***|  ");
		Serial.print("Arduino receive:	Will shut window!"); 
		Serial.println();
		rx_buffer = 'N';
		return 's';
	}
	else if ((rx_buffer == 'o') && (WindowState == SHUT_WINDOW))
	{ // open 开窗
		Serial.print("***|  ");
		Serial.print("Arduino receive:	Will open window!");
		Serial.println();
		rx_buffer = 'N';
		return 'o';
	}
	else if (rx_buffer == 'c')
	{ // clear 清洗
		Serial.print("***|  ");
		Serial.print("Arduino receive:	Will clear window!");
		Serial.println();
		rx_buffer = 'N';
		return 'c';
	}
	else if (rx_buffer == 'k')
	{ // clear 关闭清洗
		Serial.print("***|  ");
		Serial.print("Arduino receive:	Will shut clear!");
		Serial.println();
		rx_buffer = 'N';
		return 'k';
	}
	else if (rx_buffer == 'f')
	{ // f 打开风扇
		Serial.print("***|  ");
		Serial.print("Arduino receive:	Will open fan!");
		Serial.println();
		rx_buffer = 'N';
		return 'f';
	}
	else if (rx_buffer == 'g')
	{ // g 关闭风扇
		Serial.print("***|  ");
		Serial.print("Arduino receive:	Will shut fan!");
		Serial.println();
		rx_buffer = 'N';
		return 'g';
	}
	else
	{ // no message 无消息
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