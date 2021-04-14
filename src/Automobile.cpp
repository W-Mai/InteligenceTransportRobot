//
// Created by W-Mai on 2021/4/10.
//

#include "Automobile.h"

Automobile::Automobile(uint8_t num, uint16_t enable_pin) : MAX_WHEEL(num), enable_pin(enable_pin) {
    soft_pwm = new SoftPWM(num);
    pWheelS = (WheelS **) new WheelS *[num];
    max_wheel = 0;
    pinMode(enable_pin, OUTPUT);
}

void Automobile::add_wheel(uint16_t dir_pin, uint16_t step_pin, bool dir) {
    if (max_wheel == MAX_WHEEL) return;
    soft_pwm->add(step_pin, 0, 512);
    pWheelS[max_wheel++] = new WheelS{dir_pin, dir};
}

void Automobile::run(int16_t x, int16_t y, float deg) {
    int32_t speed[4]{y - x + static_cast<int32_t>(ROW_K * deg), y + x - static_cast<int32_t>(ROW_K * deg),
                     y - x - static_cast<int32_t>(ROW_K * deg), y + x + static_cast<int32_t>(ROW_K * deg)};
    for (int i = 0; i < max_wheel; ++i) {
        soft_pwm->set_freq(i, abs(speed[i]));
        digitalWrite(pWheelS[i]->dir_pin, pWheelS[i]->dir ^ (speed[i] > 0));
    }
}

void Automobile::begin() {
    for (int i = 0; i < max_wheel; ++i) {
        pinMode(pWheelS[i]->dir_pin, OUTPUT);
        soft_pwm->enable(i);
    }
}

void Automobile::set_micros(uint32_t (*func)()) {
    soft_pwm->set_micros(func);

}

void Automobile::enable() const {
    if (!enable_pin)return;
    digitalWrite(enable_pin, LOW);
}

void Automobile::disable() const {
    if (!enable_pin)return;
    digitalWrite(enable_pin, HIGH);
}

void Automobile::commit() {
    soft_pwm->commit();
}
