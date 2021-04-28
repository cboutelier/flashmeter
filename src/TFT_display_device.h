#ifndef TFT_DISPLAY_DEVICE_H
#define TFT_DISPLAY_DEVICE_H

#include <TFT_eSPI.h>
#include <display/display_device.h>

class TFTDisplayDevice: public DisplayDevice{
public:
    TFTDisplayDevice();
    void fillRect( int x, int y,  int width,  int height, unsigned int background);
    void drawRect( int x, int y, int width, int height, unsigned int color);
    void print( char const *text) ;
    void turnOn() ;
    void turnOff() ;
    void fillScreen( const unsigned int color);
    void setTextColor( unsigned int foreground_color, unsigned int background_color);
    void setTextSize( unsigned char textSize);
    void setRotation(int r);
    void setCursor( int x, int y, unsigned char font_size);
    void fillTriangle(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int color);
    void drawXBitmap( unsigned int x, unsigned int y,  unsigned char* bmp, unsigned int width, unsigned int height, unsigned int color, unsigned int bgcolor);

private:
    TFT_eSPI display;
};

#endif //TFT_DISPLAY_DEVICE_H