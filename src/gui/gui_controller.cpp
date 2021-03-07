#include "gui_controller.h"
#include <Arduino.h>
#include "setting_page.h"
#include "main_page.h"

GuiController::GuiController(TFT_eSPI *d, FlashMeterModel* model)
{
    //this->pages = new Page[5];
    this->model = model;

    this->settingPage = new SettingPage(d, this->model );
    this->mainPage = new MainPage(d);
    this->page = this->mainPage;
    isOn = true;
    display = d;
    display->init();
    display->fillScreen(TFT_BLACK);
    display->setTextColor(TFT_GREEN, TFT_BLACK);
    this->showSplash();
}

void GuiController::setLux(float luxValue)
{

    if (display)
    {
        digitalWrite(4, HIGH);
        isOn = true;
        display->fillScreen(TFT_BLACK);
        display->setTextColor(TFT_GREEN, TFT_BLACK);
        display->setRotation(1);
        display->setCursor(100, 60, 4);
        display->print(luxValue, 0);
        display->setCursor(155, 70, 1);
        display->print(F(" Lux"));
    }
}

void GuiController::on()
{
    if (!isOn)
    {
        digitalWrite(4, HIGH);
        isOn = true;
    }
}

void GuiController::off()
{
    if (isOn)
    {
        Serial.println("Turning off the display");
        digitalWrite(4, LOW);
        isOn = false;
    }
}

/*
 * Fake splash method. For now, the method just writes with white letters on blue background
 */
void GuiController::showSplash()
{
    if (display)
    {
        display->fillScreen(TFT_BLUE);
        display->setTextColor(TFT_WHITE, TFT_BLUE);
        display->setRotation(1);
        display->setCursor(40, 60, 4);
        display->print(F("FLASHMETER"));
        delay(1000);
    }
}

void GuiController::addPage(Page *page)
{
    Serial.println("..................................");
    Serial.println("Adding a page to the collection...");
    //page->setDisplay(display);
    //this->pages[this->usedPages] = page;

    this->page = page;
    this->page->declineYourId();
    Serial.print((long)&this->page, DEC);
    Serial.println("..................................");
}

void GuiController::show()
{
    this->on();
    this->page->show();
}

void GuiController::onSettingClick()
{

    if (this->page->getCode() == "MAIN")
    {
        this->on();
        this->page = this->settingPage;
        this->page->declineYourId();
        this->page->show();
    }
    //
    // this->page->show();
}

void GuiController::onUpClick(){
    if( this->page != NULL){
        this->page->onUp();
    }
}

void GuiController::onDownClick(){
    if( this->page != NULL){
        this->page->onDown();
    }
}

void GuiController::onLeftClick(){
      if( this->page != NULL){
        this->page->onLeft();
    }
}
void GuiController::onRightClick(){
      if( this->page != NULL){
          Serial.println("Right click on gui controller");
        this->page->onRight();
    }
}

bool GuiController::onOkClick(){
      if( this->page != NULL){
          Serial.println("OK click on gui controller");
        return this->page->onOk();
    }
    return false;
}