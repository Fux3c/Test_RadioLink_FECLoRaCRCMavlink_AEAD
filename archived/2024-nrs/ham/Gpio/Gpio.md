@ingroup Gpio
# Design Philosophy
The main goal behind the `Gpio` class is to simplify the process of GPIO manipulation, which is a fundamental aspect of hardware-oriented programming. This class encapsulates operations such as toggling and setting the logical state of a pin, as well as reading its current state. The design emphasizes ease of use and flexibility, allowing users to interact with hardware pins in a straightforward manner. This approach enables developers to focus on the logic of their applications without delving into the complexities of hardware-specific programming.


# Usage Example
```cpp
#include "Gpio.hpp"
#inclide "HAMTypes.hpp"

int main() {
    const HAM::Pin ledPin{GPIOE, GPIO_PIN_5};
    HAM::Gpio ledPin{ledPin}; 
    ledPin.Set(true); // Turn on the LED
    ledPin.Toggle(); // Toggle the LED state
    bool isOn = ledPin.Get(); // Check if the LED is on

    return 0;
}
```
See reference for [Gpio](@ref HAM::Gpio)