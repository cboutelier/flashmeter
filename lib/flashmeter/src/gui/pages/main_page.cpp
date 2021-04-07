#include "main_page.h"

#include "../areas/aperture_area.h"

#include "../areas/speed_area.h"

#include "../areas/info_area.h"

MainPage::MainPage(DisplayDevice *d, Model *model, ConsoleDelegator *console, char const *code) : Page(d, model, console, code)
{
    this->buildAreas();
}

MainPage::~MainPage()
{
    this->model->unRegisterObserver(this->speedArea);
    this->model->unRegisterObserver(this->apertureArea);
    this->model->unRegisterObserver(this->infoArea);
}

void MainPage::onButtonEvent(const unsigned int button)
{

    if (button == 1)
    {
        this->model->increaseApertureIndex();
    }
    else if (button == 2)
    {
        this->model->decreaseApertureIndex();
    }
    else if (button == 3)
    {
        this->speedArea->setFocus(false);
        this->apertureArea->setFocus(true);
    }
    else if (button == 4)
    {
        this->speedArea->setFocus(true);
        this->apertureArea->setFocus(false);
    }

    //if event UP  this->model->increaseApertureIndex();
    //if event DOWN  this->model->decreaseApertureIndex();
}

void MainPage::show()
{
    display->fillScreen(0xffffff);
    display->setRotation(1);
    this->apertureArea->show();
    this->speedArea->show();

    this->infoArea->show();

   // this->model->fireEvents();
}

void MainPage::buildAreas()
{
    this->apertureArea = new ApertureArea(this->display, this->console, 0, 40, 120, 95); //40: padding top for all kind of information, 95 is the complement to 135

    this->apertureArea->setBackground(TFT_BLUE);
    this->apertureArea->setForeground(0xFFFF);
    this->apertureArea->attachSubject(this->model);
    this->apertureArea->setFocus(true);

    this->speedArea = new SpeedArea(this->display, this->console, 120, 40, 120, 95); //40: padding top for all kind of information, 95 is the complement to 135
    this->speedArea->setBackground(TFT_BLUE);
    this->speedArea->setForeground(0xFFFF);
    this->speedArea->attachSubject(this->model);

    this->infoArea = new InfoArea(this->display, this->console, 0, 0, 240, 40);
    this->infoArea->setBackground(TFT_BLACK);
    this->infoArea->setForeground(TFT_WHITE);
    this->infoArea->attachSubject(this->model);
}
