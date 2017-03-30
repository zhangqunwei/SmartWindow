/**************************************************************************************
 * Copyright (c) 张群伟. 
 * All rights reserved.	
 * 文件名	：raindrop.h
 * 摘要		：CRaindrop类的接口
 * 作者		：张群伟	南昌航空大学信息工程学院自动化系
 * 日期		：[3/29/2017]
 * 历史记录	：
 *		修改者：   日期：	 版本：	   修改内容：
 *	 1. 张群伟     17/2/25   1.0         创建该模块	
 **************************************************************************************/

#ifndef _RAINDROP_H__
#define _RAINDROP_H__

#include "sensor.h"

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

/**************************************************************************************
 * 类名称	：CRaindrop
 * 功能		：CRaindrop提供雨滴传感器的使用接口。
 * 当前版本 ：1.0
 * 作者		：张群伟	南昌航空大学信息工程学院自动化系
 * 日期		：[3/29/2017]
 **************************************************************************************/
class CRaindrop : public CSensor
{
public:
	CRaindrop(int raindrop_pin);
	~CRaindrop();

	// 重写
public:
	virtual int read();
	virtual void show();
	virtual int monitor();
};

#endif
// raindrop.h end
