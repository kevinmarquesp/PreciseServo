test(class_AdvancedServo__method__movingValues)
{
    AdvancedServo motor;

    motor.config(P1, 0, 180);
    // motor.ready = true;

    // assertTrue(motor.ready);
    motor.move(180, 10);

    assertTrue(motor.moving);
    assertFalse(motor.finished);
}

test(class_AdvancedServo__method__moveUntilDone)
{
    AdvancedServo motor;
    motor.config(P1, 0, 180);

    assertFalse(motor.moving);

    while (!motor.finished)
    {
        assertFalse(motor.finished);
        motor.move(180, 10);
        assertTrue(motor.moving);
    }

    assertTrue(motor.finished);
    assertEqual(motor.read(), 180);
    assertEqual(motor.moveId, 1);
}
