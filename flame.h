/**************************************************************************************
 * Copyright (c) 张群伟. 
 * All rights reserved.	
 * 文件名	：flame.h
 * 摘要		：CFlame类的接口
 * 作者		：张群伟	南昌航空大学信息工程学院自动化系
 * 日期		：[3/29/2017]
 * 历史记录	：
 *		修改者：   日期：	 版本：	   修改内容：
 *	 1. 张群伟     17/1/10  1.0         创建该模块 
 *   2. 张群伟     17/2/3   1.1         从CSensor类继承，去掉与CSensor类相关的函数
 *   3. 张群伟	  17/2/26  1.2         重写monitor()函数，以便优化监测方式
 **************************************************************************************/

#ifndef _FLAME_H__
#define _FLAME_H__

#include "sensor.h"

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

/**************************************************************************************
 * 类名称	：CFlame
 * 功能		：CFlame提供火焰传感器的使用接口。
 * 当前版本 ：1.0
 * 作者		：张群伟	南昌航空大学信息工程学院自动化系
 * 日期		：[3/29/2017]
 **************************************************************************************/
class CFlame : public CSensor
{
public:
	CFlame(int flame_pin);
	~CFlame();

	// 重写
public:
	virtual void show();
	virtual int monitor();
};

#endif
// flame.h end
