#include "Uart.hpp"
using namespace HAM;

Uart::Uart(UART_HandleTypeDef& uart):
m_uart{&uart}
{
  // TODO 
  // Provide some error handling here
  HAL_UART_Init(m_uart);
}

Uart::~Uart()
{
}

void Uart::Print(const std::string& input) const
{
    HAL_UART_Transmit(m_uart, reinterpret_cast<const uint8_t*>(&input[0]), static_cast<uint16_t>(input.length()), 50);
}