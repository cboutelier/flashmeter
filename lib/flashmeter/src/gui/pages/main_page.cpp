#include "main_page.h"

/*
#include "../areas/aperture_area.h"
#include "../areas/speed_area.h"
#include "../areas/info_area.h"*/

MainPage::MainPage(DisplayDevice *d, Model *model, ConsoleDelegator *console, char const *code) : Page(d, model, console, code)
{
    this->buildAreas();
}

MainPage::~MainPage()
{
    /*this->model->unRegisterObserver(this->speedArea);
    this->model->unRegisterObserver(this->apertureArea);
    this->model->unRegisterObserver(this->infoArea);
    */
}

void MainPage::onButtonEvent()
{

    //if event UP  this->model->increaseApertureIndex();
    //if event DOWN  this->model->decreaseApertureIndex();
}

void MainPage::show()
{
    display->fillScreen(0xffffff);
    display->setRotation(1);
    /*  this->apertureArea->show();
    this->speedArea->show(); 
    this->infoArea->show();*/

    //this->model->fireEvents();
}

void MainPage::buildAreas()
{
    this->console->println("Build areas on main page");
    /*
    this->apertureArea = new ApertureArea(00, 40, 120, 95); //40: padding top for all kind of information, 95 is the complement to 135
this->apertureArea->setDisplay(display);
this->apertureArea->setBackground(TFT_NAVY);
this->apertureArea->setForeground(TFT_WHITE);
this->apertureArea->attachSubject(this->model);
this->speedArea = new SpeedArea(120, 40, 120, 95); //40: padding top for all kind of information, 95 is the complement to 135
this->speedArea->setDisplay(display);
this->speedArea->setBackground(TFT_DARKGREEN);
this->speedArea->setForeground(TFT_WHITE);
this->speedArea->attachSubject(this->model);
this->infoArea = new InfoArea(0,0,240, 40);
this->infoArea->setDisplay( display);
this->infoArea->setBackground(TFT_COLMOD);
this->infoArea->setForeground(TFT_WHITE); 
this->infoArea->attachSubject(this->model);
*/
}
