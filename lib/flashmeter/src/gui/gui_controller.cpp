#include "gui_controller.h"
#include "pages/main_page.h"

GuiController::GuiController(DisplayDevice *d, Model *model, ConsoleDelegator* console)
{
    //this->pages = new Page[5];
    this->model = model;
    this->console = console;

    //this->page = NULL;
    isOn = true;
    display = d;
    this->page = new MainPage(this->display, this->model, this->console, "MAIN");

    /*
    display->fillScreen(TFT_BLACK);
    display->setTextColor(TFT_GREEN, TFT_BLACK);
    */
    //this->showSplash();
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

    if (this->page != NULL)
    {
        delete this->page;
    }
    this->page = new SettingPage(this->display, this->model);
    this->page->show();
    */
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
}
void GuiController::onRightClick()
{
    /*  if (this->page != NULL)
    {
        Serial.println("Right click on gui controller");
        this->page->onRight();
    }
    */
}

bool GuiController::onOkClick()
{
    /*   if (this->page != NULL)
    {
        Serial.println("OK click on gui controller");
        return this->page->onOk();
    }
    */
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
