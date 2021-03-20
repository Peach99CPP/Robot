//
// Created by peachRJ on 2021/3/15.
//

#ifndef GDUT_ROBOT_SERVO_PCA9685_H
#define GDUT_ROBOT_SERVO_PCA9685_H
#include "main.h"
#define pca_adrr 0x80     //pca???¡¤

#define pca_mode1 0x0     //????
#define pca_pre   0xFE    //?????¡À????????254

#define LED0_ON_L 0x6
#define LED0_ON_H 0x7
#define LED0_OFF_L 0x8
#define LED0_OFF_H 0x9

void angle_control(uint8_t num,uint8_t angle);           //???¨²????????
void pca_write(uint8_t adrr,uint8_t data);
uint8_t pca_read(uint8_t adrr);
void PCA_MG9XX_Init(float hz,uint8_t angle);
void pca_setfreq(float freq);
void pca_setpwm(uint8_t num, uint32_t on, uint32_t off);

#endif //GDUT_ROBOT_SERVO_PCA9685_H
