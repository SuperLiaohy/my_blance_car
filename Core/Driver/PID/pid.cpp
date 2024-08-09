//
// Created by 24106 on 2024/4/5.
//

#include "pid.h"

float limit(float min,float &m,float max){
    if (min>m){
        m = min;
    } else if (max<m){
        m = max;
    }
    return m;
}

void pid::clear() {
    clean = true;
    PItem = 0;
    IItem = 0;
    DItem = 0;
}

float pid::PosPid(motor MOTOR, float target) {

    PItem = target - MOTOR.real;
    IItem += PItem;
    DItem = MOTOR.real - MOTOR.last_pos;

    return p * PItem + i * IItem + d * DItem;
}

float pid::AddPid(motor MOTOR, float target) {
    static float PreErr = 0;
    static float LastErr = 0;
    static float Err = 0;
    if (clean){
        PreErr = 0;
        LastErr = 0;
        Err = 0;
        clean = false;
    }
/*
 * limit speed
 * can't too small
 * else
 * Turn left and right
 */
    limit(-25,target,25);

    PreErr = LastErr;
    LastErr = Err;
    Err = target - MOTOR.speed;

    limit(-10000,Err,10000);

    PItem = Err - LastErr;
    IItem = Err;
    DItem = Err - 2 * LastErr + PreErr;

    return p * PItem + i * IItem + d * DItem;
}

float pid::SpeedPid(motor MOTOR, float target) {

    LastPItem = PItem;
    PItem = target - MOTOR.speed;
    IItem += PItem;
    DItem = PItem - LastPItem;

    return p * PItem + i * IItem + d * DItem;

}

float pid::Update(float now, float target) {

    LastPItem = PItem;
    PItem = target - now;
//    if (PItem<3||PItem>-3){
//        IItem = 0;
//    }
    IItem += PItem;
    DItem = PItem - LastPItem;
    float a = p * PItem + i * IItem + d * DItem;
    return a;

}

float pid::Update(float left, float right, float target) {
    LastPItem = PItem;
    PItem = target - (left + right);
    IItem += PItem;
//    limit(-500000,IItem,500000);
    DItem = PItem - LastPItem;
    float a = p * PItem + i * IItem + d * DItem;
    return limit(-1000,a,1000);
}

//pid angle(0,0,0);
pid angle(137 * 0.55,0,5 * 0.55);
pid speed(-0.48,-0.48 / 200.f,0);
