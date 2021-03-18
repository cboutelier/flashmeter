#include "info_area.h"
#include "../../flashmeter_model.h"

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

void InfoArea::onReceiveDataFromSubject(const FlashMeterModel *model)
{
    if (this->getLuxValue() != model->getCurrentLuxValue())
    {
        this->luxValueChanged = true;
        this->setLuxValue(model->getCurrentLuxValue());
    }
    if (this->getSensitivity() != model->getSensitivity())
    {
        this->sensitivityChanged = true;
        this->setSensitivity(model->getSensitivity());
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
        display->print(((String)this->getSensitivity()) + " ISO");
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
        String luxAsString = (String)_luxValue;

        display->print(luxAsString + " lux");
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
        String t = "EV: ";
        t.concat(this->evValue);
        display->print(t);
    }
    else
    {
        display->print("---");
    }
    evValueChanged = false;
}
