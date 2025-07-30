//
// Created by syvers on 27.07.25.
//

#include <unity.h>
#include "../lib/thermal_control.cpp"
#include <Arduino.h>



void test_thermal_throttle_condition() {
    //delay(2000);

    bool isThermallyThrottling = false;
    checkThermalStatus(100,isThermallyThrottling);
    TEST_ASSERT_TRUE(isThermallyThrottling);

    checkThermalStatus(50,isThermallyThrottling);
    TEST_ASSERT_FALSE(isThermallyThrottling);
}

