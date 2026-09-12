#pragma once
#include <adc.h>
#include<HAMTypes.hpp>
namespace HAM
{

    class AnalogToDigital
    {
        private:
            AdcHandlePointer m_handle;
        public:
            AnalogToDigital(const AdcHandlePointer& handle);
            ~AnalogToDigital();
            int PollReadAnalog();
    };
}