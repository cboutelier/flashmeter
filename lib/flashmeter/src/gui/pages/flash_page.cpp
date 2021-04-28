#include "flash_page.h"

#include "../areas/info_area.h"
#include "../areas/progress_area.h"
#include "../areas/flash_area.h"

FlashPage::FlashPage(DisplayDevice *d, Model *model, ConsoleDelegator *console, char const *code) : Page(d, model, console, code)
{
    this->buildAreas();
}

FlashPage::~FlashPage()
{
    this->model->unRegisterObserver(this->infoArea);
}

void FlashPage::onButtonEvent(const unsigned int button)
{

 

    //if event UP  this->model->increaseApertureIndex();
    //if event DOWN  this->model->decreaseApertureIndex();
}

void FlashPage::show()
{
    display->fillScreen(0xffffff);
    display->setRotation(1);
    
    this->infoArea->show();
    this->progressArea->show();
    this->flashArea->show();

   // this->model->fireEvents();
}

void FlashPage::buildAreas()
{
    this->infoArea = new InfoArea(this->display, this->console, 0, 0, 240, 40);
    this->infoArea->setBackground(TFT_BLACK);
    this->infoArea->setForeground(TFT_WHITE);
    this->infoArea->attachSubject(this->model);

    this->progressArea = new ProgressArea(this->display, this->console,0, 115, 240, 20);
    this->progressArea->setBackground(TFT_BLACK);
    this->progressArea->setForeground(TFT_WHITE);

    this->flashArea = new FlashArea(this->display, this->console, 0, 40, 240, 75 );
    this->flashArea->setBackground(TFT_BLACK);
    this->flashArea->setForeground(TFT_WHITE);

}
