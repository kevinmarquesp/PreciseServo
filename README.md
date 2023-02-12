# About the project
*Precise Servo* is an Arduino library that was created to help teachers, students
and hobbyists to easily control the speed of servo components, without the need
to manually create an `for` loop to handle that. Pull requests and sugestions
are welcome! ❤️

Features:
+ Control the speed of each movement by setting a delay between each deggree.
+ Set a minimum and maximum value to not force so much the motor.

> **&#9888; WARNING:** if you're in a bigger and complex project that involves handling
multiple task at the same time (such as moving a robot and reading the user inputs
from the keyboard, as an example) that library maybe break your code, because it
uses the `delay()` function.


## How to use it?
Since that library extends the functions of the actual `Servo.h` library, every
thing that you do with `Servo.h` can be done with `PreciseServo.h` at the same
way, but with different names.

Start by importing the library and creating your first `PreciseServo` object:
```cpp
#include <PreciseServo.h>

// it is just like `Servo my_servo;`
PreciseServo my_servo;
```

You can normally attach and detach the object from a pin with `my_servo.attach()`
and `my_servo.detach()`, but one of the killer features of that library is the
option to set the minimum and maximum values with the **`config()`** method:
```cpp
void setup()
{
    my_servo.config(7, 20, 140);
}
```
> It will attach the `my_servo` object to the pin **7** on the board, and set
**20°** to be the minimum and **140°** to be the maximum position. Which means
that even if you say it to be 180 degrees, it will stop at 140.

Again, the `write()` function also works, but to control the speed of each
movement you'll need to use the **`preciseWrite()`** function:
```cpp
void loop()
{
    my_servo.preciseWrite(140, 10);
}
```
> It will make the motor move to the **140°** position, but it will wait 10
milliseconds for each degree.

If it isn't clear enought, the code above is the same thing as:
```cpp
void loop()
{
    for (int i = 20; i <= 140; i++)
    {
        my_servo.write(i);
        delay(10);
    }
}
```
