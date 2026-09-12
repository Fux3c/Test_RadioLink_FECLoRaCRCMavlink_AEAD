#include "LedTwo.hpp"
#include "cmsis_os.h"
#include <Gpio.hpp>
#include "NRS-FC-BoardDefinitions.hpp"
void LedTwoEntry(void* argument)
{
    namespace NRS = NotRocketScienceFlightComputer;
    HAM::Gpio pin = HAM::Gpio{NRS::Servo2, NRS::outputConfig};
    // HAM::Gpio pin = HAM::Gpio{GPIOE, GPIO_PIN_9};

    while (1)
    {
      pin.Toggle();
      osDelay(1000);
      /* code */
    }
}