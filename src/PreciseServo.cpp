#include "PreciseServo.h"

void PreciseServo::_adjustDegValue(i8* deg)
{
    *deg = *deg < _minDeg ? _minDeg : *deg;
    *deg = *deg > _maxDeg ? _maxDeg : *deg;
}

void PreciseServo::config(i8 pin, i8 min = 0, i8 max = 180)
{
    this -> attach(pin);
    this -> write(min); // reset to the min value
    _minDeg = min;
    _maxDeg = max;
}

void PreciseServo::preciseWrite(i8 deg, i16 sleep)
{
    deg = deg < this->min ? this->min : deg; // use the min value if it is lesser than that
    deg = deg > this->max ? this->max : deg; // use the max value if it is greater than that

    if (!sleep)
        return this -> write(deg);

    i8 curr = this -> read();

    // while curr != deg, it will approach the target position waiting the speed time each deggre
    for (; curr != deg; deg > curr ? ++curr : --curr)
    {
        this->write(curr);
        delay(sleep);
    }
}
