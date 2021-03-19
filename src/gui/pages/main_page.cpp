#include "main_page.h"

#include "../areas/aperture_area.h"
#include "../areas/speed_area.h"
#include "../areas/info_area.h"

MainPage::MainPage(TFT_eSPI *display, FlashMeterModel* model)
{

    Serial.println("Constructor of a main page");
    this->model  = model;
    this->display = display;
    this->code = "MAIN";
    this->apertureArea = new ApertureArea(00, 40, 120, 95); //40: padding top for all kind of information, 95 is the complement to 135
    this->apertureArea->setDisplay(display);
    this->apertureArea->setBackground(TFT_NAVY);
    this->apertureArea->setForeground(TFT_WHITE);
    this->apertureArea->attachSubject(this->model);

    this->speedArea = new SpeedArea(120, 40, 120, 95); //40: padding top for all kind of information, 95 is the complement to 135
    this->speedArea->setDisplay(display);
    this->speedArea->setBackground(TFT_DARKGREEN);
    this->speedArea->setForeground(TFT_WHITE);
    this->speedArea->attachSubject(this->model);

    this->infoArea = new InfoArea(0,0,240, 40);
    this->infoArea->setDisplay( display);
    this->infoArea->setBackground(TFT_COLMOD);
    this->infoArea->setForeground(TFT_WHITE); 
    this->infoArea->attachSubject(this->model);
    Serial.println("End of main page construction");
}

MainPage::~MainPage(){
    this->model->unRegisterObserver(this->speedArea);
    this->model->unRegisterObserver(this->apertureArea);
    this->model->unRegisterObserver(this->infoArea);
}

void MainPage::onUp()
{
    this->model->increaseApertureIndex();
}

void MainPage::onDown()
{
    this->model->decreaseApertureIndex();
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

bool MainPage::onBack(){
    Serial.println("on back of main page");
    return false;
}

void MainPage::show()
{
    display->fillScreen(TFT_BLACK);
    display->setRotation(1);
    this->apertureArea->show();
    this->speedArea->show(); 
    this->infoArea->show();
    
    this->model->fireEvents();
}

void MainPage::declineYourId()
{
    Serial.println("I am a Main page");
}