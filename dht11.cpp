// dht11.cpp : implementation of the Dht11 class
// Copyright (c) 张群伟. All rights reserved.
// Version 	：1.0
// Author  	：张群伟	南昌航空大学信息工程学院自动化系
// Date    	：2017-1-13
// Brief    ：温湿度传感器类的实现
//
/////////////////////////////////////////////////////////////////////////////

#include "dht11.h"

#define VALUEMIN	0
#define VALUEMAX	1
#define VALUENORMAL 2
/////////////////////////////////////////////////////////////////////////////
// Dht11 construction/destruction
Dht11::Dht11(int dht_pin)
{
	m_pin = dht_pin;
}

/////////////////////////////////////////////////////////////////////////////
//数据读取，监测部分

// Function: read()
// Description: 读取温湿度
// Input: 无
// Output: 无
// Return:	DHT11_ERROR_TIMEOUT		超时
//			DHT11_ERROR_CHECKSUM	校验和错误
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
  while (digitalRead(m_pin)==LOW)
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

	  if ((micros()-t)>40)
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
  m_humidity    = bits[0];
  m_temperature = bits[2];

  // 校验和
  uint8_t sum = bits[0] + bits[2];
  if (bits[4] != sum) return DHT11_ERROR_CHECKSUM;

} // int Dht11::read()  END


// struct   : ValueExtent
// Function	: ValueExtent用于存储温湿度检测范围的数据
// Variable declaration:	
//			type  检测数据类型
//					取值：'H' 湿度， 'T' 温度， 'D' 露点
//			min	  最小值
//			max   最大值
// Version	：1.0
// Author	：张群伟	南昌航空大学信息工程学院自动化系
// Date		：2017-2-26
typedef	struct
{
	char type;
	float min;
	float max;
}ValueExtent;

ValueExtent value[3] = {{ 'T', 5, 25 },	// 温度的监控范围
						{ 'H', 5, 80 }, // 湿度的监控范围
						{ 'D', -20, 20 } 	// 露点的监控范围
						};	
						 

// Function: monitor()
// Description: 监测温湿度
// Input:  无
// Output: 无
// Return:	OPEN_WINDOW  开窗
//			SHUT_WINDOW  关窗
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

// Function: DetectonExtent()
// Description: 检测数据类型为m_value_type的数据是否在范围(m_value_min, m_value_max)内
// Input:	m_value_type  检测数据类型
//					取值：'H' 湿度， 'T' 温度， 'D' 露点
//			m_value_min	  最小值
//			m_value_max   最大值
// Output: 无
// Return:	VALUEMIN 小于最小值
// 			VALUEMAX 大于最大值
int Dht11::DetectonExtent(char m_value_type, float m_value_min, float m_value_max)
{
	// 监测最新值
	switch (m_value_type)
	{
	case 'H':
		if ((float)m_humidity * 100 < m_value_min * 100)
			return VALUEMIN;
		if ((float)m_humidity > m_value_max)
			return VALUEMAX;
		break;

	case 'T':
		if ((float)m_temperature * 100 < m_value_min * 100)
			return VALUEMIN;
		if ((float)m_temperature>m_value_max)
			return VALUEMAX;
		break;

	case 'D':
		if (dewPointFast(m_temperature, m_humidity) * 100 < m_value_min * 100)
			return VALUEMIN;
		if (dewPointFast(m_temperature, m_humidity) > m_value_max)
			return VALUEMAX;
		break;

	default:
		return VALUENORMAL;
		break;
	}
} // DetectonExtent() end

/////////////////////////////////////////////////////////////////////////////
// 数据显示部分

// Function: show()
// Description: 显示温湿度
// Input: 无
// Output: 无
// Return: 无
void Dht11::show()
{
	read();
	if (m_value == DHT11_ERROR_CHECKSUM) 
		Serial.println("dht11 checksum error!");
	else
	{
		Serial.print("***|	Dht11: ");

		Serial.print("\tTemperature (oC):");
		Serial.print((float)m_temperature, 2);

		//Serial.print("\t(oF): ");
		//Serial.print(Fahrenheit(m_temperature), 2);

		//Serial.print("\t(K): ");
		//Serial.print(Kelvin(m_temperature), 2);

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
	delay(50);
}	// void Dht11::show() END

// 显示露点
void Dht11::showdew()
{
  Serial.print("Dew PointFast (oC): ");
  Serial.println(dewPointFast(m_temperature, m_humidity));
  delay(350);
}

// 显示开尔文温度
void Dht11::showKelvin()
{
  Serial.print("Temperature (K): ");
  Serial.println(Kelvin(m_temperature), 2);
  delay(350);
}

// 显示华氏温度
void Dht11::showFahrenheit()
{
  Serial.print("Temperature (oF): ");
  Serial.println(Fahrenheit(m_temperature), 2);
  delay(350);
}

// 显示湿度
void Dht11::showHumidity()
{
  Serial.print("Humidity (%): ");
  Serial.print((float)m_humidity, 2);
  delay(350);
}

// 显示摄氏温度
void Dht11::showTemperature()
{
  Serial.println();
  Serial.print("Temperature (oC): ");
  Serial.println((float)m_temperature, 2);
  delay(350);
}


/////////////////////////////////////////////////////////////////////////////
// 数据处理部分

// 摄氏温度转化为开氏温度
double Dht11::Kelvin(double celsius)
{
  return celsius + 273.15;
}

// 摄氏温度度转化为华氏温度
double Dht11::Fahrenheit(double celsius)
{
  return 1.8 * celsius + 32;
}

// 快速计算露点
double Dht11::dewPointFast(double celsius, double humidity)
{
  double a = 17.271;
  double b = 237.7;
  double temp = (a * celsius) / (b + celsius) + log(humidity / 100);
  double Td = (b * temp) / (a - temp);
  return Td;
}

// dht11.cpp end
