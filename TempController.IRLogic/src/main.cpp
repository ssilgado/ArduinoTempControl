#include <Arduino.h>
#include <IRremote.hpp>
#include <ac_LG.hpp>


#define DECODE_LG
#define IR_RECEIVE_PIN 3
#define IR_SEND_PIN 5

#define TEMPERATURE_PIN 0

#define ON_OFF_BUTTON_PIN 13
#define HEATER_AC_BUTTON_PIN 12

Aircondition_LG MyLG_Airconditioner;

void setup()
{
  // Just to know which program is running
  Serial.begin(115200);

  // Initialize the LG Airconditioner
  MyLG_Airconditioner.ACIsWallType = true;
  MyLG_Airconditioner.Mode = AC_MODE_COOLING;
  MyLG_Airconditioner.Temperature = 18;
  MyLG_Airconditioner.FanIntensity = 4;

  // Initialize the IRremote receiver and sender
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  IrSender.begin(IR_SEND_PIN, ENABLE_LED_FEEDBACK);

  // Initialize buttons
  pinMode(ON_OFF_BUTTON_PIN, INPUT);
  pinMode(HEATER_AC_BUTTON_PIN, INPUT);
}

void loop()
{
  // Check if on/off button is pressed and switch the AC state
  if (digitalRead(ON_OFF_BUTTON_PIN) == LOW)
  {
    bool ACState = MyLG_Airconditioner.PowerIsOn;
    if (MyLG_Airconditioner.sendCommandAndParameter(ACState ? LG_COMMAND_OFF : LG_COMMAND_ON, 0))
    {
      Serial.print("AC state switched to ");
      Serial.println(ACState ? "OFF" : "ON");
    }
    delay(500);
  }

  // Check if the AC/Heater button is pressed and switch the AC/Heater mode
  if (digitalRead(HEATER_AC_BUTTON_PIN) == LOW)
  {
    if (MyLG_Airconditioner.Mode == AC_MODE_COOLING)
    {
      Serial.println(MyLG_Airconditioner.Mode);
      MyLG_Airconditioner.Temperature = 30;
      if (MyLG_Airconditioner.sendCommandAndParameter(LG_COMMAND_MODE, AC_MODE_HEATING))
      {
        Serial.println("AC/Heater mode switched to HEATER");
        MyLG_Airconditioner.Mode = AC_MODE_HEATING;
      }
    }
    else if (MyLG_Airconditioner.Mode == AC_MODE_HEATING)
    {
      Serial.println(MyLG_Airconditioner.Mode);
      MyLG_Airconditioner.Temperature = 18;
      if (MyLG_Airconditioner.sendCommandAndParameter(LG_COMMAND_MODE, AC_MODE_COOLING))
      {
        Serial.println("AC/Heater mode switched to COOLING");
        MyLG_Airconditioner.Mode = AC_MODE_COOLING;
      }
    }else{
      Serial.print("AC/Heater mode is ");
      Serial.println(MyLG_Airconditioner.Mode);
    }
    delay(500);
  }
}