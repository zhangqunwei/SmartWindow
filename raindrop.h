// Copyright (c) 张群伟. 
// All rights reserved.
//
// FileName:raindrop.h 
// Summary: interface of the CRaindrop class
// 
// Author: 张群伟    Version: 1.0    Date:2017/2/25
// History: 
//     Author:    Date:    Version:    Modification: 
//  1. 张群伟     17/2/25   1.0         创建该模块 
//
/////////////////////////////////////////////////////////////////////////////

#ifndef _RAINDROP_H__
#define _RAINDROP_H__

#include "sensor.h"

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

// Class   	: CRaindrop
// Function	: CRaindrop提供雨滴传感器的使用接口。
// Version	：1.0
// Author	：张群伟	南昌航空大学信息工程学院自动化系
// Date		：2017-2-25
class CRaindrop : public CSensor
{
public:
	CRaindrop(int raindrop_pin);
	~CRaindrop();

public:
	virtual int read();
	virtual void show();
	virtual int monitor();
};

#endif
// raindrop.h end
