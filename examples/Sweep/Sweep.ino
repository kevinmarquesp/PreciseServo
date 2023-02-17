#include <PreciseServo.h>

#define PIN        7
#define BASE_DELAY 20
#define PAUSE      3000

PreciseServo motor;

void setup(void)
{
        Serial.begin(9600);
        motor.config(PIN, 0, 180);
}

void loop(void)
{
        motor.move(180, BASE_DELAY);
        delay(PAUSE);

        motor.move(0, BASE_DELAY/2);
        delay(PAUSE);
}
