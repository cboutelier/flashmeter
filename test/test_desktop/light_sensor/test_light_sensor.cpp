#ifdef UNIT_TEST

#include <unity.h>
#include "light_sensor/light_sensor.h"
#include "flashmeter_model.h"
#include "MockLightSensor.h"

void test_LightSensor() {
    MockLightSensor mockLS;
    FlashMeterModel fmm;
    LightSensor* ls = new LightSensor(&mockLS, &fmm);
    TEST_ASSERT_EQUAL(ls->calculateSpeedIndex(5, 0, 0), 19);
}

int main( int argc, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_LightSensor);

    UNITY_END();
}

#endif