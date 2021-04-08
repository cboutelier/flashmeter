#include "gui_controller.h"
#include "pages/main_page.h"
#include "pages/settings_page.h"
#include <string.h>

GuiController::GuiController(DisplayDevice *d, Model *model, ConsoleDelegator *console)
{
    //this->pages = new Page[5];
    this->model = model;
    this->console = console;

    //this->page = NULL;
    isOn = true;
    display = d;

    /*
    display->fillScreen(TFT_BLACK);
    display->setTextColor(TFT_GREEN, TFT_BLACK);
    */
    //this->showSplash();

    this->page = new MainPage(this->display, this->model, this->console, "MAIN");
    this->page->show();
}

void GuiController::on()
{
    /* if (!isOn)
    {
        digitalWrite(4, HIGH);
        isOn = true;
    }
    if (this->page == NULL)
    {
        this->page = new MainPage(this->display, this->model);
        this->page->show();
        this->model->fireEvents();
    }
    */
}

void GuiController::off()
{
    /*  if (isOn)
    {
        Serial.println("Turning off the display");
        digitalWrite(4, LOW);
        isOn = false;

        if (this->page != NULL)
        {
            delete this->page;
            this->page = NULL;
        }
    }*/
}

/*
 * Fake splash method. For now, the method just writes with white letters on blue background
 */
void GuiController::showSplash()
{
    if (display)
    {
        display->fillScreen(0x001F);
        display->setTextColor(0xFFFF, 0x001F);
        display->setRotation(1);
        display->setCursor(40, 60, 4);
        display->print("FLASHMETER");
    }
    this->console->println("FLASHMETER");
}

void GuiController::show()
{
    this->on();
    // this->page->show();
}

void GuiController::onSettingClick()
{

    /*   if (!isOn)
    {
        digitalWrite(4, HIGH);
        isOn = true;
    }
    */

    if (this->page != nullptr)
    {
        delete this->page;
    }
    this->page = new SettingPage(this->display, this->model, this->console, "SETTINGS");
    ((SettingPage *)this->page)->setExitCallback(exitSettings, this);
    this->page->show();
}

void GuiController::exitSettings(void *refToThis)
{
    GuiController *self = static_cast<GuiController *>(refToThis);
    self->navigateToMain();
}


// && strcmp(this->page->getCode(), "MAIN") == 0

void GuiController::navigateToMain()
{
    if (this->page != nullptr)
    {
        delete this->page;
    }
    this->page = new MainPage(this->display, this->model, this->console, "MAIN");
    this->page->show();
    this->model->forceFireEvents();
}

void GuiController::onUpClick()
{
    if (this->page != nullptr)
    {
        this->page->onButtonEvent(1);
    }
}

void GuiController::onDownClick()
{
    if (this->page != nullptr)
    {
        this->page->onButtonEvent(2);
    }
}

void GuiController::onLeftClick()
{
    /*   if (this->page != NULL)
    {
        this->page->onLeft();
    }
    */
    if (this->page != nullptr)
    {
        this->page->onButtonEvent(3);
    }
}
void GuiController::onRightClick()
{
    if (this->page != nullptr)
    {
        this->page->onButtonEvent(4);
    }
}

bool GuiController::onOkClick()
{
    if (this->page != nullptr)
    {

        this->page->onButtonEvent(6);
    }

    return false;
}

bool GuiController::onBackClick()
{
    /*  Serial.println("on back of gui controller");
    if (this->page != NULL && this->page->getCode() == "SETTINGS")
    {
        delete this->page;
        this->page = new MainPage(this->display, this->model);
        this->page->show();
    }
    */
    return true;
}
