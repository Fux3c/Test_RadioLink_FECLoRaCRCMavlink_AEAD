#pragma once
class IAccelerometer
{
public:
    virtual float X() = 0;
    virtual float Y() = 0;
    virtual float Z() = 0;
    virtual float TotalAcceleration() = 0;
};


