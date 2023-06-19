/**
 * @file   HTmd.hpp
 * @brief  c++ header file to run HTmd.
 *
 *
 * @author  Haruto Tanaka
 * @date    2023/06/19
 */


#ifndef HTmd_hpp
#define HTmd_hpp
#include <Arduino.h>

// define pins(Do not change here)
const int PinPWM = 12;
const int PinDirection = 2;
const int PinBrake = 15;
const int PinDisable = 2;
const int CANTX = 19;
const int CANRX = 23;

// class for motor
class motor
{
private:
    uint8_t PWM_ = 0; // Range:0~255
    uint8_t PWM_buf_ = 0;
    bool direction_ = true;        // true = Go Forward,      false = Go Backwards
    bool is_enable_brake_ = true;  // true = Brake available, false = No Brake
    bool is_enable_motor_ = false; // true = Motor enable,    false = Motor disable
    const int PWM_max_ = 254;
    const int PWM_min_ = 0;
    int pin_PWM_;
    int pin_direction_;
    int pin_brake_;
    int pin_disable_;
    int channel_ = 1;

public:
    // constructor
    motor(int PinPWM, int PinDirection, int PinBrake, int PinDisable, int channel)
    {
        pin_PWM_ = PinPWM;
        pin_direction_ = PinDirection;
        pin_brake_ = PinBrake;
        pin_disable_ = PinDisable;
        channel_ = channel;
        // setup the pins
        ledcSetup(channel_, 312500, 8); // 312500 Hz, 8 bits
        ledcAttachPin(pin_PWM_, channel_);
    }

    // setter
    void setPWM(uint8_t pwm)
    {
        PWM_buf_ = pwm;
    }
    void setDirection(bool dir)
    {
        direction_ = dir;
    }
    void setBrake(bool brake)
    {
        is_enable_brake_ = brake;
    }
    void setEnable(bool en)
    {
        is_enable_motor_ = en;
    }

    void DriveMotor()
    {
        if (is_enable_motor_)
        {
            digitalWrite(pin_disable_, LOW);
            if (is_enable_brake_)
            {
                digitalWrite(pin_brake_, HIGH);
            }
            else
            {
                digitalWrite(pin_brake_, LOW);
                ledcWrite(channel_, PWM_);
                if (PWM_buf_ > PWM_)
                {
                    PWM_++;
                }
                else if (PWM_buf_ < PWM_)
                {
                    PWM_--;
                }
            }
        }
        else
        {
            digitalWrite(pin_disable_, HIGH);
        }
    }
};

motor MOTOR(PinPWM, PinDirection, PinBrake, PinDisable, 0);

#endif
