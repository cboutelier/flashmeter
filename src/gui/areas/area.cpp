#include "area.h"
#include "../../flashmeter_model.h"


Area::Area(int x, int y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->value = "";
}

int Area::getX() { return this->x; }
int Area::getY() { return this->y; }
int Area::getWidth() { return this->width; }
int Area::getHeight() { return this->height; };

uint32_t Area::getBackground()
{
    return this->background;
}
uint32_t Area::getForeground() { return this->foreground; }
void Area::setBackground(uint32_t back)
{
    this->background = back;
}
void Area::setForeground(uint32_t fore)
{
    this->foreground = fore;
}

void Area::setDisplay(TFT_eSPI* d){
    this->display = d;
}

