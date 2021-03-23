#include <Arduino.h>
#include <EEPROM.h>

#include <Wire.h>
#include <BH1750.h>
#include <model/model.h>
#include <repository.h>
#include <gui/gui_controller.h>
#include "EspEEPROMRepository.h"
#include "TFT_display_device.h"
#include <light_sensor.h>

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

BH1750 device;
LightSensor*  lightSensor;
GuiController *guiController;
//FlashMeterModel *model;
Model* model;
Repository* repository;

//For some reasons, the TFT object must be instanced here
TFTDisplayDevice display;

double focale = 1.4;
long speed = 30;

bool paused = false;

bool toSave = false;
bool upCommand = false;
bool downCommand = false;
bool rightCommand = false;
bool leftCommand = false;
bool settingsCommand = false;
bool okCommand = false;
bool backCommand = false;

unsigned long lastButtonAction = 0;

int counterForMemory = 0;

void IRAM_ATTR onSettingClick();
void IRAM_ATTR onOkClick();
void IRAM_ATTR onUpClick();
void IRAM_ATTR onDownClick();
void IRAM_ATTR onRightClick();
void IRAM_ATTR onLeftClick();
void IRAM_ATTR onBackClick();

void IRAM_ATTR attachInterrupts();
void IRAM_ATTR detachInterrupts();
 
void manageCommands();
void setup()
{

  //Alway initiate a serial connection...
  Serial.begin(9600);

  repository = new EspEEPROMRepository(&attachInterrupts, &detachInterrupts);

  //declare pin for settings as Input
  pinMode(SET_PIN, INPUT_PULLUP);
  pinMode(OK_PIN, INPUT_PULLUP);
  pinMode(UP_PIN, INPUT_PULLUP);
  pinMode(DOWN_PIN, INPUT_PULLUP);
  pinMode(RIGHT_PIN, INPUT_PULLUP);
  pinMode(LEFT_PIN, INPUT_PULLUP);
  pinMode(BACK_PIN, INPUT_PULLUP);

  //Specific initialization of the Wire library: because the bh1750 lib does not do it, and because the board uses non standard pins.
 // Wire.begin(SDA_PIN, SCL_PIN);

  model = new Model( repository);
  

  /*model = new FlashMeterModel();
  model->setAttachCallback( &attachInterrupts);
  model->setDetachCallback( &detachInterrupts);
  model->setCurrentLuxValue(20);
  lightSensor = new LightSensor(&device, model);
  lightSensor->attachSubject(model);
  */

  guiController = new GuiController( &display,  model);

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
  attachInterrupt(BACK_PIN, onBackClick, RISING);
}

void IRAM_ATTR detachInterrupts()
{
  detachInterrupt(SET_PIN);
  detachInterrupt(UP_PIN);
  detachInterrupt(DOWN_PIN);
  detachInterrupt(RIGHT_PIN);
  detachInterrupt(LEFT_PIN);
  detachInterrupt(OK_PIN);
  detachInterrupt(BACK_PIN);
}

void loop()
{

  if (millis() - lastButtonAction > READING_TIMEOUT)
  {
   // guiController->off();
    paused = true;
  }

  //manageCommands();

/*
  if( !paused){
    lightSensor->read();
  }
  */

  delay(100);

  if( counterForMemory >= 100)
  {
     uint32_t  free = esp_get_free_heap_size();
     Serial.print("-----  Free memory: ");
     Serial.println(free);
     counterForMemory=0;
  }
  counterForMemory++;
   

}

void manageCommands()
{
  if (okCommand)
  {
    //guiController->onOkClick();
    okCommand = false;
    paused = false;
  }
  if (backCommand)
  {
    //guiController->onBackClick();
    backCommand = false;
  }
  if (upCommand)
  {
    //guiController->onUpClick();
    upCommand = false;
  }
  else if (downCommand)
  {
    //guiController->onDownClick();
    downCommand = false;
  }
  else if (rightCommand)
  {
    //guiController->onRightClick();
    rightCommand = false;
  }
  else if (leftCommand)
  {
    //guiController->onLeftClick();
    leftCommand = false;
  }
  else if (settingsCommand)
  {
    //guiController->onSettingClick();
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
  //guiController->on();
  if (millis() - lastButtonAction > DEBOUNCE_DELAY)
  {
    if( millis()-lastButtonAction > READING_TIMEOUT){
     //Was guiController->on
    }
    lastButtonAction = millis();
    okCommand = true;
  }
}


void IRAM_ATTR onBackClick(){
 if (millis() - lastButtonAction > DEBOUNCE_DELAY)
  { 
    lastButtonAction = millis();
    backCommand = true;
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