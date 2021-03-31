#include "TFT_display_device.h"

TFTDisplayDevice::TFTDisplayDevice()
{
    this->display.init();
}
void TFTDisplayDevice::fillRect(int x, int y, int width, int height, unsigned int background)
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
void TFTDisplayDevice::fillScreen(const unsigned int color)
{
    this->display.fillScreen(color);
}
void TFTDisplayDevice::setTextColor(unsigned int foreground_color, unsigned int background_color)
{
    this->display.setTextColor(foreground_color, background_color);
}
void TFTDisplayDevice::setRotation(int r)
{
    this->display.setRotation(r);
}
void TFTDisplayDevice::setCursor(int x, int y, unsigned char font_size)
{
    this->display.setCursor(x, y, font_size);
}

void TFTDisplayDevice::setTextSize( unsigned char textSize){
    this->display.setTextSize( textSize);
}

void TFTDisplayDevice::fillTriangle(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int color){
    this->display.fillTriangle(x0,y0,x1, y1, x2,y2, color);
}