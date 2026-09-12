#pragma once
#include "I2C.hpp"

namespace HAM
{
    class I2CBlocking: public I2C
    {
    private:
        /* data */
    public:
        I2CBlocking(I2C_HandleTypeDef* I2CDefinition);
        bool Write(const byte& address, byte* bytes, const size_t& size);
        bool Read(const byte& address, byte* bytes, const size_t& size);
        ~I2CBlocking();
    };
}


