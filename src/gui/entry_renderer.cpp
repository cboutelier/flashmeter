#include "entry_renderer.h"

EntryRenderer::EntryRenderer()
{
    Serial.println("Default constuctor of EntryRenderer");
};

EntryRenderer::EntryRenderer(TFT_eSPI *display, Entry *entry, int yOffset)
{
    this->display = display;
    this->entry = entry;
    this->yOffset = yOffset;
}

void EntryRenderer::show()
{

    Serial.print("VSI ");
    Serial.println(entry->getCurrentValueIndex());
    
    display->setCursor(5, this->yOffset, 2);
    if (this->entrySelected)
    {
        display->setTextColor(this->background_color, this->foreground_color);
    }
    else
    {
        display->setTextColor(this->foreground_color, this->background_color);
    }
    display->print(entry->getEntryName());

    display->setTextColor(this->foreground_color, this->background_color);
    display->print(F(" "));

    int start = 0;
    int maxLength = entry->getEnabledValuesCount();
    /*  if (maxLength > 3)
    {
        Serial.print("HighlightedIndex :");
        Serial.println(this->getHighlightedIndex());
        start = this->getHighlightedIndex() - 1;
        if (start < 0)
        {
            start = 0;
        }
        maxLength = this->getHighlightedIndex() + 2;
        if (maxLength > entry->getEnabledValuesCount())
        {
            maxLength = entry->getEnabledValuesCount();
        }
        Serial.print("Max length:");
        Serial.println(maxLength);
    }

    if (start > 0)
    {
        display->print(F(".. "));
    }
    */
    for (int j = start; j < maxLength; j++)
    {

        unsigned short back_color = this->background_color;
        unsigned short fore_color = this->foreground_color;

        if (j == valueSelectedIndex)
        {
            back_color = this->foreground_color;
            fore_color = this->background_color;
        }
        if (j == entry->getCurrentValueIndex())
        {
            fore_color = this->selected_color;
        }
        display->setTextColor(fore_color, back_color);

        display->print(entry->getValue(j));
        if (j < maxLength - 1)
        {
            display->setTextColor(this->foreground_color, this->background_color);
            display->print(" - ");
        }
    }
    if (maxLength < entry->getEnabledValuesCount())
    {
        display->setTextColor(this->foreground_color, this->background_color);
        display->print(F(" .."));
    }

    Serial.println("Show methow of an entry renderer");
}

/*
void EntryRenderer::setOnSelect(void (*func)())
{
    this->onSelect = func;
}
*/

void EntryRenderer::init(TFT_eSPI *display, Entry *entry, int yOffset)
{
    this->display = display;
    this->entry = entry;
    this->yOffset = yOffset;
}

void EntryRenderer::setInitialColors(unsigned short background, unsigned short foreground, unsigned short selected)
{
    this->background_color = background;
    this->foreground_color = foreground;
    this->selected_color = selected;
}

void EntryRenderer::onRight()
{
    Serial.println("On right");
    Serial.print("VSI ---->");
    Serial.println(valueSelectedIndex);
    Serial.print("EVC ---->");
    Serial.println(entry->getEnabledValuesCount());
    if (valueSelectedIndex < entry->getEnabledValuesCount())
    {
        Serial.print("Increase value index");
        valueSelectedIndex++;
    }
    Serial.print("On Right on ");
    Serial.println(this->entry->getEntryName());
    this->show();
}

bool EntryRenderer::onOk()
{
    Serial.println("On ok");
    Serial.print("VSI ---->");
    Serial.println(valueSelectedIndex);

    if (valueSelectedIndex > -1 && this->entry->getCurrentValueIndex() != valueSelectedIndex)
    {
        this->entry->setCurrentValueIndex(valueSelectedIndex);
        this->show();
        return true;
    }
    return false;
}

void EntryRenderer::onLeft()
{
    if (valueSelectedIndex >= 0)
    {
        valueSelectedIndex--;
    }
    Serial.print("On left on ");
    Serial.println(this->entry->getEntryName());
    this->show();
}