#pragma once
/**
 * @ingroup gpio
 * 
 */
#include <gpio.h>
#include <HAMTypes.hpp>
namespace HAM{
    const static GPIO_InitTypeDef GpioDefaultInit{
        .Mode = GPIO_MODE_INPUT,
        .Pull = GPIO_NOPULL
    };
    class Gpio
    {
    private:
        // GpioPortPointer m_port{nullptr};
        // GpioPin m_pin;
        Pin m_pin;
    public:
        Gpio(const GpioPortPointer& gpioPort,  const GpioPin& pin);
        Gpio(const Pin& pin, const GPIO_InitTypeDef& config = GpioDefaultInit);

        ~Gpio();
        /**
         * @brief Toggles logical state of pin.
         * 
         */
        void Toggle();
        /**
         * @brief Sets the logical state of pin.
         * 
         * @param state High or Low
         */
        void Set(const bool& state);
        /**
         * @brief Gets the digital state of the pin.
         * 
         * @return bool   => Logical high
         * @return false  => Logical low
         */
        const bool Get() const;
    };
}
