//
// Created by W-Mai on 2021/4/10.
//

#ifndef INTELIGENCETRANSPORTROBOT_SENSORS_H
#define INTELIGENCETRANSPORTROBOT_SENSORS_H

#include "Arduino.h"

const int Sensor[6] = {A0, A1, A2, A3, A4, A5};

class Sensors {
private:
    float K[6] = {0.05, 0.05, 0.05, 0.05, 0.05, 0.05};
    uint16_t T[6] = {300, 300, 300, 300, 300, 200};
public:
    float S_O[6] = {300, 300, 300, 300, 300, 300};
    uint16_t S[6] = {300, 300, 300, 300, 300, 300};

    void update_sensor();
};


#endif //INTELIGENCETRANSPORTROBOT_SENSORS_H
