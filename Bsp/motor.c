//
// Created by peachRJ on 2021/1/29.
//
#include "motor.h"
#include "PID_struct.h"
#include "main.h"

extern TIM_HandleTypeDef htim1, htim8;

void PWM_Enable(void) {
    //enable the channels of pwm (定时器1和定时器8）
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_4);
}

short read_num(int flag) {
    short num;
    switch (num) {
        case 1:num = -(short) TIM2->CNT;
            TIM2->CNT = 0;
            break;
        case 2:num = (short) TIM3->CNT;
            TIM3->CNT = 0;
            break;
        case 3:num = (short) TIM4->CNT;
            TIM4->CNT = 0;
            break;
        case 4:num = -(short) TIM5->CNT;
            TIM5->CNT = 0;
            break;
    }
    return num;
}

void get_num(void) {
    motor_1.measure = read_num(1);
    motor_2.measure = read_num(2);
    motor_3.measure = read_num(3);
    motor_4.measure = read_num(4);
}

void set_PWM(int flag, int output) {
    if (output > 0) {//向前
        switch (flag) {
            case 1:TIM1->CCR1 = 0;
                TIM1->CCR2 = output;
                break;
            case 2: TIM1->CCR3 = output;
                TIM1->CCR4 = 0;
                break;
            case 3 :TIM8->CCR1 = output;
                TIM8->CCR2 = 0;
                break;
            case 4:TIM8->CCR3 = 0;
                TIM8->CCR4 = output;
                break;
            default:;
        }
    }
    else {
        output=-output;
        switch (flag) {
            case 1:TIM1->CCR1 = output;
                TIM1->CCR2 = 0;
                break;
            case 2: TIM1->CCR3 = 0;
                TIM1->CCR4 = output;
                break;
            case 3 :TIM8->CCR1 = 0;
                TIM8->CCR2 = output;
                break;
            case 4:TIM8->CCR3 = output;
                TIM8->CCR4 = 0;
                break;
            default:;
        }
    }

}


void Target_Speed(void) {
    Increment_PID_Calculation(&motor_1, &motor_pid_param);
    Increment_PID_Calculation(&motor_2, &motor_pid_param);
    Increment_PID_Calculation(&motor_3, &motor_pid_param);
    Increment_PID_Calculation(&motor_4, &motor_pid_param);
    set_PWM(1, motor_1.output);
    set_PWM(2, motor_2.output);
    set_PWM(3, motor_3.output);
    set_PWM(4, motor_4.output);
}
