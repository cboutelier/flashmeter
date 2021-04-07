#include "settings_page.h"
#include "../areas/title_area.h"
#include "../areas/settings_list_area.h"

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
    this->titleArea->setForeground(TFT_BLACK);

    this->settingsListArea = new SettingsListArea(this->display, this->console, 0, 40, 240, 95);
    this->settingsListArea->setBackground(TFT_BLACK);
    this->settingsListArea->setForeground(TFT_GOLD);
    ((SettingsListArea *)this->settingsListArea)->initEntries(3);
    ((SettingsListArea *)this->settingsListArea)->addEntry(this->model->getModeEntry(), 0);
    ((SettingsListArea *)this->settingsListArea)->addEntry(this->model->getSensitivityEntry(), 1);
    ((SettingsListArea *)this->settingsListArea)->setRefreshPageCallback(this->refreshCallback, this);
}
void SettingPage::refreshCallback(void *page)
{
    SettingPage *self = static_cast<SettingPage *>(page);
    self->show();
}

void SettingPage::show()
{
    display->fillScreen(TFT_BLACK);
    display->setRotation(1);
    this->titleArea->show();
    this->settingsListArea->show();
}

void SettingPage::onButtonEvent(const unsigned int button)
{
    ((SettingsListArea *)this->settingsListArea)->onButtonEvent(button);
}