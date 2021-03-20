//
// Created by peachRJ on 2021/2/5.
//

#ifndef GDUT_ROBOT_LINEFOLLOWER_H
#define GDUT_ROBOT_LINEFOLLOWER_H
#include "main.h"
#include "tim_it.h"
#include "stm32f1xx_it.h"
#include "stm32f1xx_hal_uart.h"
#include "PID_struct.h"
struct Line_Struct {
  uint16_t gray;
  float value;
  uint8_t num;
  uint8_t sign;
};
extern struct Line_Struct Line_Struct_N1;
void LFB_receive_Init(void);
void LFB_Send(void);
static uint8_t calculate_verify(const uint8_t *data, uint8_t length);
void UART4_IRQHandler(void) ;
void move_by_line(void);
#endif // GDUT_ROBOT_LINEFOLLOWER_H
