#ifndef PRECISESERVO_H
#define PRECISESERVO_H

#include <Arduino.h>
#include <Servo.h>

#define i8  uint8_t
#define i64 uint64_t

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

#endif
