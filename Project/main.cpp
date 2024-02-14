#include "main.h"
#include <Project/main.hpp>

struct Led
{
    explicit Led(GPIO_TypeDef* t_gpio, uint16_t t_pin)
        : gpio(t_gpio)
        , pin(t_pin)
    {
    }
    void on()
    {
        HAL_GPIO_WritePin(gpio, pin, GPIO_PIN_SET);
    }
    void off()
    {
        HAL_GPIO_WritePin(gpio, pin, GPIO_PIN_RESET);
    }
    void toggle()
    {
        HAL_GPIO_TogglePin(gpio, pin);
    }
    auto state() -> bool
    {
        return HAL_GPIO_ReadPin(gpio, pin);
    }

private:
    GPIO_TypeDef* gpio;
    uint16_t pin;
};
Led led = Led(GPIOE, GPIO_PIN_11);

/// @brief Initialization function, only ran once.
void init()
{
    
}

/// @brief Main function to be run continuously.
void loop()
{
    led.toggle();
    HAL_Delay(500);

}
