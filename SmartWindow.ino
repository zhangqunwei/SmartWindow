// Copyright (c) 张群伟. 
// All rights reserved.
//
// FileName:SmartWindow.ino 
// Summary: 智能窗项目主程序
// 
// Author: 张群伟    Version: 1.0    Date:2017/1/10
// History: 
//     Author:    Date:    Version:    Modification: 
//  1. 张群伟     17/1/10  1.0         创建该项目
//  2. 张群伟     17/2/25  1.1         添加舵机模块，烟雾检测模块
/////////////////////////////////////////////////////////////////////////////

#include <Servo.h>
#include <IRremote.h>
#include "notify.h"
#include "sensor.h"
#include "dht11.h"
#include "flame.h"
#include "smoke.h"
#include "people.h"
#include "raindrop.h"
#include "stepper_motor.h"
#include "string.h"

/////////////////////////////////////////////////////////////////////////////
// 传感器对象定义
Dht11  MyDht11(2);		// 温湿度
CFlame MyFlame(A0);		// 火焰
CSmoke MySmoke(A1);		// 烟雾
CPeople MyPeople(5);	// 人体
CRaindrop MyRaindrop(4);// 雨滴

CNotify MyBuzzer(3);	// 蜂鸣器	
Servo  myservo;			// 伺服电机
CStepperMotor MyStepperMotor(11, 12, 13);	// 步进电机 (byte clk, byte cw, byte en)
											
int WindowState = SHUT_WINDOW;

/////////////////////////////////////////////////////////////////////////////
// 函数声明
void MyServoControl(int pos);

// 注意区别：
// 指针数组 (存储指针的数组) array of pointers         例如：int* a[4]
// 数组指针 (指向数组的指针) a pointer to an array     例如：int(*a)[4]

// 指针数组
CSensor* sensor[5] = { &MySmoke, &MyRaindrop, &MyPeople, &MyFlame ,&MyDht11 };
String SensorName[5] = { "MySmoke", "MyRaindrop", "MyPeople", "MyFlame", "MyDht11"};

/////////////////////////////////////////////////////////////////////////////
// main
void setup() {
  // put your setup code here, to run once:
	myservo.attach(6);	// 伺服电机引脚定义
	Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

	// 显示所有传感器采集到的值
	for (int i = 0; i < 5; i++)
	{
		sensor[i]->show();
	}

	// 伺服电机部分
	//MyServoControl(360);
	Serial.println("------------------------------------------------------------------------------------------------------------");
	Serial.println("***| Num Sensor\t\tRequest\t\tWindowState\t");
	// 由传感器的数据产生相应的控制
	for (int i = 0; i < 5; i++)
	{
		if (sensor[i]->monitor() == KEEP_WINDOW)
		{
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
			MyStepperMotor.control(2, CLOCKWISE, EN);	// 顺时针
			MyBuzzer.notify(15, 5);
			//delay(200);
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
			MyStepperMotor.control(2, UNCLOCKWISE, EN);	// 逆时针
			MyBuzzer.notify(15, 5);
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
	Serial.println();
	delay(3000);
	//// 检测到人 
	//if (MyPeople.monitor() == true)
	//{
	//	MyStepperMotor.control(2, CLOCKWISE, EN);
	//	
	//}
	//// 检测到失火
	//if (MyFlame.monitor(0, 150) == 0 || MyFlame.monitor(0, 150) == 150)
	//{
	//	MyStepperMotor.control(2, CLOCKWISE, EN);
	//	
	//}
	//// 检测到气体泄漏
	//if (MySmoke.monitor(0, 60) == 0 || MySmoke.monitor(0, 150) == 150)
	//{
	//	MyStepperMotor.control(2, CLOCKWISE, EN);

	//}

	//// 检测到下雨
	//if (true == MyRaindrop.monitor())
	//{

	//}

	//// 温湿度监控 
	//if (MyDht11.monitor('T', 0, 20) == 18 || MyDht11.monitor('T', 0, 20) == 20)
	//{
	//	MyStepperMotor.control(2, CLOCKWISE, EN);
	//	
	//}
} 


/////////////////////////////////////////////////////////////////////////////
// function define

// 伺服电机控制
void MyServoControl(int pos)
{
	int i = 0;
	for (i = 0; i <  pos; i += 1)
	{
		myservo.write(i);
		delay(15);
	}
	for (i = pos; i >= 1; i -= 1)
	{
		myservo.write(i);
		delay(15);
	}
}