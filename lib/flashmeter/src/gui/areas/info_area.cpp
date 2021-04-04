#include "info_area.h"
#include "../../model/model.h"

#include <stdio.h>
#include <string.h>

InfoArea::InfoArea(DisplayDevice *d, ConsoleDelegator *console, int x, int y, int width, int height) : Area(d, x, y, width, height)
{
    this->console = console;
}

void InfoArea::fillArea()
{
    display->fillRect(this->x, this->y, this->width, this->height, this->background);
    this->initDone = true;
}

void InfoArea::show()
{
    if (!this->initDone)
    {
        this->fillArea();
    }
    display->setTextColor(this->foreground, this->background);

    int yBaseline = 5;
    int fontSize = 1;

    this->displaySensitivity(yBaseline, fontSize);
    this->displayLuxValue(yBaseline, fontSize);
    this->displayEVValue(yBaseline + 10, fontSize);
}

void InfoArea::onReceiveDataFromSubject(const Observable *observable)
{
    Model *model = (Model *)observable;
    if (this->getLuxValue() != model->getCurrentLuxValue())
    {
        this->luxValueChanged = true;
        this->setLuxValue(model->getCurrentLuxValue());
    }

    if (this->getSensitivity() != model->getSensitivityIndex())
    {
        this->sensitivityChanged = true;
        this->setSensitivity(model->getSensitivityIndex());
        strcpy(this->sensitivityValue, model->getSensitivityValue());
    }

    if (this->evValue != model->getCurrentEV())
    {
        this->evValue = model->getCurrentEV();
        this->evValueChanged = true;
    }

    this->show();
}

void InfoArea::displaySensitivity(const int yBaseLine, const int fontSize)
{
    if (!this->sensitivityChanged)
    {
        return;
    }
    display->setCursor(5, yBaseLine, fontSize);
    if (this->getSensitivity() > 0)
    {
        char msg[30];
        strcpy(msg, this->sensitivityValue);
        strcat(msg, " ISO");

        display->print(msg);
        this->sensitivityChanged = false;
    }
    else
    {
        display->print("---");
    }
}

void InfoArea::displayLuxValue(const int yBaseLine, const int fontSize)
{
    if (!this->luxValueChanged)
    {
        return;
    }
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
        char msg[15];
        sprintf(msg, "%i", _luxValue);
        strcat(msg, " lux");
        display->print(msg);
    }
    else
    {
        display->print("---");
    }
    luxValueChanged = false;
}

void InfoArea::displayEVValue(const int yBaseLine, const int fontSize)
{
    if (!this->evValueChanged)
    {
        return;
    }
    int xPosition = 195;

    display->setCursor(xPosition, yBaseLine, fontSize);

    if (this->evValue > 0)
    {
        char msg[20];
        sprintf(msg, "EV: %i", this->evValue);
        display->print(msg);
    }
    else
    {
        display->print("---");
    }
    evValueChanged = false;
}

const char *InfoArea::getSensitvityValue() const
{
    return this->sensitivityValue;
}

void InfoArea::setSensitivityValue(const char *value)
{
    strcpy(this->sensitivityValue, value);
}
