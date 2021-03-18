#include "speed_area.h"
#include "../../flashmeter_model.h"

void SpeedArea::show()
{
    display->fillRect(this->x, this->y, this->width, this->height, this->background);
    display->setTextColor(this->foreground, this->background);
    display->setCursor(130, 78, 4);
    String t = convertValue();
    display->print(t);
}

void SpeedArea::fillArea(){
    display->fillRect(this->x, this->y, this->width, this->height, this->background);
    display->setTextColor(this->foreground, this->background);
}


void SpeedArea::onReceiveDataFromSubject(const FlashMeterModel *model)
{
    double previous = this->speed;
    this->speed = model->getSpeed();

    if (this->speed != previous)
    {
        this->show();
    }
}


//TODO convert the highest values (up to 32min)
String SpeedArea::convertValue()
{
    if (this->speed == 30.0d)
    {
        return "30 s";
    }
    else if (this->speed == 15.0d)
    {
        return "15 s";
    }
else if (this->speed == 8.0d)
    {
        return "8 s";
    }
else if (this->speed == 4.0d)
    {
        return "4 s";
    }
    else if (this->speed == 2.0d)
    {
        return "2 s";
    }
    else if (this->speed == 1 / 8.0d)
    {
        return "1/8 s";
    }
    else if (this->speed == 1 / 15.0d)
    {
        return "1/15 s";
    }
    else if (this->speed == 1 / 30.0d)
    {
        return "1/30 s";
    }
    else if (this->speed == 1 / 60.0d)
    {
        return "1/60 s";
    }
    else if (this->speed == 1 / 125.0d)
    {
        return "1/125 s";
    }
     else if (this->speed == 1 /250.0d)
    {
        return "1/250 s";
    } else if (this->speed == 1 /500.0d)
    {
        return "1/500 s";
    }else if (this->speed == 1 /1000.0d)
    {
        return "1/1000 s";
    }
    else if (this->speed == 1 /2000.0d)
    {
        return "1/2000 s";
    }else if (this->speed == 1 /4000.0d)
    {
        return "1/4000 s";
    }else if (this->speed == 1 /8000.0d)
    {
        return "1/8000 s";
    }
    return "...";
}
