//
// Created by peachRJ on 2021/1/29.
//

#ifndef GDUT_ROBOT_TIM_IT_H
#define GDUT_ROBOT_TIM_IT_H
#include "main.h"
#define Speed 15
extern int step;
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
#endif //GDUT_ROBOT_TIM_IT_H
