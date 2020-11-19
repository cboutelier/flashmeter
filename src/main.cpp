#include <Arduino.h>

#include <Wire.h>
#include <BH1750.h>

#define SCL_PIN 22
#define SDA_PIN 21

BH1750 lightMeter;

void setup()
{

  //Alway initiate a serial connection...
  Serial.begin(9600);

  //Specific initialization of the Wire library: because the bh1750 lib does not do it, and because the board uses non standard pins.
  Wire.begin(SDA_PIN, SCL_PIN);

  //Start the sensor in high res mode.
  lightMeter.begin(BH1750::ONE_TIME_HIGH_RES_MODE);

  Serial.println(F("Setup done"));
}

void loop()
{

  //get the value of the sensor
  float lux = lightMeter.readLightLevel(true);
  Serial.print(F("Light: "));
  Serial.print(lux);
  Serial.println(F(" lx"));

  delay(5000);
}