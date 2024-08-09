//
// Created by 24106 on 2024/4/5.
//

#include "motor.h"




void motor::front_run() {

    HAL_GPIO_WritePin(GPIOx, GPIO_Pin_1, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin_2, GPIO_PIN_RESET);

}

void motor::back_run() {

    HAL_GPIO_WritePin(GPIOx, GPIO_Pin_1, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin_2, GPIO_PIN_SET);

}

void motor::SetPwm(int input) {

    if (input>0){
        front_run();
    } else if (input<0){
        input = -input;
        back_run();
    }
    if (input==0)
        __HAL_TIM_SetCompare(pwm,Channel,0);
    else
        __HAL_TIM_SetCompare(pwm,Channel,input);

}

void motor::GetPos() {

    last_pos = pos;
    pos = (val?1:-1) * __HAL_TIM_GET_COUNTER(encoder);
    speed = pos - last_pos;
    real += speed;

}

void motor::clear() {

    real = 0;
    pos = 0;
    last_pos = 0;
    speed = 0;
    __HAL_TIM_SET_COUNTER(encoder,0);

}

void motor::Init() {

    HAL_TIM_PWM_Start(pwm,Channel);
    HAL_TIM_Encoder_Start(encoder,TIM_CHANNEL_ALL);
    clear();

}


motor FrontRight (GPIOE,GPIO_PIN_11,GPIO_PIN_10,&htim5,TIM_CHANNEL_2,&htim3,0);

motor FrontLeft   (GPIOE,GPIO_PIN_12,GPIO_PIN_13,&htim5,TIM_CHANNEL_3,&htim4,1);

