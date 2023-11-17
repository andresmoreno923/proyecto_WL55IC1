#ifndef INC_UART_STRING_H_
#define INC_UART_STRING_H_

#include "main.h"
#define LEN_BUF 4
#define LEN_DATA 5

void HAL_UART_ReadString(UART_HandleTypeDef *huart, char* buf_rx, uint16_t st_size);
void HAL_UART_SplitBuffer(char* str, char buf[LEN_BUF][LEN_DATA], const char* c);
void HAL_UART_SplitChar(const char *cadena, char grupos[][3], int longitudGrupo);

#endif
