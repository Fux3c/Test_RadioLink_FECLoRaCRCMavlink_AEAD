#pragma once
#include "Uart.hpp"

#ifdef DEBUG
UART_HandleTypeDef DebugUSBUartDefinition
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
HAM::Uart DebugUart{DebugUSBUartDefinition};

#define DebugPrint(VAR1) DebugUart.Print(VAR1) 
#else
#define DebugPrint(VAR1)
#endif
