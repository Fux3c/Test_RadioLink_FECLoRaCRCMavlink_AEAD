#pragma once
#include <string>

namespace HAM
{
    /**
     * @brief Interface class to provide a standardized print.
     * 
     */
    class IDebugPrint
    {
    public:
        IDebugPrint() = default;
        ~IDebugPrint() = default;
        virtual void Print(const std::string& input) const = 0;
    };
}

