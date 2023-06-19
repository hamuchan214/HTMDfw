#include <Arduino.h>
#include "HTmd.hpp"

void setup()
{
    MOTOR.setEnable(true);
    MOTOR.setBrake(false);
    MOTOR.setDirection(true);
    MOTOR.setPWM(50);
}

void loop()
{
    MOTOR.DriveMotor();
    delay(3);
}