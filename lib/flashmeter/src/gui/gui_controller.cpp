#include "gui_controller.h"

GuiController::GuiController(DisplayDevice *d, Model *model)
{
    //this->pages = new Page[5];
    this->model = model;

    //this->page = NULL;
    isOn = true;
    display = d;

    /*
    display->fillScreen(TFT_BLACK);
    display->setTextColor(TFT_GREEN, TFT_BLACK);
    */
    this->showSplash();
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
    /*   if (this->page != NULL)
    {
        this->page->onUp();
    }
    */
}

void GuiController::onDownClick()
{
    /*  if (this->page != NULL)
    {
        this->page->onDown();
    }
    */
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
