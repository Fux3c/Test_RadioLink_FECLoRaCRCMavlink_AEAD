#pragma once
#include "Gpio.hpp"
namespace HAM
{
    class Pwm: public Gpio
    {
    private:
        TimerHandle m_timerHandle;
        PwmChannel m_channel;
    public:
        Pwm(const GpioPortPointer& gpioPort,  const GpioPin& pin, 
            TimerHandle timer, PwmChannel channel);
        ~Pwm() = delete;
        void SetPwm(const byte& value);
    };
}