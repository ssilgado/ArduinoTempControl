#include <Arduino.h>
#include <IRremote.hpp>
#include <ac_LG.hpp>
#include <Wire.h>
#include "main.hpp"


#define DECODE_LG
#define IR_RECEIVE_PIN 3
#define IR_SEND_PIN 5

#define TEMPERATURE_PIN 0

#define ON_OFF_BUTTON_PIN 13
#define HEATER_AC_BUTTON_PIN 12

// Defining the most efficient AC temperatures
#define HEAT_TEMP 30
#define COOL_TEMP 18

Aircondition_LG MyLG_Airconditioner;

void setup()
{
  // Initialize the serial monitor
  Serial.begin(115200);

  // Initialize the LG Airconditioner initial state
  MyLG_Airconditioner.ACIsWallType = true;
  MyLG_Airconditioner.Mode = AC_MODE_COOLING;
  MyLG_Airconditioner.Temperature = 18;
  MyLG_Airconditioner.FanIntensity = 4;

  // Initialize the IRremote receiver and sender
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  IrSender.begin(IR_SEND_PIN, ENABLE_LED_FEEDBACK);

  // Initialize manual control buttons
  pinMode(ON_OFF_BUTTON_PIN, INPUT);
  pinMode(HEATER_AC_BUTTON_PIN, INPUT);

  // Initialize the I2C bus
  Wire.begin(4);
  Wire.onReceive(receiveEvent);
}

void receiveEvent(int howMany)
{
  int x = Wire.read();
  if (x == 1)
  {
    togglePowerState();
  }
}

void loop()
{
  // Check if on/off button is pressed and switch the AC state
  if (digitalRead(ON_OFF_BUTTON_PIN) == LOW)
  {
    togglePowerState();
    delay(500);
  }

  // Check if the AC/Heater button is pressed and switch the AC/Heater mode
  if (digitalRead(HEATER_AC_BUTTON_PIN) == LOW)
  {
    toggleACMode();
    delay(500);
  }
}

void togglePowerState()
{
  bool ACState = MyLG_Airconditioner.PowerIsOn;
  if (MyLG_Airconditioner.sendCommandAndParameter(ACState ? LG_COMMAND_OFF : LG_COMMAND_ON, 0))
  {
    Serial.print("AC state switched to ");
    Serial.println(ACState ? "OFF" : "ON");
  }
}

void toggleACMode()
{
  if (MyLG_Airconditioner.Mode == AC_MODE_COOLING)
    {
      MyLG_Airconditioner.Temperature = HEAT_TEMP;
      if (MyLG_Airconditioner.sendCommandAndParameter(LG_COMMAND_MODE, AC_MODE_HEATING))
      {
        MyLG_Airconditioner.Mode = AC_MODE_HEATING; // Must manually set the mode to HEATING if command is successful
      }
    }
    else if (MyLG_Airconditioner.Mode == AC_MODE_HEATING)
    {
      MyLG_Airconditioner.Temperature = COOL_TEMP;
      if (MyLG_Airconditioner.sendCommandAndParameter(LG_COMMAND_MODE, AC_MODE_COOLING))
      {
        MyLG_Airconditioner.Mode = AC_MODE_COOLING; // Must manually set the mode to COOLING if command is successful
      }
    }

    // Print the current AC/Heater mode
    Serial.print("AC/Heater mode is ");
    Serial.println(MyLG_Airconditioner.Mode == AC_MODE_COOLING ? "COOLING" : "HEATING");
}