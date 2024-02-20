#include "main.hpp"

#include <Uart.hpp>
#include <Printer.hpp>
#include <Gpio.hpp>

#include <string>
#include <memory>

#include "NRS-FC-BoardDefinitions.hpp"

HAM::Uart usart1 {huart1};
HAM::Printer printer{usart1};

namespace NRS = NotRocketScienceFlightComputer;

/**
 * @brief Initialization function, only ran once.
*/
void init()
{
}
/**
 * @brief Main function to be run continuously.
 * 
 */
void loop()
{
    static HAM::Gpio pin = HAM::Gpio{NRS::Servo1};
    printer % HAM::PrintType::Log << "This way up " << 43;
    pin.Toggle();
    HAL_Delay(500);
}
