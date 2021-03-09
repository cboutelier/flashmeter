#include "speed_area.h"
#include "../flashmeter_model.h"
 
 

void SpeedArea::show(){
    display->fillRect(this->x, this->y, this->width, this->height,  this->background);
    display->setTextColor(this->foreground, this->background);
    display->setCursor(130, 78, 4);
    display->print("EV "  + value );
}

void SpeedArea::onReceiveDataFromSubject(const FlashMeterModel *model){
    this->value = String( model->getCurrentLuxValue());
    this->show();
}
 