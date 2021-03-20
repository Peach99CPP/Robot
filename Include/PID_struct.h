//
// Created by peachRJ on 2021/1/29.
//

#ifndef GDUT_ROBOT_PID_STRUCT_H
#define GDUT_ROBOT_PID_STRUCT_H

void PID_Init(void);

struct Speed_struct {
    int V_x, V_y, V_w;//顺时针为正方向
};

struct Increment_pid_obj {
    float output;
    int bias;
    int last_bias;
    int last2_bias;
    int measure;
    int target;
};

struct Position_pid_obj {
    float output;
    float bias;
    float measure;
    float last_bias;
    float integral;
    float last_differential;
    float target;
};
struct PID_param {
    float kp;
    float ki;
    float kd;
    float differential_filterK;
    float outputMin;
    float outputMax;
    float actualMax;
};
extern struct Increment_pid_obj motor_2, motor_1, motor_3, motor_4;
extern struct Position_pid_obj line_PID;
extern struct PID_param motor_pid_param, line_pid_param;
extern struct Speed_struct Motor_speed;

void Position_PID_Calculation(struct Position_pid_obj *PidObj, struct PID_param *param);

void Increment_PID_Calculation(struct Increment_pid_obj *motor, struct PID_param *param);

#endif //GDUT_ROBOT_PID_STRUCT_H
