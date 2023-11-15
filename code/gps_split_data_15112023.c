#include <stdio.h>
#include <string.h>

int HAL_UART_SplitBuffer(char* str, char buf[9][9], const char* c);

int main() {
    //char origen[] = "$GPGGA,,,,,,0,00,99.99,,,,,,*48";
    char origen[] = "$GPRMC,204432.00,V,,,,,,,,,,N*7E";

    printf("origen: %s \n\r",origen);

    char buf[9][9];
    int len;
    
    len = HAL_UART_SplitBuffer(origen,buf,",");
    
    for (int i = 0; i<len;i++){
        printf("%d: %s \n\r",i,buf[i]);
    }
    return 0;
}



int HAL_UART_SplitBuffer(char* str, char buf[9][9], const char* c)
{
	int cont_buf = 0;
	char* token;
	token = strtok(str, c);
	while(token != NULL)
	{
		if(cont_buf < 10){
			strcpy(buf[cont_buf++], token);
			token = strtok(NULL, c);

		}else{
			break;
		}
	}
	return cont_buf;
}
