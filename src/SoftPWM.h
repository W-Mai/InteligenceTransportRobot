//
// Created by W-Mai on 2021/4/11.
//

#ifndef INTELIGENCETRANSPORTROBOT_SOFTPWM_H
#define INTELIGENCETRANSPORTROBOT_SOFTPWM_H

#include "Arduino.h"

struct PWMProfile {
    uint16_t pin;
    uint16_t freq;
    uint16_t duty;
    uint32_t peri;
    uint32_t duty_high;
    uint32_t t0;
    bool enable;
};

class SoftPWM {
private:
    PWMProfile **pwm_profiles;
    uint16_t max_pwm = 0;
    uint16_t MAX_PWM = 0;

    uint32_t (*get_time)();

    void update_profile(uint16_t id);

public:
    explicit SoftPWM(uint16_t max_pwm);

    uint16_t add(uint16_t pin, uint16_t freq, uint16_t duty);

    void enable(uint16_t id);

    void disable(uint16_t id);

    void set_freq(uint16_t id, uint16_t freq);

    void set_duty(uint16_t id, uint16_t duty);

    void set_micros(uint32_t (*func)());

    void commit();
};


#endif //INTELIGENCETRANSPORTROBOT_SOFTPWM_H
