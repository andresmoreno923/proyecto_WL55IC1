
#include "uart_string.h"

#include <string.h>

char buffer_rx[LEN_BUF][LEN_DATA];
char *token;

void HAL_UART_ReadString(UART_HandleTypeDef *huart, char* buf_rx, uint16_t st_size)
{
	uint16_t len;
	char c[1];
	--st_size;
	len = 0;
	do{
		HAL_UART_Receive(huart, (uint8_t*)c, 1, HAL_MAX_DELAY);
		if(c[0] == 8){
			if(len > 0){
				len--;
			}
		}
		else if((c[0] >= ' ')&&(c[0] <= '~')){
			if(len < st_size){
				buf_rx[len++] = c[0];
			}
		}
	}while(c[0] != 13);
	buf_rx[len] = 0;
}

void HAL_UART_SplitBuffer(char* str, char buf[LEN_BUF][LEN_DATA], const char* c)
{
	uint8_t cont_buf = 0;
	token = strtok(str, c);
	while(token != NULL)
	{
		if(cont_buf < LEN_BUF){
			strcpy(buf[cont_buf++], token);
			token = strtok(NULL, c);
		}else{
			break;
		}
	}
	cont_buf = 0;
}


void HAL_UART_SplitChar(const char *cadena, char grupos[][3], int longitudGrupo) {
    int len = strlen(cadena);
    int grupo_index = 0;

    for (int i = 0; i < len; i += longitudGrupo) {
        if (i + longitudGrupo <= len) {
            strncpy(grupos[grupo_index], cadena + i, longitudGrupo);
            grupos[grupo_index][longitudGrupo] = '\0'; // Agrega el carácter nulo al final
            grupo_index++;
        }
    }
}
