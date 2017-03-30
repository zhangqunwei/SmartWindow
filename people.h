/**************************************************************************************
 * Copyright (c) 张群伟. 
 * All rights reserved.	
 * 文件名	：people.h
 * 摘要		：CPeople类的接口
 * 作者		：张群伟	南昌航空大学信息工程学院自动化系
 * 日期		：[3/29/2017]
 * 历史记录	：
 *		修改者：   日期：	 版本：	   修改内容：
 *	 1. 张群伟     17/1/10  1.0         创建该模块	
 *	 2. 张群伟	  17/2/3   1.1		   从传感器类继承
 **************************************************************************************/

#ifndef _PEOPLESENSOR_H__
#define _PEOPLESENSOR_H__

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "sensor.h"

/**************************************************************************************
 * 类名称	：CPeople
 * 功能		：CPeople提供人体传感器的驱动接口。
 * 当前版本 ：1.0
 * 作者		：张群伟	南昌航空大学信息工程学院自动化系
 * 日期		：[3/29/2017]
 **************************************************************************************/
class CPeople : public CSensor
{
  public:
    CPeople(int Pin);
    ~CPeople();

	// 重写
  public:
	  virtual int read();
	  virtual void show();
	  virtual int monitor();
};

#endif
// people.h end
