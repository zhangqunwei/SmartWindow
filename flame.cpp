/**************************************************************************************
 * Copyright (c) 张群伟.
 * All rights reserved.
 * 文件名	：flame.cpp
 * 摘要		：CFlame 类的实现
 * 作者		：张群伟	南昌航空大学信息工程学院自动化系
 * 日期		：[3/29/2017]
 * 历史记录	：
 *		修改者：   日期：	 版本：	   修改内容：
 *	 1. 张群伟     17/1/10  1.0         创建该模块
 **************************************************************************************/

#include "flame.h"

#define FLAME_VALUE_MAX  600

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
// CFlame 构造/析构
CFlame::CFlame(int flame_pin)
{
	m_pin = flame_pin;
	NULL;
}

CFlame::~CFlame()
{
	NULL;
}

/**************************************************************************************
 * 函数名	：show()
 * 功能		：显示
 * 参数		：void
 * 返回值   : void
 * 说明  	：
 * 作者		：张群伟	南昌航空大学信息工程学院自动化系
 * 日期		：[3/29/2017]
 **************************************************************************************/
void CFlame::show(void)
{
	read();
	Serial.print("***|	Flame:\t");
	Serial.print(m_value);
	Serial.print("\t");
	Serial.print("\t\tmax = 600");
	Serial.println();
	//!delay(50);
	delay(10);
}

/**************************************************************************************
 * 函数名	：monitor()
 * 功能		：监测火焰值
 * 参数		：
 * 返回值   : OPEN_WINDOW  开窗
 *			  SHUT_WINDOW  关窗
 * 说明  	：
 * 作者		：张群伟	南昌航空大学信息工程学院自动化系
 * 日期		：[3/29/2017]
 **************************************************************************************/
int CFlame::monitor()
{
	if (m_value > FLAME_VALUE_MAX)
		return OPEN_WINDOW;
	else
		return KEEP_WINDOW;
}

// flame.cpp end