#define PIN1 5
#define PIN2 6
#define PIN3 7

test(clsAdvancedServo, checkDefaultValues)
{
    AdvancedServo motor1;
    AdvancedServo motor2;

    motor1.config(PIN1, 90, 180);
    motor2.config(PIN2,  0,  90);

    assertTrue(motor1.is(0));
    assertFalse(motor1.isDone());
    assertFalse(motor1.isDone(1));

    assertTrue(motor2.is(0));
    assertFalse(motor2.isDone());
    assertFalse(motor1.isDone(1));

    motor1.detach();
    motor2.detach();
}

test(clsAdvancedServo, singleMovement)
{
    const uint8_t bSpeed = 10;
    AdvancedServo motor;

    motor.config(PIN1, 0, 180);
    assertEqual(motor.read(), 0);

    while (true)
    {
        motor.move(180, bSpeed);
        
        if (motor.isDone(1))
            break;
    }

    assertTrue(motor.is(1));
    motor.detach();
}

test(clsAdvancedServo, multipleMovements)
{
    const uint8_t bSpeed = 10;
    AdvancedServo motor;

    AdvancedServo top;
    AdvancedServo mid;
    AdvancedServo btm;

    top.config(PIN1, 0, 180);
    mid.config(PIN2, 0, 180);
    btm.config(PIN3, 0, 180);

    while (true)
    {
        top.move(180, bSpeed/5)
            ->move(top.is(1), 0, bSpeed);

        mid.move(mid.is(0), 180, bSpeed/2)
            ->move(mid.is(1), 0, bSpeed/2);

        btm.move(btm.is(0), 180, bSpeed)
            ->move(btm.is(1), 0, bSpeed/5);

        if (top.isDone(2) && mid.isDone(2) && btm.isDone(2))
            break;
    }

    assertTrue(top.is(2));
    assertTrue(mid.is(2));
    assertTrue(btm.is(2));

    assertEqual(top.read(), top.getMin());
    assertEqual(mid.read(), mid.getMin());
    assertEqual(btm.read(), btm.getMin());

    top.detach();
    mid.detach();
    btm.detach();
}
