test(class_AdvancedServo__method__movingValues)
{
    AdvancedServo motor;

    motor.config(P1, 0, 180);
    motor.write(0);

    motor.move(180, 10);

    assertTrue(motor.moving);
    assertFalse(motor.done);
}

test(class_AdvancedServo__method__moveUntilDone)
{
    AdvancedServo motor;
    motor.config(P1, 0, 180);

    assertFalse(motor.moving);

    while (!motor.done)
    {
        assertFalse(motor.done);
        motor.move(180, 10);

        if (motor.done) assertFalse(motor.moving);
        else assertTrue(motor.moving);
    }

    assertTrue(motor.done);
    assertEqual(motor.read(), 180);
    assertEqual(motor.moveId, 1);
}
