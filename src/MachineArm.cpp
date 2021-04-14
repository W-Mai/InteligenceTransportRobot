//
// Created by W-Mai on 2021/4/11.
//

#include "MachineArm.h"

MachineArm::MachineArm(uint16_t num) : MAX_ARM(num) {
    servos = (Servo **) new Servo *[num];
    ARM_CURRENT_DEG = new int[num];
    max_arm = 0;
}

int16_t MachineArm::add(uint16_t pin) {
    if (max_arm == MAX_ARM) return -1;
    servos[max_arm] = new Servo;
    servos[max_arm]->attach(pin);
    return max_arm++;
}

void MachineArm::begin(const int16_t *target) {
    for (uint16_t i = 0; i < max_arm; ++i) {
        ARM_CURRENT_DEG[i] = target[i];
    }
}

void MachineArm::commit_mission(int16_t *target, uint16_t time) {
    int slice_count = 15;
    float current_arm_target[MAX_ARMS]{0};
    float servo_slice_step[MAX_ARMS]{0};
    for (uint16_t i = 0; i < max_arm; ++i) {
        if (target[i] == NM) continue;
        current_arm_target[i] = static_cast<float>(ARM_CURRENT_DEG[i]);
        servo_slice_step[i] = ((float) target[i] - current_arm_target[i]) / (float) slice_count;
    }

    for (auto i = 0; i < slice_count; ++i) {
        if (target[i] == NM) continue;
        delay(time);
        servos[i]->write(static_cast<int>(current_arm_target[i]));
        current_arm_target[i] += servo_slice_step[i];
    }

    for (uint16_t i = 0; i < max_arm; ++i) {
        if (target[i] == NM) continue;
        delay(time);
        servos[i]->write(target[i]);
        ARM_CURRENT_DEG[i] = target[i];
    }
}
