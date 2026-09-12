#pragma once
#include <HAMTypes.hpp>
namespace NotRocketScienceFlightComputer
{
    const HAM::Pin Servo1{.port = GPIOE, .pinNumber = GPIO_PIN_11};
    const HAM::Pin Servo2{GPIOE, GPIO_PIN_9}; 
    UART_HandleTypeDef USBUartDefinition
    {
        .Instance = USART1,
        .Init{
            .BaudRate = 115200,
            .WordLength = UART_WORDLENGTH_8B,
            .Parity = UART_PARITY_NONE,
            .Mode = UART_MODE_TX_RX,
            .HwFlowCtl = UART_HWCONTROL_RTS_CTS,
            .OverSampling = UART_OVERSAMPLING_16,
        }
    };
    I2C_HandleTypeDef I2CDefinition
    {
        .Instance = I2C1,
        .Init
        {
            .ClockSpeed = 100000,
            .DutyCycle = I2C_DUTYCYCLE_2,
            .OwnAddress1 = 0,
            .AddressingMode = I2C_ADDRESSINGMODE_7BIT,
            .DualAddressMode = I2C_DUALADDRESS_DISABLE,
            .OwnAddress2 = 0,
            .GeneralCallMode = I2C_GENERALCALL_DISABLE,
            .NoStretchMode = I2C_NOSTRETCH_DISABLE
        }
    };
}