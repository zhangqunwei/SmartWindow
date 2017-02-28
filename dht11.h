// Copyright (c) 张群伟. 
// All rights reserved.
//
// FileName:dht11.h 
// Summary: interface of the Dht11 class
// 
// Author: 张群伟    Version: 1.0    Date:2017/1/10
// History: 
//     Author:    Date:    Version:    Modification: 
//  1. 张群伟     17/1/10   1.0			创建该模块
//	2. 张群伟	  17/2/3	1.1			从传感器类继承
//  3. 张群伟     17/2/26   1.2         修改了monitor()函数，使其更一般化
/////////////////////////////////////////////////////////////////////////////

#ifndef _DHT11_H__
#define _DHT11_H__

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WPro gram.h>
#endif

#include "sensor.h"

#define DHT11_VERSION "1.0"

#define TIME_OUT				1000

#define DHT11_OK				0
#define DHT11_ERROR_CHECKSUM	-1
#define DHT11_ERROR_TIMEOUT		-2


// Class   	: Dht11
// Function	: DHT11提供温湿度传感器的驱动接口。
// Version	：1.0
// Author	：张群伟	南昌航空大学信息工程学院自动化系
// Date		：2017-1-10
class Dht11 : public CSensor
{
private:
	uint8_t bits[5];	// 保存数据
	int read();
public:
	int m_humidity;		// 湿度
	int m_temperature;	// 温度

public:
	Dht11(int dht_pin);

public:
	// 用于扫描温湿度值是否超限
	int DetectonExtent(char m_value_type, int m_value_min, int m_value_max);
	virtual int monitor();

	// 相关显示函数
	virtual void show();
	void showdew();
	void showKelvin();
	void showHumidity();
	void showFahrenheit();
	void showTemperature();

	// 摄氏温度转化为开氏温度
	double Kelvin(double celsius);

	// 摄氏温度度转化为华氏温度
	double Fahrenheit(double celsius);

	// 快速计算露点
	double dewPointFast(double celsius, double humidity);
};
#endif
// dht11.h end
