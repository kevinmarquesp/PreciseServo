#include <PreciseServo.h>

#define MIN   0   // snippet to move to the min value
#define MAX   180 // snippet to move to the max value
#define SPEED 10  // base movement speed to all servos
#define SIZE  3   // number of servos in usage

#define servo_1 mot[0] // nickname for the first motor in the array
#define servo_2 mot[1] // nickname for the second motor in the array
#define servo_3 mot[2] // nickname for the third motor in the array

const uint8_t pin[SIZE] =    {  5,   6,   7}; // array of pins in use
const uint8_t minDeg[SIZE] = {  0,   0,   0}; // array with the min values for each pin
const uint8_t maxDeg[SIZE] = {180, 180, 180}; // array with the max values for each pin

AdvancedServo mot[SIZE]; // array that group 3 PreciseServo objects toguether
uint8_t scene = 0;

void setup(void)
{
        Serial.begin(9600);

        for (uint8_t i = 0; i < SIZE; ++i)
                mot[i].config(pin[i], minDeg[i], maxDeg[i]);
}

void loop(void)
{
        servo_1.move(180, SPEED)                           // start going to the 180 pos
                ->move(servo_1.is(1), 0, SPEED)            // second movement: start going to the 0 pos
                ->whenDone([](void) { servo_1.reset(); }); // when finished, reset the values and start again

        servo_2.move(180, SPEED/3)                         // start going to the 180 pos                      
                ->move(servo_2.is(1), 0, SPEED/2)          // second movement: start going to the 0 pos
                ->whenDone([](void) { servo_2.reset(); }); // when finished, reset the values and start again

        servo_3.move(180, SPEED)                           // start going to the 180 pos
                ->move(servo_3.is(1), 0, SPEED)            // second movement: start going to the 0 pos        
                ->whenDone([](void) { servo_3.reset(); }); // when finished, reset the values and start again; 
}
