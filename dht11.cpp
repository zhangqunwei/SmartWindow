/**************************************************************************************
 * Copyright (c) 张群伟.
 * All rights reserved.
 * 文件名	：dht11.cpp
 * 摘要		：温湿度传感器类的实现
 * 作者		：张群伟	南昌航空大学信息工程学院自动化系
 * 日期		：[3/29/2017]
 * 历史记录	：
 *		修改者：	日期：	版本：	修改内容：
 *
 **************************************************************************************/

#include "dht11.h"

#define VALUEMIN	0
#define VALUEMAX	1
#define VALUENORMAL 2

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
// Dht11 构造/析构
Dht11::Dht11(int dht_pin)
{
	m_pin = dht_pin;
}

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
//数据读取，监测部分

/**************************************************************************************
 * 函数名	：read()
 * 功能		：读取温湿度
 * 参数		：void
 * 返回值   : DHT11_ERROR_TIMEOUT		超时
 *			  DHT11_ERROR_CHECKSUM		校验和错误
 * 说明  	：
 * 作者		：张群伟
 * 日期		：[3/29/2017]
 **************************************************************************************/
int Dht11::read()
{
	uint8_t num_bit = 7;     			// min:0  max:7
	uint8_t id_byte = 0;     			// min:0  max:4

	for (int i = 0; i < 5; i++) bits[i] = 0;

	// 主机发开始信号
	pinMode(m_pin, OUTPUT);
	digitalWrite(m_pin, LOW);
	delay(20);				// 主机拉低总线至少18ms
	digitalWrite(m_pin, HIGH);
	delayMicroseconds(40);    // 主机拉高20-40us
	pinMode(m_pin, INPUT);	// 输入模式，等待从机响应

	// 等待从机响应
	unsigned int loopCount = TIME_OUT;
	while (digitalRead(m_pin) == LOW)
	if (0 == loopCount--) return DHT11_ERROR_TIMEOUT;

	loopCount = TIME_OUT;
	while (digitalRead(m_pin) == HIGH)
	if (0 == loopCount--) return DHT11_ERROR_TIMEOUT;

	// 接收数据
	for (int bit = 0; bit < 40; bit++)
	{
		loopCount = TIME_OUT;
		while (digitalRead(m_pin) == LOW)
		if (0 == loopCount--) return DHT11_ERROR_TIMEOUT;

		unsigned long t = micros();
		loopCount = TIME_OUT;
		while (digitalRead(m_pin) == HIGH)
		if (0 == loopCount--) return DHT11_ERROR_TIMEOUT;

		if ((micros() - t) > 40)
			bits[id_byte] |= (1 << num_bit);

		// 下一个字节
		if (num_bit == 0)
		{
			num_bit = 7;
			id_byte++;
		}
		else num_bit--;
	}

	// 取出数据
	m_humidity = bits[0];
	m_temperature = bits[2];

	// 校验和
	uint8_t sum = bits[0] + bits[2];
	if (bits[4] != sum) return DHT11_ERROR_CHECKSUM;
} // int Dht11::read()  END

/**************************************************************************************
 * 结构体名	：ValueExtent
 * 功能		：ValueExtent用于存储温湿度检测范围的数据
 * 参数		：type  检测数据类型
 *					取值：'H' 湿度， 'T' 温度， 'D' 露点
 *			  min	最小值
 *			  max   最大值
 * 说明  	：
 * 作者		：张群伟
 * 日期		：[3/29/2017]
 **************************************************************************************/
typedef	struct
{
	char type;
	float min;
	float max;
}ValueExtent;

//! 在此设置温湿度监控范围
ValueExtent value[3] = { { 'T', 5, 25 },		// 温度的监控范围
{ 'H', 5, 80 },		// 湿度的监控范围
{ 'D', -20, 20 } 	// 露点的监控范围
};

/**************************************************************************************
 * 函数名	：monitor()
 * 功能		：监测温湿度
 * 参数		：
 * 返回值   : OPEN_WINDOW  开窗
 *			  SHUT_WINDOW  关窗
 * 说明  	：监测温湿度的值是否超限，若超限则返回相应的请求
 * 作者		：张群伟
 * 日期		：[3/29/2017]
 **************************************************************************************/
int Dht11::monitor()
{
	// 检测温湿度是否超限
	for (int i = 0; i < 3; i++)
	{
		if (VALUEMIN == DetectonExtent(value[i].type, value[i].min, value[i].max))
			return SHUT_WINDOW;
		else if (VALUEMAX == DetectonExtent(value[i].type, value[i].min, value[i].max))
			return OPEN_WINDOW;
	}
	return KEEP_WINDOW;
}

/**************************************************************************************
 * 函数名	：DetectonExtent()
 * 功能		：检测数据类型为m_value_type的数据是否在范围(m_value_min, m_value_max)内
 * 参数		：m_value_type  检测数据类型
 *					取值：'H' 湿度， 'T' 温度， 'D' 露点
 *			  m_value_min	  最小值
 *			  m_value_max   最大值
 * 返回值   : VALUEMIN 小于最小值
 * 			  VALUEMAX 大于最大值
 * 说明  	：
 * 作者		：张群伟
 * 日期		：[3/29/2017]
 **************************************************************************************/
int Dht11::DetectonExtent(char m_value_type, float m_value_min, float m_value_max)
{
	// 监测最新值
	switch (m_value_type)
	{
	case 'H': // 湿度
		if ((float)m_humidity * 100 < m_value_min * 100)
			return VALUEMIN;
		if ((float)m_humidity > m_value_max)
			return VALUEMAX;
		break;

	case 'T': // 温度
		if ((float)m_temperature * 100 < m_value_min * 100)
			return VALUEMIN;
		if ((float)m_temperature > m_value_max)
			return VALUEMAX;
		break;

	case 'D': // 露点
		if (dewPointFast(m_temperature, m_humidity) * 100 < m_value_min * 100)
			return VALUEMIN;
		if (dewPointFast(m_temperature, m_humidity) > m_value_max)
			return VALUEMAX;
		break;

	default:
		return VALUENORMAL;
		break;
	}
}

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
// 数据显示部分

/**************************************************************************************
 * 函数名	：show()
 * 功能		：显示温湿度
 * 参数		：void
 * 返回值   : void
 * 说明  	：
 * 作者		：张群伟
 * 日期		：[3/29/2017]
 **************************************************************************************/
void Dht11::show(void)
{
	read();
	if (m_value == DHT11_ERROR_CHECKSUM)
		Serial.println("dht11 checksum error!");
	else
	{
		Serial.print("***|	Dht11: ");

		Serial.print("\tTemperature (oC):");
		Serial.print((float)m_temperature, 2);

		//!Serial.print("\t(oF): ");
		//!Serial.print(Fahrenheit(m_temperature), 2);

		//!Serial.print("\t(K): ");
		//!Serial.print(Kelvin(m_temperature), 2);

		Serial.print("\tHumidity(%): ");
		Serial.print((float)m_humidity, 2);

		Serial.print("\tDew PointFast(oC): ");
		Serial.print(dewPointFast(m_temperature, m_humidity));

		Serial.println();
		Serial.print("***|  \t\t");
		for (int i = 0; i < 3; i++)
		{
			Serial.print(value[i].type);
			Serial.print(" (");
			Serial.print(value[i].min);
			Serial.print(", ");
			Serial.print(value[i].max);
			Serial.print(" )\t");
		}
		Serial.println();
	}
	//!delay(50);
	delay(10);
}	// void Dht11::show() END

/**************************************************************************************
 * 函数名	：showdew()
 * 功能		：显示露点
 * 参数		：void
 * 返回值   : void
 * 说明  	：
 * 作者		：张群伟
 * 日期		：[3/29/2017]
 **************************************************************************************/
void Dht11::showdew(void)
{
	Serial.print("Dew PointFast (oC): ");
	Serial.println(dewPointFast(m_temperature, m_humidity));
	delay(350);
}

/**************************************************************************************
 * 函数名	：showKelvin()
 * 功能		：显示开尔文温度
 * 参数		：void
 * 返回值   : void
 * 说明  	：
 * 作者		：张群伟
 * 日期		：[3/29/2017]
 **************************************************************************************/
void Dht11::showKelvin(void)
{
	Serial.print("Temperature (K): ");
	Serial.println(Kelvin(m_temperature), 2);
	delay(350);
}

/**************************************************************************************
 * 函数名	：showFahrenheit()
 * 功能		：显示华氏温度
 * 参数		：void
 * 返回值   : void
 * 说明  	：
 * 作者		：张群伟
 * 日期		：[3/29/2017]
 **************************************************************************************/
void Dht11::showFahrenheit(void)
{
	Serial.print("Temperature (oF): ");
	Serial.println(Fahrenheit(m_temperature), 2);
	delay(350);
}

/**************************************************************************************
 * 函数名	：showHumidity()
 * 功能		：显示湿度
 * 参数		：void
 * 返回值   : void
 * 说明  	：
 * 作者		：张群伟
 * 日期		：[3/29/2017]
 **************************************************************************************/
void Dht11::showHumidity(void)
{
	Serial.print("Humidity (%): ");
	Serial.print((float)m_humidity, 2);
	delay(350);
}

/**************************************************************************************
 * 函数名	：showTemperature()
 * 功能		：显示摄氏温度
 * 参数		：void
 * 返回值   : void
 * 说明  	：
 * 作者		：张群伟
 * 日期		：[3/29/2017]
 **************************************************************************************/
void Dht11::showTemperature(void)
{
	Serial.println();
	Serial.print("Temperature (oC): ");
	Serial.println((float)m_temperature, 2);
	delay(350);
}

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
// 数据处理部分

/**************************************************************************************
 * 函数名	：Kelvin()
 * 功能		：摄氏温度转化为开氏温度
 * 参数		：celsius			摄氏温度
 * 返回值   : celsius + 273.15	开氏温度
 * 说明  	：
 * 作者		：张群伟
 * 日期		：[3/29/2017]
 **************************************************************************************/
double Dht11::Kelvin(double celsius)
{
	return celsius + 273.15;
}

/**************************************************************************************
 * 函数名	：Fahrenheit()
 * 功能		：摄氏温度度转化为华氏温度
 * 参数		：celsius				摄氏温度
 * 返回值   : 1.8 * celsius + 32	华氏温度
 * 说明  	：
 * 作者		：张群伟
 * 日期		：[3/29/2017]
 **************************************************************************************/
double Dht11::Fahrenheit(double celsius)
{
	return 1.8 * celsius + 32;
}

/**************************************************************************************
 * 函数名	：dewPointFast
 * 功能		：快速计算露点
 * 参数		：celsius	摄氏温度
 *			  humidity	湿度
 * 返回值   : Td		露点
 * 说明  	：
 * 作者		：张群伟
 * 日期		：[3/29/2017]
 **************************************************************************************/
double Dht11::dewPointFast(double celsius, double humidity)
{
	double a = 17.271;
	double b = 237.7;
	double temp = (a * celsius) / (b + celsius) + log(humidity / 100);
	double Td = (b * temp) / (a - temp);
	return Td;
}

// dht11.cpp end