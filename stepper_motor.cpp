// Copyright (c) 张群伟. 
// All rights reserved.
//
// FileName: stepper_motor.cpp
// Summary:  implementation of the CStepperMotor class 
//
// Author: 张群伟    Version: 1.0    Date:2017/1/10
// History: 
//     Author:    Date:    Version:    Modification:
// 1.  张群伟     17/1/10   1.0         创建该模块 
//
/////////////////////////////////////////////////////////////////////////////

#include "stepper_motor.h"

/////////////////////////////////////////////////////////////////////////////
// CStepperMotor construction/destruction
CStepperMotor::CStepperMotor(byte clk, byte cw, byte en)
  : m_clk(clk), m_cw(cw), m_en(en)
{
	pinMode(m_clk, OUTPUT);
	digitalWrite(m_clk, LOW);

	pinMode(m_cw, OUTPUT);
	digitalWrite(m_cw, LOW);     // anti-clockwise

	pinMode(m_en, OUTPUT);
	digitalWrite(m_en, HIGH);    // unable
}

CStepperMotor::~CStepperMotor()
{
	disattach();
}

// pin recover，come back to power up state
void CStepperMotor::disattach()
{
  digitalWrite(m_clk, LOW);
  pinMode(m_clk, INPUT);

  digitalWrite(m_cw, LOW);
  pinMode(m_cw, INPUT);

  digitalWrite(m_en, LOW);
  pinMode(m_en, INPUT);
}

// Function: get_state()
// Description: 读取步进电机的控制状态
// Input: s
// Output: 无
// Return: 无
void CStepperMotor::get_state(StepperMotorState stat)
{
  stat.clk = digitalRead(m_clk);
  stat.cw  = digitalRead(m_cw);
  stat.en  = digitalRead(m_en);
}

// Function: control()
// Description: 步进电机控制
// Input:	pulse_width	脉宽控制
//			cw			正反转控制	（CLOCKWISE 顺时针，UNCLOCKWISE 逆时针）
//			en			使能控制	（EN 使能，UNEN 不使能）
// Output: 无
// Return: 无
void CStepperMotor::control(int pulse_width, bool cw, bool en)
{
  // enable control
  if ( en )
    digitalWrite( m_en, LOW);  	// enable
  else
    digitalWrite( m_en, HIGH);
  // orientation control
  if ( cw ) {
    digitalWrite( m_clk, LOW);   // stop
    digitalWrite( m_cw, HIGH);   // clockwise
  }
  else {
    digitalWrite( m_clk, LOW);  	// stop
    digitalWrite( m_cw, LOW);   	// anti-clockwise
  }
  // pulse control
  byte num_pulse = 200;   // 脉冲数，用于调整窗子打开程度
  if ( 0 == pulse_width ) 
	  pulse_width = 1;    		// pulse ceiling

  while (num_pulse-- > 0)
  {
    digitalWrite( m_clk, HIGH);
    delay(pulse_width);
    digitalWrite( m_clk, LOW);
    delay(pulse_width);
  }
}
// stepper_motor.cpp end
