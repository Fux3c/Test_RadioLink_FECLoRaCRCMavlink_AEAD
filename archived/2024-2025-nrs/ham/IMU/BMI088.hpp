#pragma once
#include <ISensorAsync.hpp>
#include <I2C.hpp>

namespace HAM
{
    class BMI088: public ISensorAsync
    {
    private:
        
    public:
        BMI088(/* args */);
        bool initiateReading() final;
        void onNewReading() final;
        ~BMI088();
    };
    
}

