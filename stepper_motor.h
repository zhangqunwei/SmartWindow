/**************************************************************************************
 * Copyright (c) 张群伟. 
 * All rights reserved.	
 * 文件名	：stepper_motor.h
 * 摘要		：CStepperMotor类的接口
 * 作者		：张群伟	南昌航空大学信息工程学院自动化系
 * 日期		：[3/29/2017]
 * 历史记录	：
 *		修改者：   日期：	 版本：	   修改内容：
 *	 1. 张群伟     17/1/10  1.0         创建该模块	
 **************************************************************************************/

#ifndef _STEPPERMOTOR_H__
#define _STEPPERMOTOR_H__

#if defined(ARDUINO) && (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#define  NUM_PULSE      1000	// 脉冲数，用于调整步进电机的步进距离
#define  CLOCKWISE		0		// 顺时针
#define  UNCLOCKWISE    1		// 逆时针
#define  EN				1		// 使能
#define  UNEN			0		// 不使能

/**************************************************************************************
 * 结构体名	：SMS(StepperMotorState)	
 * 功能		：保存步进电机的状态
 * 参数		：clk 脉冲
 *			  cw  转向
 *			  en  使能
 * 说明  	：
 * 作者		：张群伟 	南昌航空大学信息工程学院自动化系
 * 日期		：[3/29/2017]
 **************************************************************************************/
typedef struct SMS
{
  byte clk;
  byte cw;
  byte en;
} StepperMotorState;

/**************************************************************************************
 * 类名称	：CStepperMotor
 * 功能		：CStepperMotor提供步进电机的驱动接口。
 * 当前版本 ：1.0
 * 作者		：张群伟	南昌航空大学信息工程学院自动化系
 * 日期		：[3/29/2017]
 **************************************************************************************/
class CStepperMotor
{
  private:
	byte m_clk;   // pulse		connect clk pin of Tb6560.
	byte m_cw;    // direction	connect cw pin of Tb6560.
	byte m_en;    // enable 	connect clk pin of Tb6560.

  public:
	// initialise pulse, direction, enable
	CStepperMotor(byte clk, byte cw, byte en);

	~CStepperMotor();

  public:
	void control(int pulse, bool cw, bool en); 	// control stepper motor
	void get_state(StepperMotorState* stat);    // get stepper motor state
	void disattach();                         	// free pin and stepper motor of binding，
												// so as to control other thing of pin
};

#endif
// stepper_motor.h end
