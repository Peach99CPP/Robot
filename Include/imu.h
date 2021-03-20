//
// Created by peachRJ on 2021/2/7.
//

#ifndef GDUT_ROBOT_IMU_H
#define GDUT_ROBOT_IMU_H
#define Data_Size 199

#include <stdlib.h>

void Imu_Init(void);

struct Imu {
    float yaw;
    float roll;
    float pitch;

};
extern struct Imu imu;

void turn_angle(float target_angle);

extern float now_angle,target_angle;
#endif //GDUT_ROBOT_IMU_H
