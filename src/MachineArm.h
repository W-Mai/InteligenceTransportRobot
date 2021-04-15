//
// Created by W-Mai on 2021/4/11.
//

#ifndef INTELIGENCETRANSPORTROBOT_MACHINEARM_H
#define INTELIGENCETRANSPORTROBOT_MACHINEARM_H

#include "Arduino.h"
#include "XServoList.h"

#define MAX_ARMS 10
#define NM (-3)

class MachineArm {
private:
    uint16_t MAX_ARM;
    uint16_t max_arm;

    XServoList *xServoList;
    int *ARM_CURRENT_DEG;
public:
    explicit MachineArm(uint16_t num);

    int16_t add(uint16_t pin);

    void begin(const int16_t *target);

    void commit_mission(int16_t *target, uint16_t time = 50);

    void set_micros(uint32_t (*func)()) {
        xServoList->set_micros(func);
    }

    inline void commit() {
        xServoList->commit();
    }
};


#endif //INTELIGENCETRANSPORTROBOT_MACHINEARM_H
