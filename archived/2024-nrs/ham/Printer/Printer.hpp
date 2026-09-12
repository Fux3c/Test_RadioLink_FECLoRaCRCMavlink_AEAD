#pragma once

#include "IDebugPrint.hpp"

namespace HAM
{
    enum PrintType
    {
        Log,
        Warning,
        Error
    };
    const char* PrintTypeString[] = {"[Log]: ", "[Warning]: ", "[Error]: "};
    /**
     * @brief Wrapper class to abstract Print implementation.
     * 
     */
    class Printer
    {
    private:
        IDebugPrint* m_printer{nullptr};///< Pointer reference to a object that implements Print
    public:
        /**
         * @brief Construct a new Printer object
         * 
         * @param printer Object that implements Print. 
         */
        Printer(IDebugPrint& printer): m_printer{&printer}{};
        /**
         * @brief Operator overloaded printing for const char*. Can be chained:
         * 
         * @code
         *      Printer << "Hello " << "World!";
         * @endcode 
         * 
         * @param input 
         * @return Printer& 
         */
        inline Printer& operator <<(const char* input){m_printer->Print(input); return *this;}
        /**
         * @brief Templated operator overloaded printing. Can be chained, ie Printer << "Hello " << "World!";
         * 
         * @param input 
         * @return Printer& 
         */
        template<typename T> inline Printer& operator <<(const T& input){m_printer->Print(std::to_string(input)); return *this;}
        /**
         * @brief Operator for providing what type of debug
         * 
         * Choosing a debug will append a categorization message
         * Available options are: Log, Warning, Error
         * Will output: [Log]: , [Warning]: , [Error]: 
         * @code {.cpp}
         *      Printer % PrintType::Log << "Something is logged";
         * @endcode
         * Will result in
         * @code {.shell}
         * [Log]: Something is logged
         * @endcode
         * 
         * 
         * @param type 
         * @return Printer& 
         */
        inline Printer& operator % (PrintType type){m_printer->Print(PrintTypeString[type]); return *this;}
        ~Printer() = default;
    };
}
