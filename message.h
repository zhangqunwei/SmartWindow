// Copyright (c) 张群伟. 
// All rights reserved.
//
// FileName:Message.h 
// Summary: interface of the CMessage class
// 
// Author: 张群伟    Version: 1.0    Date:2017/2/25
// History: 
//     Author:    Date:    Version:    Modification: 
//  1. 张群伟     17/2/25   1.0         创建该模块
//  2. 张群伟     17/3/2    1.1         将notify修改为message
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
// Function	: CMessage提供通知或报警的使用接口。
// Version	：1.0
// Author	：张群伟	南昌航空大学信息工程学院自动化系
// Date		：2017/2/25
class CMessage
{
public:
	int m_pin;      // 引脚
	char rx_buffer; // 串口数据缓冲区
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