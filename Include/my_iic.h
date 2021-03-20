//
// Created by peachRJ on 2021/3/15.
//

#ifndef GDUT_ROBOT_MY_IIC_H
#define GDUT_ROBOT_MY_IIC_H

#include "main.h"

#define SCL_H  HAL_GPIO_WritePin(SCL_GPIO_Port,SCL_Pin,GPIO_PIN_SET)
#define SCL_L  HAL_GPIO_WritePin(SCL_GPIO_Port,SCL_Pin,GPIO_PIN_RESET)
#define SDA_H  HAL_GPIO_WritePin(SDA_GPIO_Port,SDA_Pin,GPIO_PIN_SET)
#define SDA_L  HAL_GPIO_WritePin(SDA_GPIO_Port,SDA_Pin,GPIO_PIN_RESET)
#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(uint32_t)8<<28;}
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(uint32_t)3<<28;}
#define read_SDA() HAL_GPIO_ReadPin(SDA_GPIO_Port,SDA_Pin)

void IIC_Start(void);

void IIC_Stop(void);

void IIC_Send_Byte(uint8_t txd);

uint8_t IIC_Read_Byte(unsigned char ack);

uint8_t IIC_Wait_Ack(void);

void IIC_Ack(void);

void IIC_NAck(void);

#endif //GDUT_ROBOT_MY_IIC_H
