#pragma once
#include <HAMTypes.hpp>
#include <BMI088/Accelerometer.hpp>
namespace NotRocketScienceFlightComputer
{
    const static GPIO_InitTypeDef outputConfig{
        .Mode = GPIO_MODE_OUTPUT_PP,
        .Pull = GPIO_NOPULL,
        .Speed = GPIO_SPEED_FREQ_LOW
    };
    const HAM::Pin RTS{GPIOA, GPIO_PIN_12};
    const HAM::Pin Servo1{.port = GPIOE, .pinNumber = GPIO_PIN_11};
    const HAM::Pin Servo2{GPIOE, GPIO_PIN_9}; 
    const HAM::Pin USBUartRTS{GPIOA, GPIO_PIN_12};
    static UART_HandleTypeDef USBUartDefinition
    {
        .Instance = USART1,
        .Init{
            .BaudRate = 115200,
            .WordLength = UART_WORDLENGTH_8B,
            .Parity = UART_PARITY_NONE,
            .Mode = UART_MODE_TX_RX,
            .HwFlowCtl = UART_HWCONTROL_NONE,
            .OverSampling = UART_OVERSAMPLING_16,
        }
    };
    static I2C_HandleTypeDef I2CDefinition
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
    const static HAM::BMI088::Accelerometer::Config AccelerometerConfig
    {
        .AccelerometerODR  = HAM::BMI088::AccelerometerRegisters::ACC_CONF::Hz25
    };
    const HAM::byte BMIAccelerometerAddress = 0x18;
    const HAM::byte BMIGyroAddress = 0x68;
}