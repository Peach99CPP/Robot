//
// Created by peachRJ on 2021/2/7.
//
#include "move_control.h"
#include <stdlib.h>
#include<PID_struct.h>

int now_x, now_y;


void Position_Init(void) {
    now_x = now_y = 0;
}

void Direct_Move(int target_x, int target_y)//应该再加一个角度环来稳定行进角度，确保在行进过程中角度对准
{
    float target_angle;
    //如何确定已经走到了对应的位置？计算圈数×轮周长？误差解决？
    x_speed = abs(target_x - now_x) * 5;
    y_speed = abs(target_y - now_y) * 5;
    if (now_x > target_x)//180度角
    {
        target_angle = 180;
        if (now_y > target_y);//右移
        else;
    }
    else //0度角
    {
        target_angle = 0;
        if (now_y > target_y);//左移
        else;
    }

}


float angle_to_radian = 0.01745f; //角度转弧度

double mx_sin(double rad) {
    double sine;
    if (rad < 0)
        sine = rad * (1.27323954f + 0.405284735f * rad);
    else
        sine = rad * (1.27323954f - 0.405284735f * rad);
    if (sine < 0)
        sine = sine * (-0.225f * (sine + 1) + 1);
    else
        sine = sine * (0.225f * (sine - 1) + 1);
    return sine;
}

double my_sin(double rad) {
    int flag = 1;

    while (rad > 2 * ONE_PI) {
        rad = rad - 2 * ONE_PI;
    }
    if (rad >= ONE_PI) {
        rad -= ONE_PI;
        flag = -1;
    }

    return mx_sin(rad) * flag;
}

double my_cos(double rad) {
    int flag = 1;
    rad += ONE_PI / 2.0;
    while (rad > 2 * ONE_PI) {
        rad = rad - 2 * ONE_PI;
    }
    if (rad >= ONE_PI) {
        flag = -1;
        rad -= ONE_PI;
    }
    return my_sin(rad) * flag;
}

void speed_communication(unsigned short int motor_mode) {
    float a, b, c, ang_motion = 0;
    unsigned short int moto_num, motor_num, axis_num;

    switch (motor_mode) {
        //三轮全向轮
        case 1:a = (60 + ang_motion) * angle_to_radian;
            b = (60 - ang_motion) * angle_to_radian;
            c = (a - b) * 0.5f; //c = (0 + ang_motion)*angle_to_radian;
            motor_num = 3;
            break;
            //四轮全向轮
        case 2:a = (60 + ang_motion) * angle_to_radian;
            b = (60 - ang_motion) * angle_to_radian;
            c = (a - b) * 0.5f; //c = (0 + ang_motion)*angle_to_radian;
            motor_num = 4;
            break;
            //四轮麦轮
        case 3:a = (45 - ang_motion) * angle_to_radian;
            b = (45 + ang_motion) * angle_to_radian;
            c = a;
            motor_num = 4;
            break;
    }
    //合成公式
    motor_1.target = +my_cos(a) * Motor_speed.V_x + my_sin(a) * Motor_speed.V_y - Motor_speed.V_w; //1******2
    motor_2.target = +my_cos(b) * Motor_speed.V_x - my_sin(b) * Motor_speed.V_y - Motor_speed.V_w; //********
    motor_3.target = -my_cos(c) * Motor_speed.V_x - my_sin(c) * Motor_speed.V_y - Motor_speed.V_w; //********
    motor_4.target = -my_cos(b) * Motor_speed.V_x + my_sin(b) * Motor_speed.V_y - Motor_speed.V_w; //4******3
}

void Speed_set(int vx, int vy, int vw) {
    Motor_speed.V_x = vx;
    Motor_speed.V_y = vy;
    Motor_speed.V_w = vw;
    speed_communication(3);
}

void motor_stop(void) {
    Speed_set(0, 0, 0);
}
