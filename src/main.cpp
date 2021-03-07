#include <Arduino.h>
#include <EEPROM.h>

#include <Wire.h>
#include <BH1750.h>
#include <TFT_eSPI.h>
#include "gui/gui_controller.h"
#include "gui/setting_page.h"
#include "gui/flashmeter_model.h"

#define SCL_PIN 22
#define SDA_PIN 21
#define SET_PIN 0
#define OK_PIN 13
#define UP_PIN 32
#define LEFT_PIN 15
#define RIGHT_PIN 2
#define DOWN_PIN 12

const int DEBOUNCE_DELAY = 1000;
const int READING_TIMEOUT = 30000;

BH1750 lightMeter;
TFT_eSPI display;
GuiController *guiController;
FlashMeterModel *model;

bool toSave = false;
bool upCommand = false;
bool downCommand = false;
bool rightCommand = false;
bool leftCommand = false;
bool settingsCommand = false;
bool okCommand = false;

unsigned long lastButtonAction = 0;

void IRAM_ATTR onSettingClick();
void IRAM_ATTR onOkClick();
void IRAM_ATTR onUpClick();
void IRAM_ATTR onDownClick();
void IRAM_ATTR onRightClick();
void IRAM_ATTR onLeftClick();

void IRAM_ATTR attachInterrupts();
void IRAM_ATTR detachInterrupts();
 
void manageCommands();
void setup()
{

  //Alway initiate a serial connection...
  Serial.begin(9600);
  EEPROM.begin(512);

  //declare pin for settings as Input
  pinMode(SET_PIN, INPUT_PULLUP);
  pinMode(OK_PIN, INPUT_PULLUP);
  pinMode(UP_PIN, INPUT_PULLUP);
  pinMode(DOWN_PIN, INPUT_PULLUP);
  pinMode(RIGHT_PIN, INPUT_PULLUP);
  pinMode(LEFT_PIN, INPUT_PULLUP);

  //Specific initialization of the Wire library: because the bh1750 lib does not do it, and because the board uses non standard pins.
  Wire.begin(SDA_PIN, SCL_PIN);

  //Start the sensor in high res mode.
  lightMeter.begin(BH1750::ONE_TIME_HIGH_RES_MODE);

  model = new FlashMeterModel();
  model->setAttachCallback( &attachInterrupts);
  model->setDetachCallback( &detachInterrupts);

  guiController = new GuiController(&display, model);

 
  // SettingPage settings;
  //gui->addPage(&settings);

  attachInterrupts();

  Serial.println(F("Setup done"));
}
 


void IRAM_ATTR attachInterrupts()
{
  attachInterrupt(SET_PIN, onSettingClick, RISING);
  attachInterrupt(UP_PIN, onUpClick, RISING);
  attachInterrupt(DOWN_PIN, onDownClick, RISING);
  attachInterrupt(RIGHT_PIN, onRightClick, RISING);
  attachInterrupt(LEFT_PIN, onLeftClick, RISING);
  attachInterrupt(OK_PIN, onOkClick, RISING);
}

void IRAM_ATTR detachInterrupts()
{
  detachInterrupt(SET_PIN);
  detachInterrupt(UP_PIN);
  detachInterrupt(DOWN_PIN);
  detachInterrupt(RIGHT_PIN);
  detachInterrupt(LEFT_PIN);
  detachInterrupt(OK_PIN);
}

void loop()
{

  if (millis() - lastButtonAction > READING_TIMEOUT)
  {
    guiController->off();
  }

  manageCommands();

  delay(100);
}

void manageCommands()
{
  if (okCommand)
  {
   guiController->onOkClick();
   okCommand = false;
   }
  if (upCommand)
  {
    guiController->onUpClick();
    upCommand = false;
  }
  else if (downCommand)
  {
    guiController->onDownClick();
    downCommand = false;
  }
  else if (rightCommand)
  {
    guiController->onRightClick();
    rightCommand = false;
  }
  else if (leftCommand)
  {
    guiController->onLeftClick();
    leftCommand = false;
  }
  else if (settingsCommand)
  {
    guiController->onSettingClick();
    settingsCommand = false;
  }
}

/*
* Transmit the click on the setting button to the gui for further action
*/
void IRAM_ATTR onSettingClick()
{
  if ((millis() - lastButtonAction) > DEBOUNCE_DELAY)
  {
    lastButtonAction = millis();
    settingsCommand = true;
  }
}

void IRAM_ATTR onOkClick()
{

  /*
  if ((millis() - lastButtonAction) > DEBOUNCE_DELAY)
  {
    Serial.println("Measuring...");

    //get the value of the sensor
    float lux = lightMeter.readLightLevel(true);
    Serial.print(F("Light: "));
    Serial.print(lux);
    Serial.println(F(" lx"));
    guiController->setLux(lux);
    lastButtonAction = millis();
  }
  */
  if (millis() - lastButtonAction > DEBOUNCE_DELAY)
  {
    lastButtonAction = millis();
   // okCommand = guiController->onOkClick();
   okCommand = true;
  }
}

void IRAM_ATTR onUpClick()
{
  if (millis() - lastButtonAction > DEBOUNCE_DELAY)
  {
    lastButtonAction = millis();
    upCommand = true;
  }
}
void IRAM_ATTR onDownClick()
{
  if (millis() - lastButtonAction > DEBOUNCE_DELAY)
  {
    lastButtonAction = millis();
    downCommand = true;
  }
}
void IRAM_ATTR onRightClick()
{
  if (millis() - lastButtonAction > DEBOUNCE_DELAY)
  {
    lastButtonAction = millis();
    rightCommand = true;
  }
}

void IRAM_ATTR onLeftClick()
{
  if (millis() - lastButtonAction > DEBOUNCE_DELAY)
  {
    lastButtonAction = millis();
    leftCommand = true;
  }
}