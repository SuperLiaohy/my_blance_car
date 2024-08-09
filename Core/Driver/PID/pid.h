
#ifndef ANGLE_PID_H
#define ANGLE_PID_H

#include "motor.h"

class pid{
private:
    bool clean;

    float PItem;
    float IItem;
    float DItem;

    float LastPItem;
public:

    float p;
    float i;
    float d;

    pid(float mp=0,float mi=0,float md=0):p(mp),i(mi),d(md){}

    void clear();

    float Update(float now,float target);

    float Update(float left,float right,float target);

    float PosPid(motor MOTOR,float target);
    float AddPid(motor MOTOR,float target);

    float SpeedPid(motor MOTOR,float target);
};

float limit(float min,float &m,float max);
extern pid angle;
extern pid speed;



#endif //ANGLE_PID_H
