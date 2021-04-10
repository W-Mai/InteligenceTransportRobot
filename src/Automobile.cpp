//
// Created by W-Mai on 2021/4/10.
//

#include "Automobile.h"

Automobile::Automobile(uint8_t num) : MAX_WHEEL(num) {
    wheels = (Wheel **) new Wheel *[num];
    max_wheel = 0;
}

void Automobile::add_wheel(uint16_t dir_pin, uint16_t step_pin, bool dir) {
    if (max_wheel == MAX_WHEEL) return;
    wheels[max_wheel++] = new Wheel(dir_pin, step_pin, dir);
}

void Automobile::run(int16_t x, int16_t y, float deg) {
    wheels[0]->run(y - x + static_cast<int32_t>(ROW_K * deg));
    wheels[1]->run(y + x - static_cast<int32_t>(ROW_K * deg));
    wheels[2]->run(y - x - static_cast<int32_t>(ROW_K * deg));
    wheels[3]->run(y + x + static_cast<int32_t>(ROW_K * deg));
}

void Automobile::begin() {
    for (int i = 0; i < max_wheel; ++i) {
        wheels[i]->begin();
    }
}
