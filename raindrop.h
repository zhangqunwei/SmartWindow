/**************************************************************************************
 * Copyright (c) ��Ⱥΰ. 
 * All rights reserved.	
 * �ļ���	��raindrop.h
 * ժҪ		��CRaindrop��Ľӿ�
 * ����		����Ⱥΰ	�ϲ����մ�ѧ��Ϣ����ѧԺ�Զ���ϵ
 * ����		��[3/29/2017]
 * ��ʷ��¼	��
 *		�޸��ߣ�   ���ڣ�	 �汾��	   �޸����ݣ�
 *	 1. ��Ⱥΰ     17/2/25   1.0         ������ģ��	
 **************************************************************************************/

#ifndef _RAINDROP_H__
#define _RAINDROP_H__

#include "sensor.h"

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

/**************************************************************************************
 * ������	��CRaindrop
 * ����		��CRaindrop�ṩ��δ�������ʹ�ýӿڡ�
 * ��ǰ�汾 ��1.0
 * ����		����Ⱥΰ	�ϲ����մ�ѧ��Ϣ����ѧԺ�Զ���ϵ
 * ����		��[3/29/2017]
 **************************************************************************************/
class CRaindrop : public CSensor
{
public:
	CRaindrop(int raindrop_pin);
	~CRaindrop();

	// ��д
public:
	virtual int read();
	virtual void show();
	virtual int monitor();
};

#endif
// raindrop.h end
