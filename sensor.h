/**************************************************************************************
 * Copyright (c) ��Ⱥΰ. 
 * All rights reserved.	
 * �ļ���	��sensor.h
 * ժҪ		��CSensor��Ľӿ�
 * ����		����Ⱥΰ	�ϲ����մ�ѧ��Ϣ����ѧԺ�Զ���ϵ
 * ����		��[3/29/2017]
 * ��ʷ��¼	��
 *		�޸��ߣ�   ���ڣ�	 �汾��	   �޸����ݣ�
 *	 1. ��Ⱥΰ     17/2/3   1.0         ������ģ��	
 **************************************************************************************/

#ifndef _SENSOR_H__
#define _SENSOR_H__

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#define OPEN_WINDOW 1
#define SHUT_WINDOW 0
#define KEEP_WINDOW 2

/**************************************************************************************
 * ������	��CSensor
 * ����		��CSensor�ṩ��������ʹ�ýӿڡ�
 * ��ǰ�汾 ��1.0
 * ����		����Ⱥΰ	�ϲ����մ�ѧ��Ϣ����ѧԺ�Զ���ϵ
 * ����		��[3/29/2017]
 **************************************************************************************/
class CSensor
{
public:
	// ���洫�����ɼ�����ֵ
	int m_value;
	// ����������
	int m_pin;      

public:
	CSensor();
	~CSensor();

	// ��д
public:
	virtual int read();			// read value of m_value
	virtual void show() = 0;	// show value of m_value
	virtual int monitor() = 0;	// monitor m_value
	virtual void detach();		// free pin of m_pin
};

#endif
// sensor.h end