#include  "observer.h"
#include "flashmeter_model.h"


void Observer::attachSubject(FlashMeterModel* model){
    model->registerObserver(this);
}

