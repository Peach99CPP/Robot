//
// Created by peachRJ on 2021/2/7.
//

#ifndef GDUT_ROBOT_MOVE_CONTROL_H
#define GDUT_ROBOT_MOVE_CONTROL_H
#include "main.h"
#include "LineFollower.h"
#include "PID_struct.h"
#include <math.h>
#define ONE_PI (3.14159265)
void motor_stop(void);

void Direct_Move(int target_x,int target_y);
void Position_Init(void);
extern int now_x, now_y, x_speed, y_speed;
#endif //GDUT_ROBOT_MOVE_CONTROL_H
