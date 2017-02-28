// Copyright (c) 张群伟. 
// All rights reserved.
//
// FileName:sensor.h 
// Summary: interface of the CSensor class
// 
// Author: 张群伟    Version: 1.0    Date:2017/2/3
// History: 
//     Author:    Date:    Version:    Modification: 
//  1. 张群伟     17/2/3   1.0         创建该模块
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
// Function	: CSensor提供传感器的使用接口。
// Version	：1.0
// Author	：张群伟	南昌航空大学信息工程学院自动化系
// Date		：2017/2/3
class CSensor
{
public:
	int m_value;	// 保存传感器采集到的值
	int m_pin;      // 传感器引脚

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