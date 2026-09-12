#pragma once
#include "../Debug/Debug.hpp"
#include "../I2C/I2C.hpp"
#include <optional>

namespace HAM
{

    enum BarometerRegisters {
        //REG_LPS22HB_CTRL1_RE
        REG_LPS22HB_ADR = 0x5D,

        REG_LPS22HB_WHOAMI = 0x0f,

        REG_LPS22HB_CTRL1 = 0x10,
        REG_LPS22HB_CTRL2 = 0x11,
        REG_LPS22HB_CTRL3 = 0x12,

        REG_LPS22HB_STATUS = 0x27,

        REG_LPS22HB_PRESS_XLSB = 0x28,
        REG_LPS22HB_PRESS_LSB = 0x29,
        REG_LPS22HB_PRESS_HSB = 0x2A,

        REG_LPS22HB_TEMP_LSB = 0x2B,
        REG_LPS22HB_TEMP_HSB = 0x2C,

        REG_LPS22HB_DIG_P1 = 0x8E,
        REG_LPS22HB_DIG_P2 = 0x90,
        REG_LPS22HB_DIG_P3 = 0x92,
        REG_LPS22HB_DIG_P4 = 0x94,
        REG_LPS22HB_DIG_P5 = 0x96,
        REG_LPS22HB_DIG_P6 = 0x98,
        REG_LPS22HB_DIG_P7 = 0x9A,
        REG_LPS22HB_DIG_P8 = 0x9C,
        REG_LPS22HB_DIG_P9 = 0x9E,
    };

    typedef struct {
        // t_fine carries fine temperature as global value
        long t_fine;

        unsigned short dig_P1;
        short dig_P2;
        short dig_P3;
        short dig_P4;
        short dig_P5;
        short dig_P6;
        short dig_P7;
        short dig_P8;
        short dig_P9;
    } calib_press_LPS22HB;


    class Barometer
    {
    private:
        static I2C_HandleTypeDef defaultI2CDefinition;
        I2C* I2CInstance;
        calib_press_LPS22HB calib_data_pressure;
        bool initialised = false;

        // helper functions for reading and writing to i2c regs
        // could be made universally usable and moved into i2c in the future?
        void writeToReg(HAM::byte reg, HAM::byte data) const;
        HAM::byte readFromReg(HAM::byte reg) const;
    public:
        ~Barometer();
        int begin();
        std::optional<float> getPressure() const;
    };
}