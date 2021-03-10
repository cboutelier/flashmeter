#include "page.h"

Page::Page(){
   Serial.println("Constructor of page");
}

Page::~Page(){
}


void Page::show(){
    Serial.println("Show of page");
}

void Page::declineYourId(){
    Serial.println("I am a Page");
}

void Page::setDisplay(TFT_eSPI* display){
    this->display = display;
}

 