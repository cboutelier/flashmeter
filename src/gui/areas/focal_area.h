#ifndef FOCAL_AREA_H
#define FOCAL_AREA_H

#include <Arduino.h>
 
#include "area.h"

class FocalArea : public Area {

    public :
    using Area::Area;
     virtual void show();
     virtual void fillArea();
     void onReceiveDataFromSubject(const FlashMeterModel* model);
};

#endif //FOCAL_AREA_H