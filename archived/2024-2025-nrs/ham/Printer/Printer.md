@ingroup Printer
# Design Philosophy
The key idea behind the `Printer` class is to provide a flexible and extensible printing mechanism that can adapt to various debugging requirements without coupling the user's code to specific printing implementations. By using operator overloading, the class offers a streamlined syntax for printing messages, enhancing code readability and ease of use. The class supports printing basic strings, numerical values, and categorized messages (log, warning, error), enabling comprehensive debugging capabilities.

## Dependencies
- `IDebugPrint.hpp`: Interface that defines the `Print` method, which must be implemented by any class that the `Printer` uses to output messages.
- `Printer(IDebugPrint& printer)`: Enables dependency injection, allowing the user to provide any object that implements the `IDebugPrint` interface. This design supports the flexibility and extensibility of printing mechanisms.

## Enumerations
### PrintType
Defines the types of messages that can be printed, allowing for easy categorization and filtering of debug output.
- `Log` - General information about the application's execution.
- `Warning` - Non-critical issues that could potentially lead to problems.
- `Error` - Critical issues that need immediate attention.
### PrintTypeString
- `const char* PrintTypeString[] = {"[Log]: ", "[Warning]: ", "[Error]: "}`: Represents the string representation of each `PrintType`, facilitating readable output.

# Operator Overloads
- `template<typename T> Printer& operator <<(const T& input)`: Extends printing capabilities to various data types, leveraging C++ templates and `std::to_string` for automatic type conversion.
- `Printer& operator % (PrintType type)`: Allows for prefixed message categorization through PrintType, enriching the debug information with type-specific context.

# Usage Example
```cpp
#include "Printer.hpp"
#include "SomeDebugPrintImplementation.hpp"

int main() {
    SomeDebugPrintImplementation debugPrint;
    HAM::Printer printer(debugPrint);

    printer % HAM::Log << "Initialization complete.";
    printer % HAM::Warning << "Deprecated function called.";
    printer % HAM::Error << "Unable to open file.";

    return 0;
}
```

Output
```txt
[Log]: Initialization complete.
[Warning]: Deprecated function called.
[Error]: Unable to open file.
```
See reference [Printer](@ref HAM::Printer)