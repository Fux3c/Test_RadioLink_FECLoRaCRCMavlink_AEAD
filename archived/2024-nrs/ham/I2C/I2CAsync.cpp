#include "I2CAsync.hpp"

using namespace HAM;

I2CAsync::I2CAsync(I2C_HandleTypeDef* I2CDefinition):
I2C{I2CDefinition}
{
}

bool I2CAsync::Write(const byte& address, byte* bytes, const size_t& size)
{
    return HAL_I2C_Master_Transmit_DMA(m_handle, address, bytes, size) == HAL_OK;
}
bool I2CAsync::Read(const byte& address, byte* bytes, const size_t& size)
{
    
}

I2CAsync::~I2CAsync()
{
}