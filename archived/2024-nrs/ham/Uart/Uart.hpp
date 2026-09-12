#pragma once

#include <IDebugPrint.hpp>
#include <usart.h>
#include <HAMTypes.hpp>

namespace HAM
{

    class Uart: public IDebugPrint
    {
    private:
        UART_HandleTypeDef* m_uart = nullptr;
    public:
        Uart(UART_HandleTypeDef& uart);
        ~Uart();
        void Print(const std::string& input) const final;
    };
}


