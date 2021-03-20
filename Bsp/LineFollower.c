#include "LineFollower.h"
#include "main.h"
#include "PID_struct.h"
extern UART_HandleTypeDef huart4;
struct Line_Struct Line_Struct_N1;
float weight[10] = {-5, -4, -3, -2, -1, 1, 2, 3, 4, 5}; //权重---
static uint8_t calculate_verify(const uint8_t *data,
                                uint8_t length) { //和校验函数
    uint8_t i = 0;
    register uint16_t verify_value = 0;

    for (i = 0; i < length; i++
            )
        verify_value += data[i];

    return (uint8_t) (verify_value & 0XFF);
}

void LFB_receive_Init(void) { __HAL_UART_ENABLE_IT(&huart4, UART_IT_RXNE); }

void LFB_Send(void) {
    uint8_t getlinecom[] = {0xff, 0xff, 0x01, 0x02, 0x08, 0x0b}; // ID:0X01
    HAL_UART_Transmit(&huart4, getlinecom, 6, 0XFF);
}

void LFB_decode(struct Line_Struct *data, uint8_t *buffer, float *weight) {
    uint8_t i, a;
    float tmp = 0;
    data->gray = (buffer[5]) | (buffer[4] << 4) | ( uint16_t )(buffer[3] << 8);//转换成16位的再进行位移运算
    data->num = 0;
    for (i = 0; i < 10; i++
            ) {
        a = (data->gray >> i) & 0X01;
        data->num += a;
        tmp += a * weight[i];
    }
    if (data->num != 0)
        data->value = tmp / data->num;
    else
        data->value = 0;
}

void UART4_IRQHandler(void) {
    uint8_t Res;
    uint8_t id2 = 0;
    static uint8_t RxBuffer[10];
    static uint8_t data_cnt;
    static uint8_t state;
    if (UART4->SR & (1 << 5)) {
        Res = UART4->DR;
        if (state == 2) //两个0xff已接收
        {
            RxBuffer[data_cnt] = Res;
            if (data_cnt >= 6) {
                if (calculate_verify(RxBuffer, 6) == RxBuffer[6]) {
                    if (RxBuffer[0] == 0x01) {
                        LFB_decode(&Line_Struct_N1, RxBuffer, weight);
                    }
                }
                state = 0;
            }
            ++data_cnt;
        }
        else if (Res == 0xff && state == 0)
            state = 1;
        else if (state == 1 && Res == 0xff) {
            state = 2;
            data_cnt = 0;
        }
        else
            state = 0;
    }
}
void move_by_line(void)
{
    LFB_Send();//获取
    line_PID.measure= Line_Struct_N1.value;
    Position_PID_Calculation(&line_PID,&line_pid_param);
    motor_1.target+=line_PID.output;
    motor_2.target-=line_PID.output;
//    motor_3.target-=line_PID.output;
//    motor_4.target+=line_PID.output;
}
//
// Created by peachRJ on 2021/2/5.
//
