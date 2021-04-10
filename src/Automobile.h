//
// Created by W-Mai on 2021/4/10.
//

#ifndef INTELIGENCETRANSPORTROBOT_AUTOMOBILE_H
#define INTELIGENCETRANSPORTROBOT_AUTOMOBILE_H

#include "Arduino.h"
#include "Wheel.h"

#define ROW_K 10

class Automobile {
private:
    uint8_t MAX_WHEEL;
    uint8_t max_wheel;
    Wheel **wheels;
public:
    explicit Automobile(uint8_t num);

    void add_wheel(uint16_t dir_pin, uint16_t step_pin, bool dir);

    void begin();

    void run(int16_t x, int16_t y, float deg);
};


#endif //INTELIGENCETRANSPORTROBOT_AUTOMOBILE_H
