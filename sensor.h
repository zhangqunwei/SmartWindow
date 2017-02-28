// Copyright (c) ��Ⱥΰ. 
// All rights reserved.
//
// FileName:sensor.h 
// Summary: interface of the CSensor class
// 
// Author: ��Ⱥΰ    Version: 1.0    Date:2017/2/3
// History: 
//     Author:    Date:    Version:    Modification: 
//  1. ��Ⱥΰ     17/2/3   1.0         ������ģ��
//
/////////////////////////////////////////////////////////////////////////////

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

// Class   	: CSensor
// Function	: CSensor�ṩ��������ʹ�ýӿڡ�
// Version	��1.0
// Author	����Ⱥΰ	�ϲ����մ�ѧ��Ϣ����ѧԺ�Զ���ϵ
// Date		��2017/2/3
class CSensor
{
public:
	int m_value;	// ���洫�����ɼ�����ֵ
	int m_pin;      // ����������

public:
	CSensor();
	~CSensor();

public:
	virtual int read();			// read value of m_value
	virtual void show() = 0;	// show value of m_value
	virtual int monitor() = 0;	// monitor m_value
	virtual void detach();		// free pin of m_pin
};

#endif
// sensor.h end