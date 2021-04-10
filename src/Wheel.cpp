//
// Created by W-Mai on 2021/4/10.
//

#include "Wheel.h"


Wheel::Wheel(uint16_t dir_pin, uint16_t step_pin, bool dir) : dir_pin(dir_pin), step_pin(step_pin), dir(dir) {
    driver = new BasicStepperDriver(MOTOR_STEPS, dir_pin, step_pin);
//    driver->disable();
}

void Wheel::begin(float rpm, int16_t micro_steps) {
    driver->begin(rpm, micro_steps);
}

void Wheel::set_mission(long steps) {
    driver->startMove(dir ? steps : -steps);
}

int32_t Wheel::next_action() {
    return driver->nextAction();
}

void Wheel::set_rpm(float rpm) {
    driver->setRPM(rpm);
}

void Wheel::run(int32_t speed) {
    set_rpm(abs(speed));
    set_mission(2000 * (speed > 0 ? 1 : -1));
    for (int i = 0; i < 100; ++i) {
        next_action();
    }
//    driver->move(10);
//    if (!next_action()) {
//        while (next_action());
//
//        //set_mission(100000);
//    } else{
//        set_mission(speed*2);
//    }
}
