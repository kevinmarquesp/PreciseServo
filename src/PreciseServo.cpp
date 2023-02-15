#include "PreciseServo.h"

/** .........................
 * DServo METHOD DEFFINITIONS
 */

/** attach the object to the pin and set the min and max deggre values */
void DServo::config(i8 pin, i8 min=0, i8 max=180)
{
    this->attach(pin);
    this->write(min); // ... also, it resets to the min value on config
    this->min = min;
    this->max = max;
}

/** delayed write - sleep x milliseconds each deggre movement to reach the deg position */
void DServo::dwrite(i8 deg, i8 sleep)
{
    deg = deg < this->min ? this->min : deg; // use the min value if it is lesser than that
    deg = deg > this->max ? this->max : deg; // use the max value if it is greater than that

    // it isn't different from a regular write() if the speed is 0
    if (sleep < 1)
        return this->write(deg);

    i8 curr = this->read();

    // while curr != deg, it will approach the target position waiting the sleep time each deggre
    while (curr != deg)
    {
        deg > curr ? ++curr : --curr; // ... iterator

        this->write(curr);
        delay(sleep);
    }
}
