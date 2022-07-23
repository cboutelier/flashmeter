#ifdef UNIT_TEST

#include <unity.h>
#include "MockLightSensor.h"
#include "desktop_console.h"
#include "light_sensor.h"

DesktopConsole *console;
MockLightSensor *mls;
LightSensor *ls;


void setUp(void)
{
    console = new DesktopConsole();
    mls = new MockLightSensor();
    ls = new LightSensor(mls, console, 1);
    
}

void tearDown(void)
{
    delete (ls);
    delete (mls);
    delete (console);
}


void test_LightSensor_80()
{

    mls->setDesiredLux(80.0f);
    LightReadingResult *r = ls->read();
    TEST_ASSERT_EQUAL(r->getLux(), 80.0f);
    TEST_ASSERT_EQUAL(r->getEV100(), 5);
}

void test_LightSensor_00()
{
    mls->setDesiredLux(0.0f);
    LightReadingResult *r = ls->read();
    TEST_ASSERT_EQUAL(r->getLux(), 0.0f);
    TEST_ASSERT_EQUAL(r->isSuccess(), false);
    TEST_ASSERT_EQUAL(r->getEV100(), -1);
}

void test_LightSensor_81900()
{
    mls->setDesiredLux(81900.0f);
    LightReadingResult *r = ls->read();
    TEST_ASSERT_EQUAL(81900.0f, r->getLux());
    TEST_ASSERT_EQUAL(14, r->getEV100());
}
int main(int argc, char **argv)
{
    UNITY_BEGIN();
    RUN_TEST(test_LightSensor_80);
    RUN_TEST(test_LightSensor_81900);
    RUN_TEST(test_LightSensor_00);
    UNITY_END();
}

#endif