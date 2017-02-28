// Copyright (c) ��Ⱥΰ. 
// All rights reserved.
//
// FileName:notify.h 
// Summary: interface of the CNotify class
// 
// Author: ��Ⱥΰ    Version: 1.0    Date:2017/2/25
// History: 
//     Author:    Date:    Version:    Modification: 
//  1. ��Ⱥΰ     17/2/25   1.0         ������ģ��
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _NOTIFY_H__
#define _NOTIFY_H__

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

// Class   	: CNotify
// Function	: CNotify�ṩ֪ͨ�򱨾���ʹ�ýӿڡ�
// Version	��1.0
// Author	����Ⱥΰ	�ϲ����մ�ѧ��Ϣ����ѧԺ�Զ���ϵ
// Date		��2017/2/25
class CNotify
{
public:
	int m_pin;      // ����

public:
	CNotify(int Pin);
	~CNotify();

public:
	virtual void notify(unsigned long pulse_width, int pulse_num);
	virtual void detach();
};

#endif
//
// notify.h end
//