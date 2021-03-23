#include "TFT_display_device.h"

TFTDisplayDevice::TFTDisplayDevice()
{
    this->display.init();
}
void TFTDisplayDevice::fillRect(int x, int y, int width, int height, int background)
{
    this->display.fillRect(x, y, width, height, background);
}
void TFTDisplayDevice::print(char const *text)
{
    this->display.print(text);
   
}

void TFTDisplayDevice::turnOn()
{
      digitalWrite(4, HIGH);
}
void TFTDisplayDevice::turnOff()
{
      digitalWrite(4, LOW);
}
void TFTDisplayDevice::fillScreen(const int color)
{
    this->display.fillScreen(color);
}
void TFTDisplayDevice::setTextColor(int foreground_color, int background_color)
{
    this->display.setTextColor(foreground_color, background_color);
}
void TFTDisplayDevice::setRotation(int r)
{
    this->display.setRotation(r);
}
void TFTDisplayDevice::setCursor(int x, int y, int font_size)
{
    this->display.setCursor(x, y, font_size);
}