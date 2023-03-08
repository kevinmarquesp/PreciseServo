#include <AUnitVerbose.h>
#include <PreciseServo.h>
#include "test_PreciseServo.h"
#include "test_AdvancedServo.h"

using namespace aunit;

void setup(void)
{
    Serial.begin(115200);
    while (!Serial);
}

void loop(void)
{
    TestRunner::run();
}
