// Copyright (c) 张群伟. 
// All rights reserved.
//
// FileName:flame.h 
// Summary: interface of the CFlame class
// 
// Author: 张群伟    Version: 1.0    Date:2017/1/10
// History: 
//     Author:    Date:    Version:    Modification: 
//  1. 张群伟     17/1/10  1.0         创建该模块 
//  2. 张群伟     17/2/3   1.1         从CSensor类继承，去掉与CSensor类相关的函数
//	3. 张群伟	  17/2/26  1.2         重写monitor()函数，以便优化监测方式
/////////////////////////////////////////////////////////////////////////////


#ifndef _FLAME_H__
#define _FLAME_H__

#include "sensor.h"

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

// Class   	: CFlame
// Function	: CFlame提供火焰传感器的使用接口。
// Version	：1.0
// Author	：张群伟	南昌航空大学信息工程学院自动化系
// Date		：2017-1-10
class CFlame : public CSensor
{
public:
    CFlame(int flame_pin);
    ~CFlame();

public:
	virtual void show();
	virtual int monitor();
};

#endif
// flame.h end
