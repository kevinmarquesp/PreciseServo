test(class_AdvancedServo__method__StandardMoving)
{
    AdvancedServo motor;

    motor.config(P1, 0, 180);
    motor.ready = true;

    assertTrue(motor.ready);
    motor.move(180, 10);

    assertTrue(motor.moving);
    assertFalse(motor.finished);
}
