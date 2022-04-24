// Imports
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <Wire.h>
#include "main.hpp"

#include "config.h"

String getRequest;

void setup()
{
  // Setup serial port monitor baud
  Serial.begin(115200);
  Serial.println();

  // Initialize WiFi connection
  setupWifi();

  // Initialize the I2C bus
  Wire.begin();
}

void loop()
{
  Wire.beginTransmission(4);
  Wire.write(0x01);
  Wire.endTransmission();
  delay(5000);
}

void setupWifi()
{
  // Initialize WiFi connection
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  // Connecting to WiFi...
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) // Loop continuously while WiFi is not connected
  {
    delay(500);
    Serial.print(".");
  }

  // Connected to WiFi
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
}
