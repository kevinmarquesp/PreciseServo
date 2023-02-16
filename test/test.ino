#include <ArduinoUnit.h>
#include <PreciseServo.h>

#include "./class-PreciseServo_attribute-values.h"

void setup(void)
{
    Serial.begin(9600);
    while (!Serial) {}; // portability for leonardo/micro
}

void loop(void)
{
    Test::run();
}
