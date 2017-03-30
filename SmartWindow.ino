/**************************************************************************************
 * Copyright (c) 张群伟. 
 * All rights reserved.	
 * 文件名	：SmartWindow.ino
 * 摘要		：智能窗项目主程序
 * github	：https://github.com/zhangqunwei/SmartWindow.git
 * 作者		：张群伟	南昌航空大学信息工程学院自动化系
 * 日期		：[3/29/2017]
 * 历史记录	：
 *		修改者：   日期：	 版本：	   修改内容：
 *	 1. 张群伟     17/1/10   1.0         创建该项目
 *   2. 张群伟     17/2/25   1.1         添加舵机模块，烟雾检测模块
 **************************************************************************************/



////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
// 头文件包含
#include "Servo.h"
#include "IRremote.h"
#include "Message.h"
#include "sensor.h"
#include "dht11.h"
#include "flame.h"
#include "smoke.h"
#include "people.h"
#include "raindrop.h"
#include "stepper_motor.h"
#include "string.h"



////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
// 引脚定义
CMessage MyBuzzer(7);						// 蜂鸣器
CStepperMotor MyStepperMotor(11, 12, 13);	// 步进电机 (byte clk, byte cw, byte en)

CFlame MyFlame(A0);							// 火焰
CSmoke MySmoke(A1);							// 烟雾
Dht11  MyDht11(6);							// 温湿度
CPeople MyPeople(9);						// 人体
CRaindrop MyRaindrop(8);					// 雨滴	
Servo  MyServo;								// 伺服电机	



////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
// 全局变量
int WindowState = SHUT_WINDOW;
CMessage MySerial;

//- 注意区别：
//- 指针数组 (存储指针的数组) array of pointers         例如：int* a[4]
//- 数组指针 (指向数组的指针) a pointer to an array     例如：int(*a)[4]

CSensor* sensor[5] = { &MySmoke, &MyRaindrop, &MyPeople, &MyFlame, &MyDht11 };
String SensorName[5] = { "MySmoke", "MyRaindrop", "MyPeople", "MyFlame", "MyDht11" };



////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
// 函数声明

// 伺服电机控制
void MyServoControl(int pos);



////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
// 主函数
void setup() {
  // put your setup code here, to run once:
	MyServo.attach(10);	// 伺服电机引脚定义
	MyServo.write(LOW);
	Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:


	// 显示所有传感器采集到的值
	for (int i = 0; i < 5; i++)
	{
		sensor[i]->show();
	}
	Serial.println("------------------------------------------------------------------------------------------------------------");
	Serial.println("***| Num Sensor\t\tRequest\t\tWindowState\t");
	
	// 由传感器的数据产生相应的控制
	for (int i = 0; i < 5; i++)
	{
		if (sensor[i]->monitor() == KEEP_WINDOW)
		{	// 无请求
			Serial.print("***|  ");
			Serial.print(i);
			Serial.print(". ");
			Serial.print(SensorName[i]);
			Serial.print("\tkeep window!\t\t");
			Serial.print(WindowState);   // 1 为开状态  0 为关闭状态
			Serial.println();
			NULL;
		}
		else if ((SHUT_WINDOW == sensor[i]->monitor()) && (WindowState == OPEN_WINDOW))
		{	// 请求关窗
			MyBuzzer.pulse(15, 5);
			delay(2000);
			MyStepperMotor.control(2, CLOCKWISE, EN);	// 顺时针		
			WindowState = SHUT_WINDOW;
			Serial.print("***|  ");
			Serial.print(i);
			Serial.print(". ");
			Serial.print(SensorName[i]);
			Serial.print("\tshut window!\t\t");
			Serial.print(WindowState);
			Serial.println();
		}
		else if ((OPEN_WINDOW == sensor[i]->monitor()) && (WindowState == SHUT_WINDOW))
		{   // 请求开窗
			MyBuzzer.pulse(15, 5);
			delay(2000);
			MyStepperMotor.control(2, UNCLOCKWISE, EN);	// 逆时针
			WindowState = OPEN_WINDOW;
			Serial.print("***|  ");
			Serial.print(i);
			Serial.print(". ");
			Serial.print(SensorName[i]);
			Serial.print("\topen window!\t\t");
			Serial.print(WindowState);
			Serial.println();
		}
		else if (WindowState == sensor[i]->monitor())
		{	// 请求与窗子状态相同时不执行任何动作 
			Serial.print("***|  ");
			Serial.print(i);
			Serial.print(". ");
			Serial.print(SensorName[i]);
			Serial.print("\tNULL!\t\t\t");
			Serial.print(WindowState);
			Serial.println();
			NULL;
		}
	}
	
	Serial.println();
	Serial.println("************************************************************************************************************");
	Serial.println();
	Serial.println();
	Serial.println();

  delay(3000);
	switch (MySerial.monitor())
	{
	case 'o':
		MyBuzzer.pulse(15, 5);
		delay(2000);
		MyStepperMotor.control(2, UNCLOCKWISE, EN);	// 逆时针
		WindowState = OPEN_WINDOW;
		break;
	case 's':
		MyBuzzer.pulse(15, 5);
		delay(2000);
		MyStepperMotor.control(2, CLOCKWISE, EN);	// 顺时针		
		WindowState = SHUT_WINDOW;
		break;
	case 'c':
		MyServoControl(180);
		break;

	default:
		break;
	}
	Serial.println();

	// 伺服电机部分
	if (SHUT_WINDOW == sensor[1]->monitor())
	{
		MyServoControl(180);
	}

} 



////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
// function define

/**************************************************************************************
 * 函数名	：MyServoControl()
 * 功能		：伺服电机控制
 * 参数		：pos	旋转角度
 * 返回值   : void
 * 说明  	：
 * 作者		：张群伟	南昌航空大学信息工程学院自动化系
 * 日期		：[3/29/2017]
 **************************************************************************************/
void MyServoControl(int pos)
{
	int i = 0;
	int count = 5;
	while (count--)
	{
		for (i = 0; i < pos; i += 1)
		{
			MyServo.write(i);
			delay(15);
		}
		for (i = pos; i >= 1; i -= 1)
		{
			MyServo.write(i);
			delay(15);
		}
	}
	
}
