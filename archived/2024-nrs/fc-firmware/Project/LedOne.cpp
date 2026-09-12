#include "LedOne.hpp"
#include "cmsis_os.h"
#include <Gpio.hpp>
#include "NRS-FC-BoardDefinitions.hpp"

void LedOneEntry(void* argument)
{
    namespace NRS = NotRocketScienceFlightComputer;
    GPIO_InitTypeDef config = NRS::outputConfig;
    HAM::Gpio pin = HAM::Gpio{NRS::Servo1, NRS::outputConfig};
    while (1)
    {
      pin.Toggle();
      // HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_11);
      osDelay(500);
      /* code */
    }
}