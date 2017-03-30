/**************************************************************************************
 * Copyright (c) 张群伟. 
 * All rights reserved.	
 * 文件名	：smoke.h
 * 摘要		：CSmoke类的接口
 * 作者		：张群伟	南昌航空大学信息工程学院自动化系
 * 日期		：[3/29/2017]
 * 历史记录	：
 *		修改者：   日期：	 版本：	   修改内容：
 *	 1. 张群伟     17/2/25   1.0         创建该模块 	
 **************************************************************************************/


#ifndef _SMOKE_H__
#define _SMOKE_H__

#include "sensor.h"

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

/**************************************************************************************
 * 类名称	：CSmoke
 * 功能		：CSmoke提供烟雾传感器的使用接口。
 * 当前版本 ：1.0
 * 作者		：张群伟	南昌航空大学信息工程学院自动化系
 * 日期		：[3/29/2017]
 **************************************************************************************/
class CSmoke : public CSensor
{
public:
	CSmoke(int smoke_pin);
	~CSmoke();

	// 重写
public:
	virtual void show();
	virtual int monitor();
};

#endif
// smoke.h end
