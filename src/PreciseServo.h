#ifndef BTNHANDLER_H
#define BTNHANDLER_H

#include <Arduino.h>
#include <Servo.h>

#define i8  uint8_t
#define i16 uint16_t

class PreciseServo: public Servo
{
  private:
    i8 _minDeg;
    i8 _maxDeg; 
    void _adjustDegValue(i8*);

  public:
    void config(i8, i8, i8);
    void preciseWrite(i8, i16);
};

#endif
