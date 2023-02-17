#include <ArduinoUnit.h>
#include <PreciseServo.h>

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

void setup(void)
{
    Serial.begin(9600);
    while (!Serial) {}; // portability for leonardo/micro
}

void loop(void)
{
    Test::run();
}
