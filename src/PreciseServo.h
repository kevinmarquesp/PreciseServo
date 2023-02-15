#ifndef PRECISESERVO_H
#define PRECISESERVO_H

#include <Arduino.h>
#include <Servo.h>

#define i8 uint8_t

/** delayed servo - class to handle the servo speed with delay() function */
class DServo: public Servo
{
  public:
    i8 min;
    i8 max; 
    void config(i8 pin, i8 min, i8 max);
    void dwrite(i8 deg, i8 sleep);
};

#endif
