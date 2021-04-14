//
// Created by W-Mai on 2021/4/10.
//

#ifndef INTELIGENCETRANSPORTROBOT_AUTOMOBILE_H
#define INTELIGENCETRANSPORTROBOT_AUTOMOBILE_H

#include "Arduino.h"
#include "SoftPWM.h"

#define ROW_K 1

struct WheelS {
    uint16_t dir_pin;
    bool dir;
};

class Automobile {
private:
    uint8_t MAX_WHEEL;
    uint8_t max_wheel;
    SoftPWM *soft_pwm;
    WheelS **pWheelS;
    uint16_t enable_pin;
public:
    explicit Automobile(uint8_t num, uint16_t enable_pin = 0);

    void add_wheel(uint16_t dir_pin, uint16_t step_pin, bool dir);

    void begin();

    void set_micros(uint32_t(*func)());

    void run(int16_t x, int16_t y, float deg);

    void enable() const;

    void disable() const;

    void commit();
};


#endif //INTELIGENCETRANSPORTROBOT_AUTOMOBILE_H
