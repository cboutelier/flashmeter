#ifndef DISPLAY_DEVICE
#define DISPLAY_DEVICE

class DisplayDevice
{

public:
    virtual void fillRect( int x, int y,  int width,  int height, int background);
    virtual void print( char const *text) = 0;
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual void fillScreen( const int color);
    virtual void setTextColor( int foreground_color, int background_color);
    virtual void setRotation(int r);
    virtual void setCursor( int x, int y, int font_size);
};

#endif //DISPLAY_DEVICE