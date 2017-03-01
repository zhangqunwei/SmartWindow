// Copyright (c) 张群伟. 
// All rights reserved.
//
// FileName:people.h 
// Summary: interface of the CPeople class
// 
// Author: 张群伟    Version: 1.0    Date:2017/1/10
// History: 
//     Author:    Date:    Version:    Modification: 
//  1. 张群伟     17/1/10  1.0         创建该模块
//	2. 张群伟	  17/2/3   1.1		   从传感器类继承
/////////////////////////////////////////////////////////////////////////////

#ifndef _PEOPLESENSOR_H__
#define _PEOPLESENSOR_H__

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include "sensor.h"

// Class   	: CPeople
// Function	: CPeople提供人体传感器的驱动接口。
// Version	：1.0
// Author	：张群伟	南昌航空大学信息工程学院自动化系
// Date		：2017-1-10
class CPeople : public CSensor
{
  public:
    CPeople(int Pin);
    ~CPeople();

  public:
	  virtual int read();
	  virtual void show();
	  virtual int monitor();
};

#endif
// people.h end
