#include "info_area.h"
#include "../../flashmeter_model.h"

void InfoArea::show()
{
    display->fillRect(this->x, this->y, this->width, this->height, this->background);
    display->setTextColor(this->foreground, this->background);

    int yBaseline = 5;
    int fontSize = 1;

    this->displaySensitivity(yBaseline, fontSize);
    this->displayLuxValue(yBaseline, fontSize);
    this->displayEVValue(yBaseline + 10, fontSize);
}

void InfoArea::onReceiveDataFromSubject(const FlashMeterModel *model)
{
    this->setLuxValue(model->getCurrentLuxValue());
    this->setSensitivity(model->getSensitivity());
    this->evValue = model->getCurrentEV();
    this->show();
}

void InfoArea::displaySensitivity(const int yBaseLine, const int fontSize)
{
    display->setCursor(5, yBaseLine, fontSize);
    if (this->getSensitivity() > 0)
    {
        display->print(((String)this->getSensitivity()) + " ISO");
    }
    else
    {
        display->print("---");
    }
}

void InfoArea::displayLuxValue(const int yBaseLine, const int fontSize)
{

    int _luxValue = this->getLuxValue();

    int xPosition = 200;
    if (_luxValue >= 100)
    {
        xPosition = xPosition - 5;
    }
    if (_luxValue >= 1000)
    {
        xPosition = xPosition - 5;
    }
    if (_luxValue >= 10000)
    {
        xPosition = xPosition - 5;
    }
    display->setCursor(xPosition, yBaseLine, fontSize);

    if (_luxValue > 0)
    {
        String luxAsString = (String)_luxValue;

        display->print(luxAsString + " lux");
    }
    else
    {
        display->print("---");
    }
}

void InfoArea::displayEVValue(const int yBaseLine, const int fontSize)
{

    int xPosition = 195;

    display->setCursor(xPosition, yBaseLine, fontSize);

    if (this->evValue > 0)
    {
        String t = "EV: ";
        t.concat(this->evValue);
        display->print(t);
    }
    else
    {
        display->print("---");
    }
}
