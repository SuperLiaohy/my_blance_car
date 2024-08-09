//
// Created by lhy on 2024/7/25.
//
#ifdef __cplusplus
extern "C" {
#endif

#include "tim.h"
#include "MPU6050.h"


#ifdef __cplusplus
}
#endif

#include "pid.h"
#include "motor.h"

extern float pitch, roll, yaw;
int time=0;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance == TIM6) {
        static int cnt;
        if (cnt++ % 10 == 0) {
            FrontLeft.GetPos();
            FrontRight.GetPos();
        }



//        float a = speed.SpeedPid(FrontLeft,angle.Update(roll, 0));

        float a=0;
        a = angle.Update(roll, 0);
        a += speed.Update(FrontRight.speed,FrontLeft.speed, 0);
        limit(-1000,a,1000);
        FrontLeft.SetPwm(a);
        FrontRight.SetPwm(a);
    }
}