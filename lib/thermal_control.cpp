//
// Created by syvers on 27.07.25.
//

#include "config.h"

void checkThermalStatus(float currentTemp, bool &thermallyThrottling) {
    if (currentTemp > THERMAL_THROTTLE_THRESHOLD) {
        thermallyThrottling = true;
    } else if (currentTemp < THERMAL_THROTTLE_THRESHOLD - 1) {
        thermallyThrottling = false;
    }
}
