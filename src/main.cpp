#include <Arduino.h>

#include <Wire.h>
#include <BH1750.h>
#include <TFT_eSPI.h>

#define SCL_PIN 22
#define SDA_PIN 21

BH1750 lightMeter;
TFT_eSPI display;

void setup()
{

  //Alway initiate a serial connection...
  Serial.begin(9600);

  //Specific initialization of the Wire library: because the bh1750 lib does not do it, and because the board uses non standard pins.
  Wire.begin(SDA_PIN, SCL_PIN);

  //Start the sensor in high res mode.
  lightMeter.begin(BH1750::ONE_TIME_HIGH_RES_MODE);
  display.init();
  Serial.println(F("Setup done"));
}

void loop()
{

  //get the value of the sensor
  float lux = lightMeter.readLightLevel(true);
  Serial.print(F("Light: "));
  Serial.print(lux);
  Serial.println(F(" lx"));

  display.fillScreen(TFT_BLACK);
  display.setTextColor(TFT_GREEN, TFT_BLACK);
  display.setRotation(1);
  display.setCursor(100,60,4);
   
  display.print(lux, 0);
 // display.setTextFont(1);
  display.setCursor(155, 70, 1 );
  display.print(F(" Lux"));

  delay(5000);
}