#define PIN1 5
#define PIN2 6

test(clsPreciseServo, checkDefaultValues)
{
    PreciseServo motor1;
    PreciseServo motor2;

    motor1.config(PIN1, 90, 180);
    motor2.config(PIN2,  0,  90);

    assertEqual(motor1.read(),    90);
    assertEqual(motor1.getMin(),  90);
    assertEqual(motor1.getMax(), 180);

    assertEqual(motor2.read(),    0);
    assertEqual(motor2.getMin(),  0);
    assertEqual(motor2.getMax(), 90);

    motor1.detach();
    motor2.detach();
}

test(clsPreciseServo, delayedMovementDuration)
{
    PreciseServo motor1;
    PreciseServo motor2;

    const uint8_t ll[2] = {0, 180}; // max and min limits
    const uint8_t bSpeed = 10;      // base speed
    uint64_t timer;                 // to hold the time

    // void setup(void) {...}
    const uint8_t la[2] = {90, 180};
    const uint8_t lb[2] = { 0,  90};

    motor1.config(PIN1, la[0], la[1]);
    motor2.config(PIN2, lb[0], lb[1]);

    // void loop(void) {...}
    timer = millis();
    motor1.move(ll[1], bSpeed);
    motor2.move(ll[1], bSpeed/2);
    assertTrue(millis() - timer >= bSpeed + bSpeed/2);

    timer = millis();
    motor1.move(ll[0], bSpeed);
    motor2.move(ll[0], bSpeed/2);
    assertTrue(millis() - timer >= bSpeed + bSpeed/2);

    motor1.detach();
    motor2.detach();
}
