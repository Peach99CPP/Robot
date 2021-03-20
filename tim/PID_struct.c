//
// Created by peachRJ on 2021/1/29.
//

#include "PID_struct.h"
#include "tim_it.h"


struct PID_param line_pid_param, blank = {0, 0, 0, 1, 0, 0, 0};
struct Position_pid_obj Line_PID = {0, 0, 0, 0, 0, 0, 0};
struct Increment_pid_obj motor_1 = {0, 0, 0, 0, 0, Speed}, motor_2 = {0, 0, 0, 0, 0, Speed}, motor_3 = {0, 0, 0, 0, 0,
                                                                                                        0}, motor_4 = {
        0, 0, 0, 0, 0, 0};
struct Speed_struct Motor_speed = {0, 0, 0};
struct PID_param motor_pid_param, Imu_pid_param;

void PID_Init(void) {
    motor_pid_param.outputMax = 7200;
    motor_pid_param.kp = 200;
    motor_pid_param.ki = 40;
    motor_pid_param.kd = 0;
    motor_pid_param.differential_filterK = 1;
    motor_pid_param.actualMax = 200;

    line_pid_param.kp = 2.8;
    line_pid_param.ki = 0;
    line_pid_param.kd = 0.0;
    line_pid_param.outputMax = 50;
    line_pid_param.outputMin = -50;
    line_pid_param.differential_filterK = 1;
}

float positional_PID(struct Position_pid_obj *obj, struct PID_param *pid) {
    float differential = 0;

    obj->bias = obj->target - obj->measure;

    if (obj->output >= pid->outputMax) {
        if (obj->bias < 0)
            obj->integral += obj->bias;
    }
    else if (obj->output <= pid->outputMin) {
        if (obj->bias > 0)
            obj->integral += obj->bias;
    }
    else {
        obj->integral += obj->bias;
    }

    //微分项低通滤波
    differential = (obj->bias - obj->last_bias) * pid->differential_filterK +
                   (1 - pid->differential_filterK) * obj->last_differential;

    obj->output =
            pid->kp * obj->bias + pid->ki * obj->integral + pid->kd * differential;

    obj->last_bias = obj->bias;
    obj->last_differential = differential;

    return obj->output;
}

void Increment_PID_Calculation(struct Increment_pid_obj *motor,
                               struct PID_param *pid) {
    float proportion = 0, integral = 0, differential = 0;

    motor->bias = motor->target - motor->measure;

    proportion = motor->bias - motor->last_bias;

    //抗积分饱和
    if (motor->output > pid->outputMax || motor->measure > pid->actualMax) {
        if (motor->bias < 0)
            integral = motor->bias;
    }
    else if (motor->output < -pid->outputMax ||
             motor->measure < -pid->actualMax) {
        if (motor->bias > 0)
            integral = motor->bias;
    }
    else {
        integral = motor->bias;
    }

    differential = (motor->bias - 2 * motor->last_bias + motor->last2_bias);

    motor->output +=
            pid->kp * proportion + pid->ki * integral + pid->kd * differential;

    motor->last2_bias = motor->last_bias;
    motor->last_bias = motor->bias;
}
