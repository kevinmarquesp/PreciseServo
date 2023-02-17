test(minMax_defaultValues)
{
    PreciseServo motor;

    motor.config(10);
    assertEqual(motor.min, 0);
    assertEqual(motor.max, 180);
}

test(minMax_updated_config)
{
    PreciseServo motor;

    motor.config(10, 20, 90);
    motor.config(7, 0, 180);

    assertEqual(motor.min, 0);
    assertEqual(motor.max, 180);
}

test(minMax_updated_hardCoded)
{
    PreciseServo motor;

    motor.config(5, 20, 90);

    motor.min = 0;
    motor.max = 180;

    assertEqual(motor.min, 0);
    assertEqual(motor.max, 180);
}
