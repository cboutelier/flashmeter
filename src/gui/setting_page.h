#ifndef SETTING_PAGE_H
#define SETTING_PAGE_H
#include "page.h"
#include "flashmeter_model.h"
#include "entry_renderer.h"


class SettingPage :  public Page{

    private:
        int selectedEntry = 0;
        void adjustSelectedEntry();
    
    protected:
     EntryRenderer *renderers;

    public: 
        SettingPage(TFT_eSPI* display, FlashMeterModel* model);
        void onUp() ;
        void onDown();
        void onLeft();
        void onRight();
        bool onOk();
        void show();
        void declineYourId();
};

#endif //SETTING_PAGE_H