#ifndef DISPLAY_DEVICE
#define DISPLAY_DEVICE

class DisplayDevice
{

public:
    virtual void fillRect(int x, int y, int width, int height, int background);
    virtual void print(char const *text) = 0;
    virtual void turnOn() = 0;
    virtual void turnOff() = 0;
    virtual void fillScreen(const int color);
    virtual void setTextColor(int foreground_color, int background_color);
    virtual void setRotation(int r);
    virtual void setCursor(int x, int y, unsigned char font_size);
    virtual void setTextSize( unsigned char text_size);
    virtual void fillTriangle(unsigned int x0, unsigned int y0, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, unsigned int color);
};

#endif //DISPLAY_DEVICE