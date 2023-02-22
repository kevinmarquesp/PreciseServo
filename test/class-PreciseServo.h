test (class_PreciseServo__defaultConfigValues)
{
    PreciseServo motor;

    motor.config(P1);
    assertEqual(motor.min, 0);
    assertEqual(motor.max, 180);
}

test (class_PreciseServo__updatingServoConfig)
{
    PreciseServo motor;

    motor.config(P1, 20, 90);
    motor.config(P2, 0, 180);

    assertEqual(motor.min, 0);
    assertEqual(motor.max, 180);
}

test (class_PreciseServo__changeMinMaxValues)
{
    PreciseServo motor;

    motor.config(P1, 20, 90);

    motor.min = 0;
    motor.max = 180;

    assertEqual(motor.min, 0);
    assertEqual(motor.max, 180);
}

test (class_PreciseServo__defaultSpeedValue)
{
    PreciseServo motor;
    i64 timer;
    i64 result;

    motor.config(P1, 0, 180);

    timer = millis();
    motor.move(180);
    result = millis() - timer;

    assertTrue(result <= 1);
}

test (class_PreciseServo__customSpeedDuration)
{
    PreciseServo motor;
    i64 timer;
    i64 result;

    motor.config(P1, 0, 180);

    timer = millis();
    motor.move(180, 10);
    result = millis() - timer;

    assertTrue(result >= 10 * 180);
}
