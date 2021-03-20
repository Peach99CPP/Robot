//
// Created by peachRJ on 2021/1/29.
//

#include "tim_it.h"
#include "PID_struct.h"
#include "main.h"
#include "motor.h"

int step=0;
extern TIM_HandleTypeDef htim6;

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim == (&htim6)) {//10ms一次
        get_num();
        Speed_set(10,10,0);
        switch(step)
        {;}
        Target_Speed();
    }
}
