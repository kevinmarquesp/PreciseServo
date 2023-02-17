#include "PreciseServo.h"

/** HELPER FUNCTION - ajust the deg value and tells if the sleep is needed to be considered */
bool _isOkToProceed(i8& min, i8& max, i8& deg, i8 sleep)
{
    deg = deg < min ? min : deg; // use the min value if it is lesser than that
    deg = deg > max ? max : deg; // use the max value if it is greater than that

    // it isn't different from a regular write() if the speed is 0
    return sleep < 1;
}

/** .............................
 * _BaseServo METHOD DEFFINITIONS
 */

/** attach the object to the pin and set the min and max deggre values */
void _BaseServo::config(i8 pin, i8 min=0, i8 max=180)
{
    this->attach(pin);
    this->write(min); // ... also, it resets to the min value on config
    this->min = min;
    this->max = max;
}

/** ...............................
 * PreciseServo METHOD DEFFINITIONS
 */

/** delayed write - sleep x milliseconds each deggre movement to reach the deg position */
void PreciseServo::move(i8 deg, i8 sleep=0)
{
    if (_isOkToProceed(this->min, this->max, deg, sleep))
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
