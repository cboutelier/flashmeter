#include <Arduino.h>
#include <EEPROM.h>
#include <Wire.h>
#include <SPI.h>
#include <FS.h>
#include <SPIFFS.h>

#define SCL_PIN 22
#define SDA_PIN 21
#define SET_PIN 0
#define OK_PIN 13
#define UP_PIN 32
#define LEFT_PIN 15
#define RIGHT_PIN 2
#define DOWN_PIN 12
#define BACK_PIN 35

const int DEBOUNCE_DELAY = 500;
const int READING_TIMEOUT = 20000;

void setup()
{

  Serial.println(F("Setup done"));
}

void loop()
{
}
