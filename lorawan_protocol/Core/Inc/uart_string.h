#ifndef INC_UART_STRING_H_
#define INC_UART_STRING_H_

#include "main.h"

#define LEN_BUF 4
#define LEN_DATA 5

void HAL_UART_ReadString(UART_HandleTypeDef *huart, char* buf_rx, uint16_t st_size);
//void HAL_UART_SplitBuffer(char* str, char buf[LEN_BUF][LEN_DATA], const char* c);
uint8_t HAL_UART_SplitBuffer(char* str, char buf[9][9], const char* c);


#endif
