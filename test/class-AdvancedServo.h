test (class_AdvancedServo__method__movingValues)
{
    AdvancedServo motor;

    motor.config(P1, 0, 180);
    motor.write(0);

    motor.move(180, 10);

    assertTrue(motor.moving);
    assertFalse(motor.done);
}

test (class_AdvancedServo__method__moveUntilDone)
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

test (class_AdvancedServo__method__moveUntilDoneBackwards)
{
    AdvancedServo motor;
    motor.config(P1, 0, 180);
    motor.write(180);

    assertFalse(motor.moving);

    while (!motor.done)
    {
        assertFalse(motor.done);
        motor.move(0, 10);

        if (motor.done) assertFalse(motor.moving);
        else assertTrue(motor.moving);
    }

    assertTrue(motor.done);
    assertEqual(motor.read(), 0);
    assertEqual(motor.moveId, 1);
}

test (class_AdvancedServo__method__moreMovements)
{
    AdvancedServo motor;

    const i8 SPEED = 5;
    motor.config(P1, 0, 180);

    assertFalse(motor.moving);

    while (true)
    {
        motor.move(motor.is(0), 180, SPEED)
            ->move(motor.is(1),   0, SPEED)
            ->move(motor.is(2), 180, SPEED)
            ->move(motor.is(3),   0, SPEED);

        if (motor.is(4)) break;
    }

    assertTrue(motor.done);
    assertEqual(motor.read(), 0);
    assertEqual(motor.moveId, 4);
}
