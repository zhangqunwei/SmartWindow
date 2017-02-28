// Copyright (c) 张群伟. 
// All rights reserved.
//
// FileName:notify.h 
// Summary: interface of the CNotify class
// 
// Author: 张群伟    Version: 1.0    Date:2017/2/25
// History: 
//     Author:    Date:    Version:    Modification: 
//  1. 张群伟     17/2/25   1.0         创建该模块
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
// Function	: CNotify提供通知或报警的使用接口。
// Version	：1.0
// Author	：张群伟	南昌航空大学信息工程学院自动化系
// Date		：2017/2/25
class CNotify
{
public:
	int m_pin;      // 引脚

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