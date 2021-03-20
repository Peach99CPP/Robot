
#include "imu.h"
#include "main.h"
#include "move_control.h"
#include "string.h"

uint8_t Data_set[Data_Size] = {0};
int len = 0;
extern UART_HandleTypeDef husart3;
extern DMA_HandleTypeDef hdma_usart3_rx;
struct Imu imu;
float now_angel,target_angle;

void turn_angle(float target_angle) {
    if (fabs(target_angle - now_angle) < 2) { ;
    }
}

void Imu_Init(void)//开启接收
{
    __HAL_UART_ENABLE_IT(&husart3, UART_IT_IDLE);
    HAL_UART_Receive_DMA(&husart3, Data_set, Data_Size);
}

void USART3_IRQHandler(void) {
    uint32_t flag_idle = 0;

    flag_idle = __HAL_UART_GET_FLAG(&husart3, UART_FLAG_IDLE);
    if ((flag_idle != RESET)) {
        __HAL_UART_CLEAR_IDLEFLAG(&husart3);

        HAL_UART_DMAStop(&husart3);
        uint32_t temp = __HAL_DMA_GET_COUNTER(&hdma_usart3_rx);
        len = Data_Size - temp;

        if (Data_set[0] == 0x55) {
            uint8_t sum = 0;
        }
        memset(Data_set, 0, len);
        len = 0;
    }
    HAL_UART_Receive_DMA(&husart3,Data_set,Data_Size);
    HAL_UART_IRQHandler(&husart3);
// Created by peachRJ on 2021/2/7.

//

}