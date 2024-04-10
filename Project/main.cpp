#include "main.hpp"

#include <Uart.hpp>
#include <Printer.hpp>
#include <Gpio.hpp>

#include <string>
#include <memory>

#include "NRS-FC-BoardDefinitions.hpp"
namespace NRS = NotRocketScienceFlightComputer;

HAM::Uart USBUart {NRS::USBUartDefinition};
HAM::Printer printer{USBUart};


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
    printer % HAM::PrintType::Log << "This way up " << 43 << "\n";
    printer << "Test\n";
    pin.Toggle();
    HAL_Delay(500);
}
