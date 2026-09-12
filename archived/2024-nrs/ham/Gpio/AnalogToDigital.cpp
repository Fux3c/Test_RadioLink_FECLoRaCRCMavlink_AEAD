#include "AnalogToDigital.hpp"
using namespace HAM;
AnalogToDigital::AnalogToDigital(const AdcHandlePointer& handle):
m_handle{handle}
{

}
AnalogToDigital::~AnalogToDigital()
{

}
int AnalogToDigital::PollReadAnalog()
{
    HAL_ADC_Start(m_handle);
    HAL_ADC_PollForConversion(m_handle, HAL_MAX_DELAY);
    return HAL_ADC_GetValue(m_handle);
}