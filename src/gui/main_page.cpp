#include "main_page.h"

MainPage::MainPage(TFT_eSPI* display){
   
    Serial.println("Constructor of a main page");
    this->display = display;
    this->code = "MAIN";
}

void MainPage::onUp(){
    Serial.println("On Up of main page");
}

void MainPage::onDown(){
    Serial.println("On down of main page");
}

 

void MainPage::onRight(){
    Serial.println("On Right of main  page");
}

void MainPage::onLeft(){
    Serial.println("On Left of  main page");
}

bool MainPage::onOk(){
    Serial.println("On ok of page");
    return false;
}

void MainPage::show(){
    Serial.println("Show on main page");
  display->fillScreen(TFT_DARKGREY);
        display->setTextColor(TFT_WHITE, TFT_DARKGREY);
        display->setRotation(1);
        display->setCursor(40, 60, 4);
        display->print(F("MAIN"));
        delay(5000);
}

void MainPage::declineYourId(){
    Serial.println("I am a Main page");
}