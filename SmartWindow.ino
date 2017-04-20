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
// 调试

// 开关
#define open			1
#define shut			0

// 舵机开关
#define _zqwdebug_Servo			open

// 风扇开关
#define _zqwdebug_fan			open

// 传感器开关
#define _zqwdebug_smoke_		open
#define _zqwdebug_raindrop_		open
#define _zqwdebug_people_		open
#define _zqwdebug_flame_		open
#define _zqwdebug_dht11_		open

#define _zqwdebug_sensor(i) 	if(!_zqwdebug_smoke_) ++i;\
if (!_zqwdebug_raindrop_) ++i;\
if (!_zqwdebug_people_)	++i;\
if (!_zqwdebug_flame_) ++i;\
if (!_zqwdebug_dht11_) ++i\
	
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
// 头文件包含
#if _zqwdebug_Servo
#include "Servo.h"
#endif
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
CMessage MyBuzzer(12);						// 蜂鸣器
CStepperMotor MyStepperMotor(2, 3, 4);	// 步进电机 (byte clk, byte cw, byte en)

CFlame MyFlame(A4);							// 火焰
CSmoke MySmoke(A5);							// 烟雾
Dht11  MyDht11(13);							// 温湿度
CPeople MyPeople(9);						// 人体
CRaindrop MyRaindrop(11);					// 雨滴

#if _zqwdebug_Servo
Servo  MyServo;								// 伺服电机
#endif
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
// 全局变量
int WindowState(SHUT_WINDOW);
int FanFlag(LOW);
int ServoFlag(0);
CMessage MySerial;

//- 注意区别：
//- 指针数组 (存储指针的数组) array of pointers         例如：int* a[4]
//- 数组指针 (指向数组的指针) a pointer to an array     例如：int(*a)[4]

CSensor* sensor[5] = { &MySmoke, &MyRaindrop, &MyPeople, &MyFlame, &MyDht11 };
String SensorName[5] = { "MySmoke", "MyRaindrop", "MyPeople", "MyFlame", "MyDht11" };

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
// 函数声明
#if _zqwdebug_Servo
// 伺服电机控制
void MyServoControl(int pos);
#endif

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
// 主函数
void setup() {
	// put your setup code here, to run once:
	//!引脚定义
#if _zqwdebug_Servo
	// 伺服电机引脚
	MyServo.attach(10);	
	MyServo.write(LOW);
#endif
	// 限位开关引脚（不分左右）
	pinMode(7, OUTPUT);
	digitalWrite(7, LOW);
	pinMode(7, INPUT);

	pinMode(8, OUTPUT);
	digitalWrite(8, LOW);
	pinMode(8, INPUT);

	// 风扇引脚
	pinMode(6, OUTPUT);
	digitalWrite(6, LOW);

	// 串口波特率
	Serial.begin(9600);
	
	// 关闭步进电机
	digitalWrite(4, HIGH);
	//MyStepperMotor.control(2, CLOCKWISE, UNEN);	
}

void loop() {
	// put your main code here, to run repeatedly:

	// 显示所有传感器采集到的值
	for (int i = 0; i < 5; i++)
	{
		sensor[i]->show();
	}
	Serial.println();
	Serial.println("************************************************************************************************************");
	Serial.println();

	//Serial.println("------------------------------------------------------------------------------------------------------------");
	Serial.println("***| Num Sensor\t\tRequest\t\tWindowState(1 open : 0 shut)\t");

	// 由传感器的数据产生相应的控制
	for (int i = 0; i < 5; i++)
	{
		_zqwdebug_sensor(i);
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
			ServoFlag = 0;
			MyBuzzer.pulse(15, 5);
			delay(2000);
			MyStepperMotor.control(2, UNCLOCKWISE, EN);	// 逆时针
#if _zqwdebug_fan
			if (i == 0) digitalWrite(6, HIGH);
#endif
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
	case 'o':// 开窗
		MyBuzzer.pulse(15, 5);
		delay(5000);
		MyStepperMotor.control(2, CLOCKWISE, EN);	
		WindowState = OPEN_WINDOW;
		break;
	case 's':// 关窗
		MyBuzzer.pulse(15, 5);
		delay(5000);
		MyStepperMotor.control(2, UNCLOCKWISE, EN);
		WindowState = SHUT_WINDOW;
		break;
#if _zqwdebug_Servo
	case 'c':// 清洗
		ServoFlag = 1;
		delay(5000);
		break;
	case 'k':// 关闭清洗
		ServoFlag = 0;
		delay(5000);
		break;
#endif
#if _zqwdebug_fan
	case 'f':// 打开风扇
		FanFlag = HIGH;
		delay(5000);
		break;
	case 'g':// 关闭风扇
		FanFlag = LOW;
		delay(5000);
		break;
#endif
	default:
		break;
	}
	Serial.println();
	if (ServoFlag)
	{
		for (int i(0); i < 180; i += 1)
		{
			MyServo.write(i);
			delay(10);
		}
		for (int i(180); i >= 1; i -= 1)
		{
			MyServo.write(i);
			delay(10);
		}
		ServoFlag++;
		// 清洗4次后自动关闭清理
		if (ServoFlag == 5)
		{
			ServoFlag = 0;
		}
	}
	else
	{
		MyServo.write(LOW);
	}

	digitalWrite(6, FanFlag);
	// 关闭步进电机
	//MyStepperMotor.control(2, CLOCKWISE, UNEN);
}

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
// function define

#if false
/**************************************************************************************
 * 函数名	：MyServoControl()
 * 功能		：伺服电机控制
 * 参数		：pos	旋转角度
 * 返回值   : void
 * 说明  	：
 * 作者		：张群伟	南昌航空大学信息工程学院自动化系
 * 日期		：[3/29/2017]
 **************************************************************************************/
inline void MyServoControl(int pos)
{
	int i = 0;
	int count = 5;
	while (count--)
	{
		for (i = 0; i < pos; i += 1)
		{
			MyServo.write(i);
			delay(10);
		}
		for (i = pos; i >= 1; i -= 1)
		{
			MyServo.write(i);
			delay(10);
		}
	}
}
#endif
