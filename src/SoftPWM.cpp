//
// Created by W-Mai on 2021/4/11.
//

#include "SoftPWM.h"

SoftPWM::SoftPWM(uint16_t max_pwm) : MAX_PWM(max_pwm) {
    pwm_profiles = (PWMProfile **) new PWMProfile *[MAX_PWM];
    max_pwm = 0;
    get_time = nullptr;
}

void SoftPWM::update_profile(uint16_t id) {
    uint16_t freq = pwm_profiles[id]->freq;
    if (freq <= 0) {
        pwm_profiles[id]->duty_high = 0;
        return;
    }
    pwm_profiles[id]->peri = 1000000 / freq;
    pwm_profiles[id]->duty_high =
            static_cast<uint32_t>(1.0 * pwm_profiles[id]->duty * pwm_profiles[id]->peri / 1024.0);
}

void SoftPWM::enable(uint16_t id) {
    pwm_profiles[id]->enable = true;
    pinMode(pwm_profiles[id]->pin, OUTPUT);
}

void SoftPWM::disable(uint16_t id) {
    pwm_profiles[id]->enable = false;
}

void SoftPWM::set_freq(uint16_t id, uint16_t freq) {
    pwm_profiles[id]->freq = freq;
    update_profile(id);
}

void SoftPWM::set_duty(uint16_t id, uint16_t duty) {
    pwm_profiles[id]->duty = duty;
    update_profile(id);
}

void SoftPWM::set_micros(uint32_t (*func)()) {
    get_time = func;
}

uint16_t SoftPWM::add(uint16_t pin, uint16_t freq, uint16_t duty) {
    if (max_pwm == MAX_PWM) return -1;
    pwm_profiles[max_pwm] = new PWMProfile;
    pwm_profiles[max_pwm]->pin = pin;
    pwm_profiles[max_pwm]->freq = freq;
    pwm_profiles[max_pwm]->duty = duty;
    pwm_profiles[max_pwm]->t0 = get_time();
    update_profile(max_pwm);
    enable(max_pwm);
    return max_pwm++;
}

void SoftPWM::commit() {
    for (uint16_t id = 0; id < max_pwm; ++id) {
        if (!pwm_profiles[id]->enable) continue;
        uint32_t tmp_t = get_time() - pwm_profiles[id]->t0;
        digitalWrite(pwm_profiles[id]->pin, tmp_t > pwm_profiles[id]->duty_high ? LOW : HIGH);
        if (tmp_t > pwm_profiles[id]->peri) pwm_profiles[id]->t0 = get_time();
    }
}
