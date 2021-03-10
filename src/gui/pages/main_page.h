#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H
#include "page.h"
#include "../areas/area.h"
#include "../flashmeter_model.h"


class MainPage :  public Page{

    public: 
        MainPage(TFT_eSPI* display, FlashMeterModel *model);
        ~MainPage();
        void onUp() ;
        void onDown();
        void onRight();
        void onLeft();
        bool onOk();
        bool onBack();
        void show();
        void declineYourId();
        Area* focalArea;
        Area* speedArea;
};

#endif //MAIN_PAGE_H