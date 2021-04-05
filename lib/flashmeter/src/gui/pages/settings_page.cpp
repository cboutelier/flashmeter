#include "settings_page.h"
#include "../areas/title_area.h"

SettingPage::SettingPage(DisplayDevice *d, Model *model, ConsoleDelegator *console, char const *code) : Page(d, model, console, code)
{
    this->buildAreas();
}

SettingPage::~SettingPage()
{
     
}


void SettingPage::buildAreas()
{
    this->titleArea = new TitleArea(this->display, this->console, 0, 0, 240, 40); //40: padding top for all kind of information, 95 is the complement to 135
    this->titleArea->setBackground(TFT_GOLD);
    this->titleArea->setForeground(0xFFFF);
}

void SettingPage::show()
{
    display->fillScreen(TFT_BLACK);
    display->setRotation(1);
    this->titleArea->show();
}

void SettingPage::onButtonEvent(const unsigned int button)
{
  
}