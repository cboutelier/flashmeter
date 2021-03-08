#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H
#include "page.h"
#include "../areas/area.h"
#include "../flashmeter_model.h"


class MainPage :  public Page{

    public: 
        MainPage(TFT_eSPI* display, FlashMeterModel *model);
        void onUp() ;
        void onDown();
        void onRight();
        void onLeft();
        bool onOk();
        void show();
        void declineYourId();
        Area* area;
};

#endif //MAIN_PAGE_H