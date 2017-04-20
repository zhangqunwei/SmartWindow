/**************************************************************************************
 * Copyright (c) 张群伟.
 * All rights reserved.
 * 文件名	：stepper_motor.cpp
 * 摘要		：CStepperMotor类的实现
 * 作者		：张群伟	南昌航空大学信息工程学院自动化系
 * 日期		：[3/29/2017]
 * 历史记录	：
 *		修改者：   日期：	 版本：	   修改内容：
 *	1.  张群伟     17/1/10   1.0         创建该模块
 **************************************************************************************/

#include "stepper_motor.h"

////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
// CStepperMotor 构造/析构
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

/**************************************************************************************
 * 函数名	：disattach()
 * 功能		：恢复引脚状态
 * 参数		：void
 * 返回值   : void
 * 说明  	：
 * 作者		：张群伟	南昌航空大学信息工程学院自动化系
 * 日期		：[3/29/2017]
 **************************************************************************************/
void CStepperMotor::disattach(void)
{
	digitalWrite(m_clk, LOW);
	pinMode(m_clk, INPUT);

	digitalWrite(m_cw, LOW);
	pinMode(m_cw, INPUT);

	digitalWrite(m_en, LOW);
	pinMode(m_en, INPUT);
}

/**************************************************************************************
 * 函数名	：get_state()
 * 功能		：读取步进电机的控制状态
 * 参数		：stat
 * 返回值   : void
 * 说明  	：
 * 作者		：张群伟	南昌航空大学信息工程学院自动化系
 * 日期		：[3/29/2017]
 **************************************************************************************/
void CStepperMotor::get_state(StepperMotorState* stat)
{
	stat->clk = digitalRead(m_clk);
	stat->cw = digitalRead(m_cw);
	stat->en = digitalRead(m_en);
}

/**************************************************************************************
 * 函数名	：control()
 * 功能		：步进电机控制
 * 参数		：pulse_width	脉宽控制
 *			  cw			正反转控制	（CLOCKWISE 顺时针，UNCLOCKWISE 逆时针）
 *			  en			使能控制	（EN 使能，UNEN 不使能）
 * 返回值   : void
 * 说明  	：
 * 作者		：张群伟	南昌航空大学信息工程学院自动化系
 * 日期		：[3/29/2017]
 **************************************************************************************/
void CStepperMotor::control(int pulse_width, bool cw, bool en)
{
	// enable control
	if (en)
		digitalWrite(m_en, LOW);  	// enable
	else
		digitalWrite(m_en, HIGH);
	// orientation control
	if (cw) {
		digitalWrite(m_clk, LOW);   // stop
		digitalWrite(m_cw, HIGH);   // clockwise
	}
	else {
		digitalWrite(m_clk, LOW);  	// stop
		digitalWrite(m_cw, LOW);   	// anti-clockwise
	}
	// pulse control
	//!int num_pulse = NUM_PULSE;   // 脉冲数，用于调整窗子打开程度
	if (0 == pulse_width)
		pulse_width = 1;    		// pulse ceiling

	//!while (num_pulse-- > 0)
	if (en)
		for (int i = 50; i > 0; i--)
		{
			digitalWrite(m_clk, HIGH);
			delay(pulse_width);
			digitalWrite(m_clk, LOW);
			delay(pulse_width);
		}
	while (0x0 != digitalRead(7) && 0x0 != digitalRead(8))
	{
		digitalWrite(m_clk, HIGH);
		delay(pulse_width);
		digitalWrite(m_clk, LOW);
		delay(pulse_width);
	}
}
// stepper_motor.cpp end
