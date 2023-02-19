// DEVELOPING TIP - (un)comment the line above to activate/deactvate the debbuger printer
#define PRECISE_SERVO_DEBUG_FLAG

#include "PreciseServo.h"

#ifdef PRECISE_SERVO_DEBUG_FLAG
    // list of commands to show a log line in the serial port
    #define debug_log(flag,msg)   \
        Serial.print(flag);       \
        Serial.print(":");        \
        Serial.print(__LINE__);   \
        Serial.print(" :: ");     \
        Serial.println(msg)

    // list of commands to do the same thing, but to show a large number
    #define debug_log64(flag,num) \
        Serial.print(flag);       \
        Serial.print(":");        \
        Serial.print(__LINE__);   \
        Serial.print(" :: ");     \
        debug_print64(num)

    /** HELPER FUNCTION - print a large number in the serial monitor */
    void debug_print64(i64 num)
    {
        char buff[24];
        utoa(num, buff, 10);
        Serial.println(String(buff));
    }
#else
    #define debug_log(flag, msg)
    #define debug_log64(flag, msg)
#endif

/** HELPER FUNCTION - ajust the deg value and tells if the sleep is needed to be considered */
bool _isOkToProceed(i8& min, i8& max, i8& deg, i8 sleep)
{
    deg = deg < min ? min : deg; // use the min value if it is lesser than that
    deg = deg > max ? max : deg; // use the max value if it is greater than that

    // it isn't different from a regular write() if the speed is 0
    return sleep < 1;
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
        delay(curr == deg ? 0 : sleep); // the last sleep is irrelevant

        debug_log("PreciseServo-move/2", curr);
    }
}


/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * AdvancedServo METHOD DEFFINITIONS
 */

/** AdvancedServo - constructor to set the boolean values to false by default */
AdvancedServo::AdvancedServo(void)
{
    this->ready = false;
    this->moving = false;
    this->finished = false;
}

/** movement core - backbone of the movement validation */
AdvancedServo* AdvancedServo::move(bool cond, i8 deg, i8 sleep)
{
    // validade the values and finisht if is ok to do that
    if (_isOkToProceed(this->min, this->max, deg, sleep))
    {
        this->write(deg); 
        _done();
    }

    // when it is ready to move but hasen't started yet
    if (cond && this->ready && !this->finished)
    {
        debug_log("AdvancedServo-move/3", "staring the movement process");

        _scheduler = millis();
        this->moving = true;
    }

    // when already is moving, and every thing is ok, just update the position
    if (cond && this->moving && !this->finished)
        _update(deg);

    return this;
}

/** shorthand to call the real move function, that has a condition to start */
AdvancedServo* AdvancedServo::move(i8 deg, i8 sleep)
{
    this->move(true, deg, sleep);
}

/** instructions that mark this servo object as done */
void AdvancedServo::_done(void)
{
    debug_log("AdvancedServo-_done/0", "this servo is already in the target position");

    this->ready = false;
    this->finished = true;
    ++this->moveId;
}

/** update loop - it will count the milliseconds and write the deg based on that */
void AdvancedServo::_update(i8 deg)
{
}
