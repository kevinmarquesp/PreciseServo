test(default_leepValue)
{
    PreciseServo motor;
    uint64_t timer;
    uint64_t result;

    motor.config(5, 0, 180);

    timer = millis();
    motor.move(180);
    result = millis() - timer;

    assertTrue(result == 0);
}
