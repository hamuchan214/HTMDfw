#include <Arduino.h>
#include "HTmd.hpp"

void setup()
{
    MOTOR.setEnable(true);
    MOTOR.setBrake(false);
    MOTOR.setDirection(true);
    MOTOR.setPWM(250);
    Serial.begin(115200);
    Serial.println("SS");
}

void loop()
{
    Serial.println(MOTOR.getPWM());
    MOTOR.DriveMotor();
    delay(80);
}