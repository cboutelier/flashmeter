#ifndef TFT_DISPLAY_DEVICE_H
#define TFT_DISPLAY_DEVICE_H

#include <TFT_eSPI.h>
#include <display/display_device.h>

class TFTDisplayDevice: public DisplayDevice{
public:
    TFTDisplayDevice();
    void fillRect( int x, int y,  int width,  int height, int background);
    void print( char const *text) ;
    void turnOn() ;
    void turnOff() ;
    void fillScreen( const int color);
    void setTextColor( int foreground_color, int background_color);
    void setRotation(int r);
    void setCursor( int x, int y, int font_size);
    void fillTriangle(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int color);

private:
    TFT_eSPI display;
};

#endif //TFT_DISPLAY_DEVICE_H