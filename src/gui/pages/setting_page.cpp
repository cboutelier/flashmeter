#include "setting_page.h"

SettingPage::SettingPage(TFT_eSPI *display, FlashMeterModel *model)
{
    this->model = model;
    this->code = "SETTINGS";
    this->display = display;

    renderers = new EntryRenderer[this->model->getEntriesCount()];
    for (int i = 0; i < this->model->getEntriesCount(); i++)
    {
        renderers[i].init(display, this->model->getEntry(i), 30 + i * 15);
        renderers[i].setInitialColors(TFT_DARKGREEN, TFT_WHITE, TFT_SKYBLUE);
    }

}

void SettingPage::onUp()
{
    if (selectedEntry > 0  && this->isUpDownAllowed())
    {
        selectedEntry--;
        this->adjustSelectedEntry();
        this->show();
    }
}

void SettingPage::onDown()
{
    if( selectedEntry < this->model->getEntriesCount() && this->isUpDownAllowed()){
        selectedEntry++;
        this->adjustSelectedEntry();
        this->show();
    }
}


/**
 * Accepts scrolling only if the carret is on the name.
 **/
bool SettingPage::isUpDownAllowed(){
   
    if( selectedEntry == 0){
        return true;
    }

    if( selectedEntry > 0 ){
        EntryRenderer entry = renderers[selectedEntry-1];
        if( entry.getValueSelectedIndex()==-1){
            return true;
        }
    }
    return false;
}

void SettingPage::onLeft()
{
    if (renderers != NULL)
    {
        for (int i = 0; i < this->model->getEntriesCount(); i++)
        {
            if (renderers[i].isEntrySelected())
            {
                renderers[i].onLeft();
                break;
            }
        }
    }
}

void SettingPage::onRight()
{
    if (renderers != NULL)
    {
        for (int i = 0; i < this->model->getEntriesCount(); i++)
        {
            if (renderers[i].isEntrySelected())
            {
                renderers[i].onRight();
                break;
            }
        }
    }
}

bool SettingPage::onOk()
{
    if (renderers != NULL)
    {
        for (int i = 0; i < this->model->getEntriesCount(); i++)
        {
            if (renderers[i].isEntrySelected())
            {
                bool save = renderers[i].onOk();
                if( save ){
                    this->model->save();
                }
                
                Serial.print("Saving? ");
                Serial.println(save);
                return save;
            }
        }
    }
    return false;
}

bool SettingPage::onBack(){
    return false;
}

void SettingPage::adjustSelectedEntry()
{
    if (renderers != NULL)
    {
        for (int i = 0; i < this->model->getEntriesCount(); i++)
        {
            if (i == selectedEntry - 1)
            {
                renderers[i].setEntrySelected(true);
            }
            else
            {
                renderers[i].setEntrySelected(false);
            }
            renderers[i].show();
        }
    }
}

void SettingPage::show()
{
    display->fillScreen(TFT_DARKGREEN);
    if (selectedEntry > 0)
    {
        display->setTextColor(TFT_WHITE, TFT_DARKGREEN);
    }
    else
    {
        display->setTextColor(TFT_DARKGREEN, TFT_WHITE);
    }
    display->setRotation(1);
    display->setCursor(10, 5, 2);
    display->print(F("SETTINGS"));
    display->drawLine(0, 20, 240, 20, TFT_WHITE);

    if (renderers != NULL)
    {
        for (int i = 0; i < this->model->getEntriesCount(); i++)
        {
            renderers[i].show();
        }
    }
    delay(1000);
}

void SettingPage::declineYourId()
{
    Serial.println("I am a SettingPage");
}


 