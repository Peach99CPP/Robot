//
// Created by peachRJ on 2021/3/15.
//

#ifndef GDUT_ROBOT_MY_USART_H
#define GDUT_ROBOT_MY_USART_H
#include "main.h"
#include "my_iic.h"
void USART_send_byte(uint8_t byte);//
void USART_Send(uint8_t *Buffer, uint8_t Length);//
void USART_Send_bytes(uint8_t *Buffer, uint8_t Length);//

#endif //GDUT_ROBOT_MY_USART_H
