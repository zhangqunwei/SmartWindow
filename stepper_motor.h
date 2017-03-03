// Copyright (c) 张群伟. 
// All rights reserved.
//
// FileName:stepper_motor.h 
// Summary: interface of the CStepperMotor class
// 
// Author: 张群伟    Version: 1.0    Date:2017/1/10
// History: 
//     Author:    Date:    Version:    Modification: 
//  1. 张群伟     17/1/10  1.0         创建该模块
//
/////////////////////////////////////////////////////////////////////////////

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

// save stepper motor state
typedef struct SMS
{
  byte clk;
  byte cw;
  byte en;
} StepperMotorState;


// Class   	: CStepperMotor
// Function	: CStepperMotor提供步进电机的驱动接口。
// Version	：1.0
// Author	：张群伟	南昌航空大学信息工程学院自动化系
// Date		：2017-1-10
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
	void get_state(StepperMotorState s);        // get stepper motor state
    void disattach();                         	// free pin and stepper motor of binding，
												// so as to control other thing of pin
};

#endif
// stepper_motor.h end
