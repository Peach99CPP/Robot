//
// Created by peachRJ on 2021/1/29.
//

#ifndef GDUT_ROBOT_MOTOR_H
#define GDUT_ROBOT_MOTOR_H
#include "main.h"
short read_num(int flag);
void get_num(void );
void PWM_Enable(void);
void set_PWM(int flag,int output);
void Target_Speed(void );
void speed_communication(unsigned short int motor_mode);
void Speed_set(int vx,int vy,int vw);
#endif //GDUT_ROBOT_MOTOR_H
