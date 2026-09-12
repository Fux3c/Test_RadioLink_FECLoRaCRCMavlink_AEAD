#pragma once
#include <stm32f4xx_hal_conf.h>
#include <stm32f4xx_hal_def.h>
#include <stm32f4xx_hal_tim.h>
namespace HAM
{
    typedef uint8_t byte;
    typedef GPIO_TypeDef* GpioPortPointer;
    typedef uint16_t GpioPin; 
    typedef TIM_HandleTypeDef TimerHandle;
    typedef uint32_t PwmChannel;
    typedef ADC_HandleTypeDef* AdcHandlePointer;
    /**
     * @brief Data class to abstract pins attached to microcontroller.
     * 
     */
    struct Pin
    {
        GpioPortPointer port;
        GpioPin pinNumber;
    };
} // namespace HAM
