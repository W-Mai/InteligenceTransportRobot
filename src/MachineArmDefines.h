//
// Created by W-Mai on 2021/4/14.
//

#ifndef INTELIGENCETRANSPORTROBOT_MACHINEARMDEFINES_H
#define INTELIGENCETRANSPORTROBOT_MACHINEARMDEFINES_H

//#include "MachineArm.h"
#define NM (-3)
#define AS(X) ARM_STATUS_ARRAY[(X)]

int ARM_SERVO_PORT[]{44, 45, 46, 9, 10};

enum ARM_STATUS {
    INIT = 0,
    SCAN,
    DRAWLUP,//上边的状态
    DRAWL,//抓取左边第一个
    DRAWMUP,//上边的状态
    DRAWM,//抓取中间的
    DRAWRUP,//上边的状态
    DRAWR,//抓取右边第一个
    MOVEING,//移动过程中状态

    //前面放置
    PLACEMUP,//
    PLACEM,//中间放置
    PLACERUP,
    PLACER,//前右边放置
    PLACELUP,
    PLACEL,//前左边放置

    //左边台阶放置
    PLACELMUP,
    PLACELM,
    PLACELLUP,
    PLACELL,
    PLACELRUP,
    PLACELR,

    //左下边放置
    PLACELDMUP,//PLACE LEFT DOWN MIDDLE UP
    PLACELDM,
    PLACELDLUP,//PLACE LEFT DOWN LEFT UP
    PLACELDL,
    PLACELDRUP,//PLACE LEFT DOWN RIGHT UP
    PLACELDR,

    CLAW_OPEN,
    CLAW_CLOSE
};

int16_t ARM_STATUS_ARRAY[][5] = {
        {145,  30,  0,  35,  145}, // INIT
        {NM, 100, 5,  70,  45}, // SCAN  识别二维码

        {145, 110, 60, 90,  80},//DRAWLup抓取上边的状态
        {NM, 85,  3,  80,  80},//DRAWL抓取左边第一个

        {145, 90,  0,  60,  45},//DRAWMup上边的状态
        {NM, 107, 0,  65,  45},//DRAWM抓取中间

        {145, 90,  15, 75,  12}, // 上边的状态
        {NM, 70,  3,  87,  12},//DRAWR抓取右边第一个

        {0,  30,  0,  35,  145},//移动过程中状态

        {NM, 55,  40, 120, 147},//PLACEMUP
        {NM, 35,  40, 165, 145},//PLACEM放置中间

        {NM, 30,  40, 120, 115},
        {NM, 46,  52, 165, 115},//qian右边放置

        {NM, 30,  40, 120, 172},
        {NM, 50,  55, 165, 172},

        //PLACEL
        {NM, 22,  22, 22,  240},
        {NM, 22,  22, 22,  240},

        {NM, 22,  22, 22,  240},
        {NM, 22,  22, 22,  240},

        {NM, 22,  22, 22,  240},
        {NM, 22,  22, 22,  240},

        //PLACELD    PLACE LEFT DOWN RIGHT UP
        {NM, 22,  22, 22,  240},
        {NM, 22,  22, 22,  240},

        {NM, 22,  22, 22,  240},
        {NM, 22,  22, 22,  240},

        {NM, 22,  22, 22,  240},
        {NM, 22,  22, 22,  240},


        {145, NM, NM, NM, NM},//CLAW张开状态
        {185,  NM, NM, NM, NM},//CLAW紧闭状态
};

#endif //INTELIGENCETRANSPORTROBOT_MACHINEARMDEFINES_H
