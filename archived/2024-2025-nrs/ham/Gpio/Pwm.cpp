#include "Pwm.hpp"
using namespace HAM;

Pwm::Pwm(const GpioPortPointer& gpioPort,  const GpioPin& pin, 
            TimerHandle timer, PwmChannel channel):
            Gpio{gpioPort, pin}, m_timerHandle{timer}, m_channel{channel}
{
    
}

void Pwm::SetPwm(const byte& value)
{
    HAL_TIM_PWM_Start(&m_timerHandle, m_channel);
}
