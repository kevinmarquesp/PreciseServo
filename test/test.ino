#include <ArduinoUnit.h>
#include <PreciseServo.h>

#define P1 7

void log64(i64 n)
{
    char buff[24];
    utoa(n, buff, 10);
    Serial.print(String(buff));
}

void log64ln(i64 n)
{
    log64(n);
    Serial.print('\n');
}

#include "./class-PreciseServo.h"
#include "./class-AdvancedServo.h"

void setup(void)
{
    Serial.begin(9600);
    while (!Serial) {}; // portability for leonardo/micro

    #ifdef PRECISE_SERVO_DEBUG
    Test::exclude("class_PreciseServo__defaultSpeedValue");
    #endif
}

void loop(void)
{
    Test::run();
}
