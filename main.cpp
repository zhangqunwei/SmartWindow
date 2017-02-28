// SmartWindow.ino : Project master file of the Smart Window
// Copyright (c) 张群伟. All rights reserved.
// Version  ：1.0
// Author   ：张群伟  南昌航空大学信息工程学院自动化系
// Date     ：2017-1-10
// Brief    ：智能窗项目的主程序
//
/////////////////////////////////////////////////////////////////////////////

#include "dht11.h"
#include "flame.h"
#include "people_sensor.h"
#include "stepper_motor.h"
#include <Arduino.h>
//    pin define
byte   Buzzer = 2;            // buzzer
PeopleSensor PS(4);           // people sensor
CFlame  FL(A0);                // flame sensor
Dht11  DH(3);                 // temperature-humidity sensor
StepperMotor SM(13, 12, 11);  // stepper-motor module   SM(byte clk, byte cw, byte en)

//    function declare
void BUZZER();
void Scan();
void Show();

byte count = 200;

void setup() {
  // put your setup code here, to run once:
  pinMode(Buzzer, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Scan();
  Show();
} // loop() end

void BUZZER()
{
  int count = 2;
  while (count--)
  {
    digitalWrite(Buzzer, HIGH);
    delay(100);
    digitalWrite(Buzzer,  LOW);
    delay(100);
  }
}

void Scan()
{
  //Temperature-Humidity sensor
  DH.read();
  if ( true == DH.scan() )   // temperature-humidity scan
  {
    BUZZER();
    //void StepperMotorControl(int pulse, bool cw, bool en);
    SM.control( 2, OPEN, ON );
  }

  // People Sensor scan
  if ( true == PS.scan() )
  {
    BUZZER();
    SM.control( 2, OPEN, ON );
  }

  // Flame Sensor scan
  if ( true == FL.scan() )
  {
    BUZZER();
    SM.control( 2, OPEN, ON );
  }
}

void Show()
{
  DH.show();
  FL.show();
  PS.show();
}