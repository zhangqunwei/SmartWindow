/**************************************************************************************
 * Copyright (c) 张群伟. 
 * All rights reserved.	
 * 文件名	：sensor.h
 * 摘要		：CSensor类的接口
 * 作者		：张群伟	南昌航空大学信息工程学院自动化系
 * 日期		：[3/29/2017]
 * 历史记录	：
 *		修改者：   日期：	 版本：	   修改内容：
 *	 1. 张群伟     17/2/3   1.0         创建该模块	
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
 * 类名称	：CSensor
 * 功能		：CSensor提供传感器的使用接口。
 * 当前版本 ：1.0
 * 作者		：张群伟	南昌航空大学信息工程学院自动化系
 * 日期		：[3/29/2017]
 **************************************************************************************/
class CSensor
{
public:
	// 保存传感器采集到的值
	int m_value;
	// 传感器引脚
	int m_pin;      

public:
	CSensor();
	~CSensor();

	// 重写
public:
	virtual int read();			// read value of m_value
	virtual void show() = 0;	// show value of m_value
	virtual int monitor() = 0;	// monitor m_value
	virtual void detach();		// free pin of m_pin
};

#endif
// sensor.h end