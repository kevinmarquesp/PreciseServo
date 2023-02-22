#ifndef PRECISESERVO_H
#define PRECISESERVO_H

#include <Arduino.h>
#include <Servo.h>

#define i8  uint8_t
#define i64 uint64_t

// DEVELOPING TIP - (un)comment the line above to activate/deactvate the debbuger printer
// #define PRECISE_SERVO_DEBUG

#ifdef PRECISE_SERVO_DEBUG
// HELPER FUNCTION - print a large number in the serial monitor
void debug_print64(i64 num);

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
#else
#define debug_log(flag, msg)
#define debug_log64(flag, msg)
#endif

/** base attributes/methods that every servo class has in this library */
class _BaseServo: public Servo
{
  public:
    void config(i8 pin, i8 min=0, i8 max=180);
    i8 min, max; 
};

/** delayed servo - class to handle the servo speed with delay() function */
class PreciseServo: public _BaseServo
{
  public:
    void move(i8 deg, i8 sleep=0);
};

/** millis servo - same as PreciseServo but with millis() instead of delay() */
class AdvancedServo: public _BaseServo
{
  public:
    i8 moveId;
    bool locked, moving, done;
    AdvancedServo(void);
    bool is(i8 id);
    bool isDone(void);
    bool isDone(i8 id);
    AdvancedServo* move(bool cond, i8 deg, i8 sleep);
    AdvancedServo* move(i8 deg, i8 sleep);
    void reset(void);
    void whenDone(void fn(void));

  private:
    i64 _scheduler;
    void _update(i8 deg, i8 sleep);
    void _markAsDone(void);
};

/** ... */
namespace ArrayHelpers
{
    bool isAllDone(AdvancedServo* servos, i8 size);
    bool isAll(AdvancedServo* servos, i8 size, i8 id);
    void resetAll(AdvancedServo* servos, i8 size);
}

#endif
