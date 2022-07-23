#ifdef UNIT_TEST

#include <unity.h>
#include "desktop_console.h"
#include "exposure_calculator.h"

ExposureCalculator *calculator;

void setUp(void)
{
    calculator = new ExposureCalculator();
}

void tearDown(void)
{
    delete calculator;
}

void test_GetOffset_800()
{
    TEST_ASSERT_EQUAL(-3, calculator->getEVOffset(800));
}

void test_GetOffset_200()
{
    TEST_ASSERT_EQUAL(-1, calculator->getEVOffset(200));
}

void test_GetOffset_100()
{
    TEST_ASSERT_EQUAL(0, calculator->getEVOffset(100));
}

void test_GetOffset_50()
{
    TEST_ASSERT_EQUAL(1, calculator->getEVOffset(50));
}

void test_GetOffset_0()
{
    bool catched = false;
    try
    {
        calculator->getEVOffset(0);
    }
    catch (InvalidIsoException i)
    {
        catched = true;
    }
    TEST_ASSERT_EQUAL(true, catched);
}

void test_GetAperture_loose()
{
    TEST_ASSERT_EQUAL_FLOAT(5.6, calculator->getAperture(5.6, false));
    TEST_ASSERT_EQUAL_FLOAT(5.6, calculator->getAperture(5.7, false));
}

/**
 * This test will fail when the third steps will be implemented
 **/
void test_GetApertures()
{
    ApertureEntry **apertures = calculator->getApertures();
    /* for (int j = 0; j < 20; j++)
     {
         ApertureEntry *aperture = apertures[j];
         cout << j << " Display:" << aperture->getDisplay() << " Simplified:" << aperture->getSimplified() << " Value " << aperture->getValue() << endl;
     }
     */

    TEST_ASSERT_EQUAL_STRING("f/1", apertures[0]->getDisplay());
    TEST_ASSERT_EQUAL_STRING("f/2", apertures[2]->getDisplay());
    TEST_ASSERT_EQUAL_STRING("f/4", apertures[4]->getDisplay());
    TEST_ASSERT_EQUAL_STRING("f/11", apertures[7]->getDisplay());
}

void test_GetSpeeds()
{
    ShutterSpeedEntry **speeds = calculator->getShutterSpeeds();
    for (int j = 0; j < 10; j++)
    {
        ShutterSpeedEntry *entry = speeds[j];
        cout << j << " Display:" << entry->getDisplay() << " Value " << entry->getValue() << endl;
    }
}

void test_GetSpeedForAperture_EV10_5ISO100()
{
    LightReadingResult *reading = new LightReadingResult(1, true, 56.0, 10);
    ExposureProposal *result = calculator->getSettingsForDefinedAperture(reading, 5.6, 100);
    cout << "lux:" << result->lux << " iso:" << result->iso << " aperture:" << result->aperture << " speed:" << result->speed << " " << result->speedDisplay << endl;
    TEST_ASSERT_EQUAL_STRING("1/30", result->speedDisplay);
}

void test_GetSpeedForAperture_EV11_5ISO100()
{
    LightReadingResult *reading = new LightReadingResult(1, true, 56.0, 11);
    ExposureProposal *result = calculator->getSettingsForDefinedAperture(reading, 5.6, 100);
   TEST_ASSERT_EQUAL_STRING("1/60", result->speedDisplay);
}

void test_GetSpeedForAperture_EV10_5ISO200()
{
    LightReadingResult *reading = new LightReadingResult(1, true, 56.0, 10);
    ExposureProposal *result = calculator->getSettingsForDefinedAperture(reading, 5.6, 200);
    TEST_ASSERT_EQUAL_STRING("1/60", result->speedDisplay);
}

void test_GetSpeedForAperture_EV10_5ISO400()
{
    LightReadingResult *reading = new LightReadingResult(1, true, 56.0, 10);
    ExposureProposal *result = calculator->getSettingsForDefinedAperture(reading, 5.6, 400);
    TEST_ASSERT_EQUAL_STRING("1/125", result->speedDisplay);
}

void test_GetSpeedForAperture_EV10_8ISO100()
{
    LightReadingResult *reading = new LightReadingResult(1, true, 56.0, 10);
    ExposureProposal *result = calculator->getSettingsForDefinedAperture(reading, 8, 100);
    TEST_ASSERT_EQUAL_STRING("1/15", result->speedDisplay);
}
void test_GetSpeedForAperture_EV10_4ISO100()
{
    LightReadingResult *reading = new LightReadingResult(1, true, 56.0, 10);
    ExposureProposal *result = calculator->getSettingsForDefinedAperture(reading, 4, 100);
    TEST_ASSERT_EQUAL_STRING("1/60", result->speedDisplay);
}

void test_GetApertureOffset_5_4()
{
    TEST_ASSERT_EQUAL(-1, calculator->getApertureOffset(5.6, 4));
}

void test_GetApertureOffset_5_8()
{
    TEST_ASSERT_EQUAL(1, calculator->getApertureOffset(5.6, 8));
}
void test_GetApertureOffset_5_11()
{
    TEST_ASSERT_EQUAL(2, calculator->getApertureOffset(5.6, 11));
}
/*
int main(int argc, char **argv)
{
   
}*/

int runUnityTests(void) {
   UNITY_BEGIN();
    RUN_TEST(test_GetOffset_800);
    RUN_TEST(test_GetOffset_200);
    RUN_TEST(test_GetOffset_100);
    RUN_TEST(test_GetOffset_50);
    RUN_TEST(test_GetOffset_0);

    RUN_TEST(test_GetApertures);

    RUN_TEST(test_GetAperture_loose);
    RUN_TEST(test_GetSpeeds);
    RUN_TEST(test_GetSpeedForAperture_EV10_5ISO100);
    RUN_TEST(test_GetSpeedForAperture_EV11_5ISO100);
    RUN_TEST(test_GetSpeedForAperture_EV10_5ISO200);
    RUN_TEST(test_GetSpeedForAperture_EV10_5ISO400);
    RUN_TEST(test_GetSpeedForAperture_EV10_8ISO100);
    RUN_TEST(test_GetSpeedForAperture_EV10_4ISO100);
    RUN_TEST(test_GetApertureOffset_5_4);
    RUN_TEST(test_GetApertureOffset_5_8);
    RUN_TEST(test_GetApertureOffset_5_11);

    return UNITY_END();
}

// WARNING!!! PLEASE REMOVE UNNECESSARY MAIN IMPLEMENTATIONS //

/**
  * For native dev-platform or for some embedded frameworks
  */
int main(void) {
  return runUnityTests();
}

#endif