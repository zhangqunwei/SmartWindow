// Copyright (c) ��Ⱥΰ. 
// All rights reserved.
//
// FileName:smoke.h 
// Summary: interface of the CSmoke class
// 
// Author: ��Ⱥΰ    Version: 1.0    Date:2017/2/25
// History: 
//     Author:    Date:    Version:    Modification: 
//  1. ��Ⱥΰ     17/2/25   1.0         ������ģ�� 
//
/////////////////////////////////////////////////////////////////////////////


#ifndef _SMOKE_H__
#define _SMOKE_H__

#include "sensor.h"

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

// Class   	: CSmoke
// Function	: CSmoke�ṩ����������ʹ�ýӿڡ�
// Version	��1.0
// Author	����Ⱥΰ	�ϲ����մ�ѧ��Ϣ����ѧԺ�Զ���ϵ
// Date		��2017-2-25
class CSmoke : public CSensor
{
public:
	CSmoke(int smoke_pin);
	~CSmoke();

public:
	virtual void show();
	virtual int monitor();
};

#endif
// smoke.h end
