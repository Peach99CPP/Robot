//
// Created by peachRJ on 2021/3/15.
//

#ifndef GDUT_ROBOT_GY33_H
#define GDUT_ROBOT_GY33_H
#include "main.h"
#include "my_iic.h"
#include "my_usart.h"
#define s0_H  HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,GPIO_PIN_SET)
#define s0_L  HAL_GPIO_WritePin(GPIOE,GPIO_PIN_13,GPIO_PIN_RESET)
extern uint8_t rx_length;
extern uint8_t value[USART_RX_LEN];
extern uint8_t USART_RX_STA;
extern uint8_t GY_DATA[USART_RX_LEN];
extern uint8_t HAL_RXOK;
extern uint8_t sum,num;
#define	red 1
#define yellow 2
#define pink 3
#define white 4
#define black 5
#define green 6
#define mazarine 7
#define blue 8
void gy33_init(void);  //??????¡À????¨¦?????????¡§??????????9600
void led_change(uint8_t n);//??¡À?led????
void WHIBC_int(void);  //¡ã¡Á??????¡Á?
void GET_RGB(uint8_t *p_R,uint8_t *p_G,uint8_t *p_B);  //????RGB????
uint8_t GET_STATUS(uint16_t *lux,uint16_t *CT);//?????????????????¨°??????
void data_outtime(uint8_t n);//??¡À??????????¡À??????
void clear(void); //??GY_DATA[]????

#endif //GDUT_ROBOT_GY33_H
