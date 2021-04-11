//
// Created by W-Mai on 2021/4/10.
//

#include <Arduino.h>

#include "Sensors.h"
#include "Automobile.h"
#include "SoftPWM.h"

#define MOTOR_STEPS 200
#define RPM 240

#define MICRO_STEPS 2

#define MFL 13, 12
#define MFR 7, 4
#define MBL 6, 3
#define MBR 5, 2

Sensors sensors;
//SoftPWM soft_pwm(4);
Automobile automobile(4);

//Wheel wheel(MFR, true);

void pwm_out(uint8_t pin, uint16_t freq, uint16_t duty);

void Automobile_Init();

void setup() {
    Serial.begin(115200);
    pinMode(8, OUTPUT);
    digitalWrite(8, LOW);

    Automobile_Init();
//wheel.begin();
}


int k = 1;
int f = 1;
uint32_t t0 = millis();

void loop() {
    if (millis() - t0 > 200) {
        if (k == -1 || k == 1) f = -f;
        k += f;

        t0 = millis();
    }
    automobile.run(0, 600, 100*k);
}

void Automobile_Init() {
    automobile.set_micros(micros);

    automobile.add_wheel(MFR, false);
    automobile.add_wheel(MFL, true);
    automobile.add_wheel(MBL, true);
    automobile.add_wheel(MBR, false);

    automobile.begin();
}

void pwm_out(uint8_t pin, uint16_t freq, uint16_t duty) { // duty: 0~1023
    static uint32_t t0;

    uint32_t tmp_periodical = 1000000 / freq;
    uint32_t duty_high = duty * tmp_periodical / 1024;

    if (micros() - t0 > duty_high) digitalWrite(pin, LOW);
    else digitalWrite(pin, HIGH);

    if (micros() - t0 > tmp_periodical) t0 = micros();
}
//sensors.update_sensor();
//
//Serial.print(sensors.S_O[0]);
//Serial.print(", ");
//Serial.print(sensors.S_O[1]);
//Serial.print(", ");
//Serial.print(sensors.S_O[2]);
//Serial.print(", ");
//Serial.print(sensors.S_O[3]);
//Serial.print(", ");
//Serial.print(sensors.S_O[4]);
//Serial.print(", ");
//Serial.print(sensors.S_O[5]);
//Serial.print("\n");