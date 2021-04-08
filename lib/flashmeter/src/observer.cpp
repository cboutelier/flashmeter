#include "observer.h"

void Observer::attachSubject(Observable *model)
{
    model->registerObserver(this);
}
