//
// Created by W-Mai on 2021/4/15.
//

#ifndef INTELIGENCETRANSPORTROBOT_XSERVOLIST_H
#define INTELIGENCETRANSPORTROBOT_XSERVOLIST_H

#include "SoftPWM.h"

#define SERVO_MIN() (25)  // minimum value in uS for this servo
#define SERVO_MAX() (130)  // maximum value in uS for this servo

#define GET_DUTY(DEG) (uint32_t)map((DEG), 0, 270, SERVO_MIN(), SERVO_MAX())

class XServoList {
private:
    SoftPWM *soft_pwm;
    uint16_t MAX_SERVO;
    uint16_t max_servo;
public:
    explicit XServoList(uint16_t num);

    int add(uint16_t pin);

    inline void write(uint16_t id, uint16_t deg) { soft_pwm->set_duty(id, GET_DUTY(deg)); }

    void set_micros(uint32_t (*func)());

    inline int commit() {
        soft_pwm->commit();
    }
};


#endif //INTELIGENCETRANSPORTROBOT_XSERVOLIST_H
