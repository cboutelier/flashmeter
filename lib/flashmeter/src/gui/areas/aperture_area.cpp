#include "aperture_area.h"
#include <string.h>
#include <stdio.h>

ApertureArea::ApertureArea(DisplayDevice *d, ConsoleDelegator *console, int x, int y, int width, int height) : Area(d, x, y, width, height)
{
    this->console = console;
    this->buildApertures();
}

void ApertureArea::show()
{
    display->fillRect(this->x, this->y, this->width, this->height, this->background);
    display->setTextColor(this->foreground, this->background);
    display->setCursor(30, 78, 4);

    char apertureMessage[60];
    strcpy(apertureMessage, "f");
    strcat(apertureMessage, this->getApertureFromIndex());

    display->print(apertureMessage);

    unsigned int color = this->background;
    if (this->hasFocus())
    {
        color = this->foreground;
    }
    //Add the cursors
    display->fillTriangle(5, 65, 10, 55, 15, 65, color);
    if (this->currentIndex > 0)
    {
        display->fillTriangle(5, 110, 10, 120, 15, 110, color);
    }
    else
    {
        display->fillRect(4, 118, 12, 12, this->background);
    }
}

void ApertureArea::fillArea()
{
    display->fillRect(this->x, this->y, this->width, this->height, this->background);
    display->setTextColor(this->foreground, this->background);
}

void ApertureArea::onReceiveDataFromSubject(const Observable *m)
{
    Model *model = (Model *)m;
    int currentIndex = model->getPreferredApertureIndex();
    if (currentIndex != this->currentIndex)
    {
        this->currentIndex = model->getPreferredApertureIndex();
        this->show();
    }
}

void ApertureArea::buildApertures()
{
    this->apertures[0] = "1.4";
    this->apertures[1] = "2";
    this->apertures[2] = "2.8";
    this->apertures[3] = "4";
    this->apertures[4] = "5.6";
    this->apertures[5] = "8";
    this->apertures[6] = "11";
    this->apertures[7] = "16";
    this->apertures[8] = "22";
    this->apertures[9] = "32";
}

char const *ApertureArea::getApertureFromIndex()
{
    if (this->currentIndex >= 0 && this->currentIndex < 10)
    {
        return this->apertures[this->currentIndex];
    }
    else
    {
        return "...";
    }
}