#include "precise-servo.h"

void PServo::_adjustDegValue(i8* deg)
{
    *deg = *deg < _minDeg ? _minDeg : *deg;
    *deg = *deg > _maxDeg ? _maxDeg : *deg;
}

void PServo::config(i8 pin, i8 min = 0, i8 max = 180)
{
    this -> attach(pin);
    this -> write(min); // reset to the min value
    _minDeg = min;
    _maxDeg = max;
}

void PServo::preciseWrite(i8 deg, i16 sleep)
{
    _adjustDegValue(&deg);

    if (!sleep)
        return this -> write(deg);

    i8 curr = this -> read();

    for (; curr < deg || curr > deg; deg > curr ? ++curr : --curr)
    {
        this -> write(curr);
        delay(sleep);
    }
}
