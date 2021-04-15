//
// Created by W-Mai on 2021/4/10.
//

#include "Sensors.h"

void Sensors::update_sensor() {
    for (int i = 0; i < 6; ++i) {
        auto t = static_cast<float>(analogRead(Sensor[i]));
        S_O[i] = (1 - K[i]) * S_O[i] + K[i] * t;
        S[i] = S_O[i] > static_cast<float>(T[i]);

        if (S[i]) is_pushed[i] = true;
        if (!S[i] && is_pushed[i]) {
            is_pushed[i] = false;
            C[i]++;
        }
    }
}

void Sensors::reset_count() {
    for (auto &x : C)x = 0;
}
