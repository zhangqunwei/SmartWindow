/**************************************************************************************
 * Copyright (c) ��Ⱥΰ. 
 * All rights reserved.	
 * �ļ���	��message.h
 * ժҪ		��CMessage ��Ľӿ�
 * ����		����Ⱥΰ	�ϲ����մ�ѧ��Ϣ����ѧԺ�Զ���ϵ
 * ����		��[3/29/2017]
 * ��ʷ��¼	��
 *		�޸��ߣ�   ���ڣ�	 �汾��	   �޸����ݣ�
 *	 1. ��Ⱥΰ     17/2/25   1.0         ������ģ��	
 *	 2. ��Ⱥΰ     17/3/2    1.1         ��notify�޸�Ϊmessage
 **************************************************************************************/
#ifndef _MESSAGE_H__
#define _MESSAGE_H__

#include "sensor.h"

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

extern int WindowState;

/**************************************************************************************
 * ������	��CMessage
 * ����		��CMessage�ṩ֪ͨ�򱨾���ʹ�ýӿڡ�
 * ��ǰ�汾 ��1.0
 * ����		����Ⱥΰ	�ϲ����մ�ѧ��Ϣ����ѧԺ�Զ���ϵ
 * ����		��[3/29/2017]
 **************************************************************************************/
class CMessage
{
public:
	// ����
	int m_pin;     
	// �������ݻ�����
	char rx_buffer; 

public:
	CMessage();
	CMessage(int Pin);
	~CMessage();

	// ��д
public:
	virtual void pulse(unsigned long pulse_width, int pulse_num);
	
	virtual char monitor();

	virtual void detach();
};


#endif
//
// Message.h end
//