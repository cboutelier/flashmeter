#include "focal_area.h"
#include "../../flashmeter_model.h"

void FocalArea::show()
{
    display->fillRect(this->x, this->y, this->width, this->height, this->background);
    display->setTextColor(this->foreground, this->background);
    display->setCursor(10, 78, 4);
    display->print("f " + value);
}

void FocalArea::onReceiveDataFromSubject(const FlashMeterModel *model)
{
    String newValue = model->getCurrentFocale();
    if (newValue != this->value)
    {
        this->value = model->getCurrentFocale();
        this->show();
    }
}
