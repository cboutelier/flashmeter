#include "area.h"

Area::Area(DisplayDevice *d, int x, int y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->display = d;
}

int Area::getX() { 
    return this->x; 
}

int Area::getY() { return this->y; }

int Area::getWidth() { return this->width; }

int Area::getHeight() { return this->height; };

unsigned int Area::getBackground()
{
    return this->background;
}

unsigned int Area::getForeground() { 
    return this->foreground; 
}

void Area::setBackground(unsigned int back)
{
    this->background = back;
}

void Area::setForeground(unsigned int fore)
{
    this->foreground = fore;
}

void Area::setFocus(bool b){
    bool oldFocus = this->focus;
    this->focus = b;
    if( oldFocus!=this->focus){
        this->show();
    }
}

bool Area::hasFocus(){
    return this->focus;
}