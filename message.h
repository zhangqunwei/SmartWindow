// Copyright (c) ��Ⱥΰ. 
// All rights reserved.
//
// FileName:Message.h 
// Summary: interface of the CMessage class
// 
// Author: ��Ⱥΰ    Version: 1.0    Date:2017/2/25
// History: 
//     Author:    Date:    Version:    Modification: 
//  1. ��Ⱥΰ     17/2/25   1.0         ������ģ��
//  2. ��Ⱥΰ     17/3/2    1.1         ��notify�޸�Ϊmessage
/////////////////////////////////////////////////////////////////////////////

#ifndef _MESSAGE_H__
#define _MESSAGE_H__

#include "sensor.h"

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

extern int WindowState;

// Class   	: CMessage
// Function	: CMessage�ṩ֪ͨ�򱨾���ʹ�ýӿڡ�
// Version	��1.0
// Author	����Ⱥΰ	�ϲ����մ�ѧ��Ϣ����ѧԺ�Զ���ϵ
// Date		��2017/2/25
class CMessage
{
public:
	int m_pin;      // ����
	char rx_buffer; // �������ݻ�����
public:
	CMessage();
	CMessage(int Pin);
	~CMessage();

public:
	virtual void pulse(unsigned long pulse_width, int pulse_num);
	
	virtual char monitor();

	virtual void detach();
};


#endif
//
// Message.h end
//