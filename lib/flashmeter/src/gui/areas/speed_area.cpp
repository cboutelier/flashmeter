#include "speed_area.h"
#include <string.h>
#include <stdio.h>

SpeedArea::SpeedArea(DisplayDevice *d, ConsoleDelegator *console, int x, int y, int width, int height) : Area(d, x, y, width, height)
{
    this->console = console;
    this->buildSpeeds();
}

void SpeedArea::show()
{
    this->console->println("Show of speed area");
    display->fillRect(this->x, this->y, this->width, this->height, this->background);
    display->setTextColor(this->foreground, this->background);
    display->setCursor(130, 78, 4);
    display->setTextSize(1);
    display->print(this->speeds[this->index]);
    //display->print("ok");
}

void SpeedArea::fillArea()
{
    display->fillRect(this->x, this->y, this->width, this->height, this->background);
    display->setTextColor(this->foreground, this->background);
}

void SpeedArea::onReceiveDataFromSubject(const Observable *m)
{
    Model *model = (Model *)m;
    if (this->index != model->getSpeedIndex())
    {
        this->index = model->getSpeedIndex();
        this->show();
    }
}

void SpeedArea::buildSpeeds()
{
  this->speeds[0] = "32 min";
  this->speeds[1] = "16 min";
  this->speeds[2] = "8 min";
  this->speeds[3] = "4 min";
  this->speeds[4] = "2 min";
  this->speeds[5] = "1 min";
  this->speeds[6] = "30s";
  this->speeds[7] = "15s";
  this->speeds[8] = "8s";
  this->speeds[9] = "4s";
  this->speeds[10] = "2s";
  this->speeds[11] = "1s";
  this->speeds[12] = "1 / 2 s";
  this->speeds[13] = "1 / 4 s";
  this->speeds[14] = "1 / 8 s";
  this->speeds[15] = "1 / 15 s";
  this->speeds[16] = "1 / 30 s";
  this->speeds[17] = "1 / 60 s";
  this->speeds[18] = "1 / 125 s";
  this->speeds[19] = "1 / 250 s";
  this->speeds[20] = "1 / 500 s";
  this->speeds[21] = "1 / 1 000 s";
  this->speeds[22] = "1 / 2 000 s";
  this->speeds[23] = "1 / 4 000 s";
  this->speeds[24] = "1 / 8 000 s";
  this->speeds[25] = "1 / 16 000 s";
  this->speeds[26] = "1 / 32 000 s";
}

const char *SpeedArea::convertToStringValue()
{
    if (this->index >= 0 && this->index < SPEED_ARRAY_SIZE)
    {
        return this->speeds[this->index];
    }
    else
    {
        return "...";
    }
}
