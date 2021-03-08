#include "main_page.h"

MainPage::MainPage(TFT_eSPI *display, FlashMeterModel* model)
{

    Serial.println("Constructor of a main page");
    this->model  = model;
    this->display = display;
    this->code = "MAIN";
    this->area = new Area(00, 40, 120, 95); //40: padding top for all kind of information, 95 is the complement to 135
    this->area->setDisplay(display);
    this->area->setBackground(TFT_NAVY);
    this->area->attachSubject(this->model);
    
}

void MainPage::onUp()
{
    Serial.println("On Up of main page");
}

void MainPage::onDown()
{
    Serial.println("On down of main page");
}

void MainPage::onRight()
{
    Serial.println("On Right of main  page");
}

void MainPage::onLeft()
{
    Serial.println("On Left of  main page");
}

bool MainPage::onOk()
{
    Serial.println("On ok of page");
    return false;
}

void MainPage::show()
{
    Serial.println("Show on main page");
    display->setTextColor(this->area->getForeground(), this->area->getBackground());
    display->setRotation(1);
    this->area->show();
   
}

void MainPage::declineYourId()
{
    Serial.println("I am a Main page");
}