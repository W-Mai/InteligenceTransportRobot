//
// Created by W-Mai on 2021/4/15.
//

#include "XServoList.h"

XServoList::XServoList(uint16_t num) : MAX_SERVO(num) {
    soft_pwm = new SoftPWM(num);
    max_servo = 0;
}

int XServoList::add(uint16_t pin) {
    if (max_servo == MAX_SERVO) return -1;
    max_servo++;
    return soft_pwm->add(pin, 50, GET_DUTY(135));
}


void XServoList::set_micros(uint32_t (*func)()) {
    soft_pwm->set_micros(func);
}
