#include "page.h"

Page::Page(){
   Serial.println("Constructor of page");
}
/*
void Page::onUp(){
    Serial.println("On Up of  page");
}

void Page::onDown(){
    Serial.println("On down of  page");
}

void Page::onRight(){
    Serial.println("On Right of  page");
}

void Page::onLeft(){
    Serial.println("On Left of  page");
}
*/

void Page::show(){
    Serial.println("Show of page");
}

/*
bool Page::onOk(){
    Serial.println("On ok of page");
    return false;
}
*/

void Page::declineYourId(){
    Serial.println("I am a Page");
}

void Page::setDisplay(TFT_eSPI* display){
    this->display = display;
}