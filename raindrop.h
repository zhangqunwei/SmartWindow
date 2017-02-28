// Copyright (c) ��Ⱥΰ. 
// All rights reserved.
//
// FileName:raindrop.h 
// Summary: interface of the CRaindrop class
// 
// Author: ��Ⱥΰ    Version: 1.0    Date:2017/2/25
// History: 
//     Author:    Date:    Version:    Modification: 
//  1. ��Ⱥΰ     17/2/25   1.0         ������ģ�� 
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _RAINDROP_H__
#define _RAINDROP_H__

#include "sensor.h"

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

// Class   	: CRaindrop
// Function	: CRaindrop�ṩ��δ�������ʹ�ýӿڡ�
// Version	��1.0
// Author	����Ⱥΰ	�ϲ����մ�ѧ��Ϣ����ѧԺ�Զ���ϵ
// Date		��2017-2-25
class CRaindrop : public CSensor
{
public:
	CRaindrop(int raindrop_pin);
	~CRaindrop();

public:
	virtual int read();
	virtual void show();
	virtual int monitor();
};

#endif
// raindrop.h end
