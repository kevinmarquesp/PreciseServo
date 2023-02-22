#include "PreciseServo.h"

#ifdef PRECISE_SERVO_DEBUG_FLAG
/** HELPER FUNCTION - print a large number in the serial monitor */
void debug_print64(u64 num)
{
    char buff[24];
    utoa(num, buff, 10);
    Serial.println(String(buff));
}
#endif

/** HELPER FUNCTION - ajust the deg value and tells if the sleep is needed to be considered */
bool local_isRedundant(u8& min, u8& max, u8& deg, u8 sleep)
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
void _BaseServo::config(u8 pin, u8 min=0, u8 max=180)
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
void PreciseServo::move(u8 deg, u8 sleep=0)
{
    if (local_isRedundant(this->min, this->max, deg, sleep))
        return this->write(deg); 

    u8 curr = this->read();

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
    this->moveId = 0;
    this->locked = false;
    this->moving = false;
    this->done = false;
}

/** movement core - backbone of the movement validation */
AdvancedServo* AdvancedServo::move(bool cond, u8 deg, u8 sleep)
{
    // if the user condition isn't true, stop, otherwise, start a new movement
    if (!cond || this->locked)
        return this;
    else
        this->done = false;

    // there is no need to continue if the value is already setted, mark as done
    if (deg == this->read())
    {
        debug_log("AdvancedServo-move/3", "the deg value is the current position");

        _markAsDone();
    }

    // validade the values and finish the movement if it is ok to do that
    if (local_isRedundant(this->min, this->max, deg, sleep))
    {
        debug_log("AdvancedServo-move/3", "the sleep delay was not defined");

        this->write(deg); 
        _markAsDone();
    }

    // when it is ready to move but hasen't started yet, start the shceduler thing
    if (!this->moving && !this->done)
    {
        debug_log("AdvancedServo-move/3", "staring the movement process");

        _scheduler = millis();
        this->moving = true;
    }

    // when already is moving, and every thing is ok, just update the position
    else if (this->moving && !this->done)
        _update(deg, sleep);

    return this;
}

/** shorthand to call the real move function, that has a condition to start */
AdvancedServo* AdvancedServo::move(u8 deg, u8 sleep)
{
    return this->move(this->is(0), deg, sleep);
}

/** instructions that mark this servo object as done */
void AdvancedServo::_markAsDone(void)
{
    debug_log("AdvancedServo-_done/0", "this servo is already in the target position");

    this->done = true;
    this->moving = false;
    ++this->moveId;
}

/** update loop - it will count the milliseconds and write the deg based on that */
void AdvancedServo::_update(u8 deg, u8 sleep)
{
    debug_log("AdvancedServo-_update/2", this->read());

    // count the millis() to check if it is able to make a single movement
    if (millis() - _scheduler >= sleep)
    {
        u8 curr = this->read();
        _scheduler = millis();

        if (deg > curr)
            this->write(this->read() + 1);
        else
            this->write(this->read() - 1);
    }
}

/** user id validation - check if the current motor is the expected id by the user */
bool AdvancedServo::is(u8 id)
{
    return id == this->moveId;
}

/** getter - get the done value of this object instance */
bool AdvancedServo::isDone(void)
{
    return this->done;
}

/** getter (aternative) - get the done value if the motor is in a specific movement */
bool AdvancedServo::isDone(u8 id=0)
{
    return id == this->moveId && this->done;
}

/** instructions to reset the values of an AdvancedServo object instance */
void AdvancedServo::reset(void)
{
    this->moveId = 0;
    this->moving = false;
    this->done = false;
}

/** just a syntaxe helper to run anonymous functions when the movement is completed */
void AdvancedServo::whenDone(void fn(void))
{
    if (this->done) fn();
}

/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * ArrayHeler NAMESPACE FUNCTIONS
 */

/** check if an array of servos is all marked as completed */
bool ArrayHelpers::isAllDone(AdvancedServo* servos, u8 size)
{
    for (u8 i = 0; i < size; ++i)
        if (!servos[i].done)
            return false;
    return true;
}

/** check if all servos has the same movement ID */
bool ArrayHelpers::isAll(AdvancedServo* servos, u8 size, u8 id)
{
    for (u8 i = 0; i < size; ++i)
        if (servos[i].moveId != id)
            return false;
    return true;
}

/** reset an array of multiple servos to their default values */
void ArrayHelpers::resetAll(AdvancedServo* servos, u8 size)
{
    for (u8 i = 0; i < size; ++i)
        servos[i].reset();
}
