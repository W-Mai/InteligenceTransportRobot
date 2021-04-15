//
// Created by W-Mai on 2021/4/10.
//

#define XDEBUG

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include "MsTimer2.h"
#include "TimerOne.h"
#include "TimerThree.h"
#include "TimerFive.h"

#include "Sensors.h"
#include "Automobile.h"
#include "MachineArmDefines.h"
//#include "XServoList.h"
//#include "ServoTimer2.h"

#define MFL 13, 12
#define MFR 7, 4
#define MBL 6, 3
#define MBR 5, 2

Sensors sensors;
Automobile automobile(4, 8);
MachineArm machine_arm(5);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

XServoList xServoList(5);

int CODE_SERIES[6] = {0, 0, 0, 0, 0, 0};

enum CAR_STATE {
    LEFT, MIDDLE, RIGHT, FULL
};

CAR_STATE carState[2] = {CAR_STATE::MIDDLE, CAR_STATE::MIDDLE};
int CURRENT_DIR = -1; // 0 F, 1 B, 2 L, 3 R
int CURRENT_STAGE = 0;

//ServoTimer2 servos[5] = {ServoTimer2(), ServoTimer2(), ServoTimer2(), ServoTimer2(), ServoTimer2()};

void Automobile_Init();

void MachineArm_Init();

void car_auto_control();

void testdrawstyles();

void get_qrcode();

void refresh_sensors();

void refresh_car_state();

int timer1_counter;

void gogogo();

uint32_t t0 = millis();

SoftPWM softPwm(2);

void mypwm();

void setup() {
    Serial.begin(115200);
    Serial1.begin(19200);
    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;); // Don't proceed, loop forever
    }

    display.clearDisplay();

    Automobile_Init();
    MachineArm_Init();

    automobile.disable();


//    delay(1000);
//    MsTimer2::set(2, mypwm);
//    MsTimer2::start();

//    Timer3.initialize(1000);
//    Timer3.attachInterrupt(refresh_sensors);

    Timer1.initialize(100);
    Timer1.attachInterrupt(gogogo);


    Timer5.initialize(3000);
    Timer5.attachInterrupt(refresh_sensors);


    CURRENT_DIR = -1;
    t0 = millis();

//    softPwm.set_micros(micros);
//    softPwm.add(44, 50, 76);
//
//    Serial.println("START");

//    xServoList.add(44);
//    xServoList.write(0, 165);
//    Serial.println("ADD NEW CONFIG");
    Timer3.initialize(16);

    Timer3.attachInterrupt(mypwm);
//    Serial.println("INTERRUPT");

    machine_arm.commit_mission(AS(ARM_STATUS::INIT), 50);
}

void mypwm() {
    machine_arm.commit();
}

void gogogo() {
//    automobile.commit();

}

int k = 1;
int f = 1;


void open_and_close() {
//    machine_arm.commit_mission(AS(CLAW_OPEN), 50);
//    delay(2000);
//    machine_arm.commit_mission(AS(CLAW_CLOSE), 50);
//    delay(2000);
}

bool flag = false;

void loop2() {
#define SERVO_MIN() (25)  // minimum value in uS for this servo
#define SERVO_MAX() (130)  // maximum value in uS for this servo
    if (millis() - t0 < 2000) {
//        softPwm.set_duty(0, map(145, 0, 270, SERVO_MIN(), SERVO_MAX()));
        xServoList.write(0, 145);
    } else if (millis() - t0 < 4000) {
//        softPwm.set_duty(0, map(165, 0, 270, SERVO_MIN(), SERVO_MAX()));
        xServoList.write(0, 165);

    } else t0 = millis();

}

void loop() {

//    if (millis() - t0 > 50) {
//        if (k == -1 || k == 1) f = -f;
//        k += f;

#if defined(XDEBUG)
    testdrawstyles();      // Draw characters of the default font
#else
    get_qrcode();
#endif
    if (0 <= CURRENT_DIR && CURRENT_DIR <= 3) {
        car_auto_control();
    }
    switch (CURRENT_STAGE) {
        case 0:
            if (millis() - t0 > 7000) {
                t0 = millis();
                CURRENT_STAGE = 1;
            }
            automobile.run(0, 1200, 0);
            break;
        case 1:
            if (millis() - t0 > 2500) {
                t0 = millis();
                CURRENT_STAGE = 2;
                break;
            }
            automobile.run(1200, 0, 0);
            break;
        case 2:
            if (millis() - t0 > 2000) {
                t0 = millis();
                CURRENT_STAGE = 3;
                sensors.reset_count();
            }
            automobile.run(0, 0, 0);
            break;
        case 3:
            flag = sensors.C[3] == 5 || sensors.C[4] == 5 || sensors.C[5] == 5;
            if (millis() - t0 > 23000 || flag) {
                t0 = millis();
                CURRENT_STAGE = 4;
                CURRENT_DIR = -1;
                automobile.run(0, 0, 0);
                break;
            }
            CURRENT_DIR = 0;
            break;
        case 4:
            if (millis() - t0 > 10000) {
                t0 = millis();
                CURRENT_STAGE = 5;
                sensors.reset_count();
            }
            automobile.run(0, 0, 0);
            break;
        case 5:
            if (millis() - t0 > 1000) {
                t0 = millis();
                CURRENT_STAGE = 6;
                sensors.reset_count();
            }
            automobile.run(1200, 0, 0);
            break;
        case 6:
            flag = sensors.C[0] == 3 || sensors.C[1] == 3 || sensors.C[2] == 3;
            if (/*millis() - t0 > 20000 || */flag) {
                t0 = millis();
                CURRENT_STAGE = 7;
                CURRENT_DIR = -1;
                automobile.run(0, 0, 0);
                sensors.reset_count();
                break;
            }
            CURRENT_DIR = 2;
            break;
        case 7:
            if (millis() - t0 > 3000) {
                t0 = millis();
                CURRENT_STAGE = 8;
                automobile.run(0, 0, 0);
            }
            automobile.run(0, 1200, 0);
            break;
        case 8:
            if (millis() - t0 > 3000) {
                t0 = millis();
                CURRENT_STAGE = 9;
                automobile.run(0, 0, 0);
            }
            automobile.run(0, 0, 0);
            break;
        case 9:
            if (millis() - t0 > 3000) {
                t0 = millis();
                CURRENT_STAGE = 10;
                automobile.run(0, 0, 0);
                sensors.reset_count();
            }
            automobile.run(0, -1200, 0);
            break;
        case 10:
            if (millis() - t0 > 1000) {
                t0 = millis();
                CURRENT_STAGE = 11;
                sensors.reset_count();
            }
            automobile.run(1200, 0, 0);
            break;
        case 11:
            flag = sensors.C[0] == 3 || sensors.C[1] == 3 || sensors.C[2] == 3;
            if (/*millis() - t0 > 20000 || */flag) {
                t0 = millis();
                CURRENT_STAGE = 12;
                CURRENT_DIR = -1;
                automobile.run(0, 0, 0);
                sensors.reset_count();
                break;
            }
            CURRENT_DIR = 3;
            break;
    }


}

bool left_timer = millis();

void car_auto_control() {
    if (CURRENT_DIR == 0) {
        switch (carState[0]) {
            case CAR_STATE::LEFT:
                automobile.run(0, 1200, 600);
                break;
            case CAR_STATE::RIGHT:
                automobile.run(0, 1200, -600);
                break;
            case CAR_STATE::MIDDLE:
                automobile.run(0, 1200, 0);
                break;
            case CAR_STATE::FULL:
                automobile.run(0, 1200, 0);
                break;
        }
    } else if (CURRENT_DIR == 1) {
        switch (carState[0]) {
            case CAR_STATE::LEFT:
                automobile.run(600, -1200, 0);
                break;
            case CAR_STATE::RIGHT:
                automobile.run(-600, -1200, -0);
                break;
            case CAR_STATE::MIDDLE:
                automobile.run(0, -1200, 0);
                break;
            case CAR_STATE::FULL:
                automobile.run(0, -1200, 0);
                break;
        }
    } else if (CURRENT_DIR == 2) {
        switch (carState[1]) {
            case CAR_STATE::LEFT:
                automobile.run(1200, -0, 600);
                break;
            case CAR_STATE::RIGHT:
                automobile.run(1200, 0, -600);
                break;
            case CAR_STATE::MIDDLE:
                automobile.run(1200, 0, 0);
                break;
            case CAR_STATE::FULL:
                automobile.run(1200, 0, 0);
                break;
        }
    } else if (CURRENT_DIR == 3) {
        switch (carState[1]) {
            case CAR_STATE::LEFT:
                automobile.run(-1200, -300, 0);
                break;
            case CAR_STATE::RIGHT:
                automobile.run(-1200, 300, -0);
                break;
            case CAR_STATE::MIDDLE:
                automobile.run(-1200, 0, 0);
                break;
            case CAR_STATE::FULL:
                automobile.run(-1200, 0, 0);
                break;
        }
    }
}

void refresh_sensors() {
    //更新传感器数据
    sensors.update_sensor();
    refresh_car_state();
}

void Automobile_Init() {
    automobile.set_micros((uint32_t (*)()) (micros));

    automobile.add_wheel(MFR, false);
    automobile.add_wheel(MFL, true);
    automobile.add_wheel(MBL, true);
    automobile.add_wheel(MBR, false);

    automobile.enable();
    automobile.begin();
}

void MachineArm_Init() {
    machine_arm.set_micros(micros);
    for (int port : ARM_SERVO_PORT) {
        machine_arm.add(port);
    }
    machine_arm.begin(AS(ARM_STATUS::INIT));
//    for (int i = 0; i < 1; ++i) {
////        servos[i].attach(ARM_SERVO_PORT[i]);
//    }
}

void refresh_car_state() {
    if (sensors.S[0] && sensors.S[1] && sensors.S[2]) {
        carState[0] = CAR_STATE::FULL;
    } else {
        if (sensors.S[2] || (sensors.S[1] && sensors.S[2])) {
            carState[0] = CAR_STATE::LEFT;
        } else if (sensors.S[0] || (sensors.S[1] && sensors.S[0])) {
            carState[0] = CAR_STATE::RIGHT;
        } else if (sensors.S[1]) {
            carState[0] = CAR_STATE::MIDDLE;
        }
    }

    if (sensors.S[3] && sensors.S[4] && sensors.S[5]) {
        carState[1] = CAR_STATE::FULL;
    } else {
        if (sensors.S[5] || (sensors.S[4] && sensors.S[5])) {
            carState[1] = CAR_STATE::LEFT;
        } else if (sensors.S[3] || (sensors.S[4] && sensors.S[3])) {
            carState[1] = CAR_STATE::RIGHT;
        } else if (sensors.S[4]) {
            carState[1] = CAR_STATE::MIDDLE;
        }
    }
}


void get_qrcode() {
    display.clearDisplay();
    display.setCursor(2, 2);

    display.setTextSize(3, 8);             // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);

    Serial1.println("qrcode");
    while (Serial1.available()) {
        auto str = Serial1.readStringUntil('\n');
        str = str.substring(0, str.length() - 1);

        sscanf(str.c_str(), "%1d%1d%1d+%1d%1d%1d",
               &CODE_SERIES[0], &CODE_SERIES[1], &CODE_SERIES[2],
               &CODE_SERIES[3], &CODE_SERIES[4], &CODE_SERIES[5]);

        display.println(str);
        display.display();
    }
    Serial1.flush();
    delay(20);
}

void testdrawstyles() {
    display.clearDisplay();
    display.setCursor(2, 2);
//    Serial1.println("color");
//
////    while (Serial1.available()) {
//    auto str = Serial1.readStringUntil('\n');
//    if (str.length() > 3) {
//        str = str.substring(0, str.length() - 1);
//
//        int l, a, b;
//        sscanf(str.c_str(), "%d,%d,%d", &l, &a, &b);
//
//        String s;
//        if (abs(b) < 10) {
//            if (a < -10) s = "G";
//            else if (a > 10) s = "R";
//        } else if (b < -10) s = "B";
//
//        Serial.println(str);
//
//        display.setTextSize(1, 1);             // Draw 2X-scale text
//        display.setTextColor(SSD1306_WHITE);
//        display.println(s);
//        display.println(str);
//    }
//
//    Serial1.flush();
//
//    Serial1.println("qrcode");
//    str = Serial1.readStringUntil('\n');
//    if (str.length() > 2) {
//        str = str.substring(0, str.length() - 1);
//        display.println(str);
//    }
//
////
////    char qrcode_res[20]{0};
//////    sscanf(str.c_str(), , qrcode_res);
//
//    Serial1.flush();
////    }
    display.setTextSize(1, 1);             // Draw 2X-scale text
    display.setTextColor(SSD1306_WHITE);
    display.print(sensors.S_O[0]);
    display.print(",");
    display.print(sensors.S_O[1]);
    display.print(",");
    display.print(sensors.S_O[2]);
    display.println("");
    display.print(sensors.S_O[3]);
    display.print(",");
    display.print(sensors.S_O[4]);
    display.print(",");
    display.print(sensors.S_O[5]);
    display.println("");

    display.print(sensors.S[0]);
    display.print(", ");
    display.print(sensors.S[1]);
    display.print(", ");
    display.print(sensors.S[2]);
    display.print(", ");
    display.print(sensors.S[3]);
    display.print(", ");
    display.print(sensors.S[4]);
    display.print(", ");
    display.print(sensors.S[5]);
    display.print("\n");

    display.display();
//    delay(20);
}