/**************************************************************************************
 * Copyright (c) 张群伟. 
 * All rights reserved.	
 * 文件名	：message.h
 * 摘要		：CMessage 类的接口
 * 作者		：张群伟	南昌航空大学信息工程学院自动化系
 * 日期		：[3/29/2017]
 * 历史记录	：
 *		修改者：   日期：	 版本：	   修改内容：
 *	 1. 张群伟     17/2/25   1.0         创建该模块	
 *	 2. 张群伟     17/3/2    1.1         将notify修改为message
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
 * 类名称	：CMessage
 * 功能		：CMessage提供通知或报警的使用接口。
 * 当前版本 ：1.0
 * 作者		：张群伟	南昌航空大学信息工程学院自动化系
 * 日期		：[3/29/2017]
 **************************************************************************************/
class CMessage
{
public:
	// 引脚
	int m_pin;     
	// 串口数据缓冲区
	char rx_buffer; 

public:
	CMessage();
	CMessage(int Pin);
	~CMessage();

	// 重写
public:
	virtual void pulse(unsigned long pulse_width, int pulse_num);
	
	virtual char monitor();

	virtual void detach();
};


#endif
//
// Message.h end
//