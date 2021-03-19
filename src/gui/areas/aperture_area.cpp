#include "aperture_area.h"
#include "../../flashmeter_model.h"

void ApertureArea::show()
{
    display->fillRect(this->x, this->y, this->width, this->height, this->background);
    display->setTextColor(this->foreground, this->background);
    display->setCursor(10, 78, 4);
    display->print("f " + this->getApertureFromIndex());
}

void ApertureArea::fillArea(){
    display->fillRect(this->x, this->y, this->width, this->height, this->background);
    display->setTextColor(this->foreground, this->background);
}


void ApertureArea::onReceiveDataFromSubject(const FlashMeterModel *model)
{
    int currentIndex = model->getPreferredApertureIndex();
    if (currentIndex != this->currentIndex)
    {
        this->currentIndex = model->getPreferredApertureIndex();
        this->show();
    }
}


String ApertureArea::getApertureFromIndex(){
    if( this->currentIndex==0){
        return "1.4";
    }else if( this->currentIndex==1){
        return "2";
    }else if( this->currentIndex==2){
        return "2.8";
    }else if( this->currentIndex==3){
        return "4";

    }else if( this->currentIndex==4){
        return "5.6";
    }
    return "xx";
}