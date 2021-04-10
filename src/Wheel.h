//
// Created by W-Mai on 2021/4/10.
//

#ifndef INTELIGENCETRANSPORTROBOT_WHEEL_H
#define INTELIGENCETRANSPORTROBOT_WHEEL_H

#include "Arduino.h"
#include "A4988.h"

#define MOTOR_STEPS 200
#define RPM 240

#define MICRO_STEPS 2

class Wheel {
private:
    uint16_t dir_pin, step_pin;
    bool dir;
    BasicStepperDriver *driver;
public:
    Wheel(uint16_t dir_pin, uint16_t step_pin, bool dir);

    void begin(float rpm = 240, int16_t micro_steps = MICRO_STEPS);

    void set_mission(long steps);

    int32_t next_action();

    void set_rpm(float rpm);

    void run(int32_t speed);
};


#endif //INTELIGENCETRANSPORTROBOT_WHEEL_H
