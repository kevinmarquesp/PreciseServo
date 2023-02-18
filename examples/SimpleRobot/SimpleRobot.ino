#include <PreciseServo.h>

#define MIN   0   // snippet to move to the min value
#define MAX   180 // snippet to move to the max value
#define SPEED 10  // base movement speed to all servos
#define N     3   // number of servos in usage

const uint8_t pin[N] =    {  5,   6,   7}; // array of pins in use
const uint8_t minDeg[N] = {  0,  45,  90}; // array with the min values for each pin
const uint8_t maxDeg[N] = { 90, 135, 180}; // array with the max values for each pin

PreciseServo group[N]; // array that group 3 PreciseServo objects toguether

void setup(void)
{
        // make config every thing based on the pin, min and max values
        for (int i = 0; i < N; ++i)
        {
                group[i].config(pin[i], minDeg[i], maxDeg[i]);
        }
}

void loop(void)
{
        // make everything go to the max position that it can be
        for (int i = 0; i < N; ++i)
        {
                group[i].move(maxDeg[i], SPEED);
        }

        // make everything go to the min position that it can be
        for (int i = 0; i < N; ++i)
        {
                group[i].move(minDeg[i], SPEED);
        }
}
