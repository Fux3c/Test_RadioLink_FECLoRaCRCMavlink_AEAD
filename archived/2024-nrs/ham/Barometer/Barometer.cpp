#include "Barometer.hpp"
#include "../I2C/I2C.hpp"
#include <I2CBlocking.hpp>
using namespace HAM;

I2C_HandleTypeDef Barometer::defaultI2CDefinition
{
    .Instance = I2C1,
    .Init
    {
        .ClockSpeed = 100000,
        .DutyCycle = I2C_DUTYCYCLE_2,
        .OwnAddress1 = 0,
        .AddressingMode = I2C_ADDRESSINGMODE_7BIT,
        .DualAddressMode = I2C_DUALADDRESS_DISABLE,
        .OwnAddress2 = 0,
        .GeneralCallMode = I2C_GENERALCALL_DISABLE,
        .NoStretchMode = I2C_NOSTRETCH_DISABLE
    }
};

void Barometer::writeToReg(HAM::byte reg, HAM::byte data) const {
    HAM::byte reg_n_data[2] = {reg, data};
    I2CInstance->Write((REG_LPS22HB_ADR<<1),reg_n_data,2);
}
HAM::byte Barometer::readFromReg(HAM::byte reg) const {
    HAM::byte read_data;
    I2CInstance->Write((REG_LPS22HB_ADR<<1),&reg,1);
    I2CInstance->Read((REG_LPS22HB_ADR<<1),&read_data,1);
    return read_data;
}

// using separate function to establish chip, since it can fail.
int Barometer::begin() {
    if (initialised) {
        return 0;
    }
    I2CInstance = new I2CBlocking(&defaultI2CDefinition);

    // Quit if adress dont lead to correct chip
    HAM::byte buf_who_am_i = readFromReg(REG_LPS22HB_WHOAMI);
    if(buf_who_am_i != 0xb1) {
        DebugPrint("LPS22HB's 'Who am I' was not expected value.");
        return 1;
    }

    initialised = true;
    return 0;
}

Barometer::~Barometer()
{
    delete I2CInstance;
}

std::optional<float> Barometer::getPressure() const
{

    if(initialised) {
        
        // set one-shot bit high
        writeToReg(REG_LPS22HB_CTRL2, 0x01);
        HAM::byte ctrl2_read = readFromReg(REG_LPS22HB_CTRL2);
        // Waits for one-shot bit to clear, meaning it's done reading sensor.
        // This is blocking for very short moment
        while ((readFromReg(REG_LPS22HB_CTRL2) & 0x01) != 0) {
            //wait
        }

        // Reading from result registers
        HAM::byte buf_press_out[3];
        HAM::byte press_reg_addrs[3] = {
            REG_LPS22HB_PRESS_XLSB,
            REG_LPS22HB_PRESS_LSB,
            REG_LPS22HB_PRESS_HSB
        };
        DebugPrint("Register values:\n");
        for(int i = 0; i < 3; ++i) {
            DebugPrint(std::to_string(i));
            DebugPrint(": \n");
            buf_press_out[i] = readFromReg(press_reg_addrs[i]);
            DebugPrint(std::to_string(buf_press_out[i]));
            DebugPrint("\n");
        }
        float reading = (
            static_cast<uint32_t>(buf_press_out[0]) |
            (static_cast<uint32_t>(buf_press_out[1]) << 8) |
            (static_cast<uint32_t>(buf_press_out[2]) << 16) 
        ) / 40960.0f;
        DebugPrint("Reading:");
        DebugPrint(std::to_string(static_cast<long>(reading)));
        DebugPrint("\n");
        return reading;
    }
    return {};
}