#ifndef MAIN_PAGE_H
#define MAIN_PAGE_H
#include "page.h"


class MainPage :  public Page{

    public: 
        MainPage(TFT_eSPI* display);
        void onUp() ;
        void onDown();
        void onRight();
        void onLeft();
        bool onOk();
        void show();
        void declineYourId();
};

#endif //MAIN_PAGE_H