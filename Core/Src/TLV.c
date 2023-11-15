
#include "TLV.h"
//#include "mpu6050.h"

void tlv_response_template(const char grupos[][3], int i, char *tlv_sequence)
{

	switch(grupos[i][0]) {

	        case '0':
	                switch(grupos[i][1]){
	                        case 'B': //METER READING
	                            //CODIGO
	                        	break;

	                        case 'D': //MONTHLY FROZEN ACUMULATIVE FLOW
	                        	//CODIGO

	                        	char info_0D[] = "161D0D141B120B1A3323";
	                        	//char info_0D[] = "0D";
	                        	sprintf(tlv_sequence,"%s",info_0D);
	                        	break;

	                        case 'E': //YEAR FROZEN ACUMULATIVE FLOW
	                        	//CODIGO
	                        	char info_0E[] = "161D0E141B120B1A3323";
	                        	//char info_0E[] = "0E";
	                        	sprintf(tlv_sequence,"%s",info_0E);
	                        	break;
	                      }
	                      break;
	        case '1':

	                switch(grupos[i][1]){

	                        case '2':  //METERING MODE
	                        	char info_12[] = "12";
	                        	sprintf(tlv_sequence,"%s",info_12);
	                        	break;

	                        case '3':  //MAXIMUM MEASUREMENT VALUE
	                            //CODIGO
	                        	break;

	                        case '4':  //PULSE CONSTANT
	                        	break;

	                        case '6':  //METER NO.
	                        	break;

	                        case '8':  //VERSION INFO
	                            //CODIGO
	                        	break;

	                        case '9':  //PACKET SEQUENCE
	                            //CODIGO
	                        	// not necesary, static value
	                        break;

	                        case 'A':  //BATERRY VOLTAJE
	                            //CODIGO
	                        	char info_1A[] = "1A";
	                        	sprintf(tlv_sequence,"%s",info_1A);
	                        	break;

	                        case 'B':  //METER TYPE
	                            break;

	                        case 'C':  //MODULE TIME
	                            //CODIGO
								char info_1C[] = "161C1B120B141A3323";
								sprintf(tlv_sequence,"%s",info_1C);
	                        	break;

	                        case 'D':  //FROZEN DATA TIME
	                            //CODIGO
	                        	break;

	                        case 'F': //VALVE CONTROL
	                        	char info_1F[] = "1F";
	                        	sprintf(tlv_sequence,"%s%s",info_1F);
	                            break;
	                      }
	                      break;
	        case '2':
	                switch(grupos[i][1]){
	                        case '3':  //TRIGGER SOURCE
	                            //CODIGO
	                        	char info_1A[] = "23";
	                        	sprintf(tlv_sequence,"%s",info_1A);

	                        break;
	                      }
	                      break;
	        case '3':
	                switch(grupos[i][1]){
	                        case '3': //STATUS WORD
	                            //CODIGO
	                        	char info_1A[] = "33";
	                        	sprintf(tlv_sequence,"%s",info_1A);
	                        	break;
	                      }
	                      break;
	    }
}

void tlv_set_values(const char grupos[][3], int i, char *hexa, UART_HandleTypeDef *huart, I2C_HandleTypeDef *hi2c3, const uint8_t tmp102_address, const uint8_t mpu6050_address) {

    switch(grupos[i][0]) {

        case '0':
                switch(grupos[i][1]){
                        case 'B': //METER READING
                            //CODIGO

							sprintf( hexa, "0B%08X", ( mpu_read_data( hi2c3, mpu6050_address))  );
                        	break;

                        case 'D': //MONTHLY FROZEN ACUMULATIVE FLOW

                        	sprintf( hexa, "0D%08X", ( mpu_read_data( hi2c3, mpu6050_address))  );
                        	break;

                        case 'E': //YEAR FROZEN ACUMULATIVE FLOW

                        	sprintf( hexa, "0E%08X", ( mpu_read_data( hi2c3, mpu6050_address))  );
                        	break;
                      }
                      break;
        case '1':

                switch(grupos[i][1]){

                        case '2':  //METERING MODE
                            uint8_t Boton3_state = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8);
                            uint8_t Boton4_state = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5);
                            uint8_t Boton5_state = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_3);

                            uint8_t result1 =  (Boton5_state << 2) | (Boton4_state << 1) | Boton3_state  ;

                            sprintf(hexa, "12%02X", result1 );
                        	break;

                        case '3':  //MAXIMUM MEASUREMENT VALUE
                            //CODIGO
                        	break;

                        case '4':  //PULSE CONSTANT
                            uint8_t Boton6_state = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_1);
                            uint8_t Boton7_state = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_2);

                            uint8_t result2 =  (Boton7_state << 1) | Boton6_state  ;

                            sprintf(hexa, "14%02X", result2+1  );
                        	break;

                        case '6':  //METER NO.
                        	int meter_no = 0x12345678;

                            //sprintf(msg_payload + strlen(msg_payload), "16%08X", meter_no);
                        	sprintf(hexa, "16%08X", meter_no);
                        	break;

                        case '8':  //VERSION INFO
                            //CODIGO
                        	char ver_info[] = "98134841432d4d4c572d413139412056312e322e31";
                        	sprintf(hexa,"18%s",ver_info);
                        	break;

                        case '9':  //PACKET SEQUENCE
                            //CODIGO
                        	// not necesary, static value
                        break;

                        case 'A':  //BATERRY VOLTAJE
                            //CODIGO
							sprintf( hexa, "1A%04X", ( read_temp2( hi2c3, tmp102_address))  );
                        break;

                        case 'B':  //METER TYPE
                            uint8_t Boton1_state = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1);
                            uint8_t Boton2_state = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10);
                            uint8_t result3 =  (Boton2_state << 1) | Boton1_state ;

                            sprintf(hexa, "1B%02X", result3  );
                            break;

                        case 'C':  //MODULE TIME
                            //CODIGO
                        	// 2023 NOV 10 00:00:00
                        	char mod_time[] = "170B10000000";
                        	sprintf(hexa,"1C%s",mod_time);
                        break;

                        case 'D':  //FROZEN DATA TIME
                            //CODIGO
                        	// 2023 NOV 10 00:00:00
                        	char frozen_time[] = "170B10";
                        	sprintf(hexa,"1D%s",frozen_time);
                        break;

                        case 'F': //VALVE CONTROL
                            	if (strcmp("00", grupos[i+1]) == 0){
                                	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
                                }else if(strcmp("01", grupos[i+1]) == 0){
                                    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_SET);
                                }else if(strcmp("02", grupos[i+1]) == 0){
                                    HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_11);
                                }

                                sprintf(hexa + strlen(hexa), "1F%s", grupos[i+1]);
                                //return msg_payload;
                                break;
                      }
                      break;
        case '2':
                switch(grupos[i][1]){
                        case '3':  //TRIGGER SOURCE
                            //CODIGO
							char status_word[] = "FF";
							sprintf(hexa,"23%s",status_word);
							break;
							break;
                      }
                      break;
        case '3':
                switch(grupos[i][1]){
                        case '3': //STATUS WORD
                            //CODIGO
                        	char status_word[] = "FFFF";
                        	sprintf(hexa,"33%s",status_word);
                        	break;
                      }
                      break;
    }



}

void divideCadenaEnGrupos(const char *cadena, char grupos[][3], int longitudGrupo) {
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


void payload_msg(char *cadena, const char *data_marks[], UART_HandleTypeDef *huart, I2C_HandleTypeDef *hi2c3, const uint8_t tmp102_address, const uint8_t mpu6050_address)
{

	uint8_t groupSize = 2;
	char buf_tx[300];

	uint8_t MSG1[] = " \r\n";
	uint8_t len = strlen(cadena)/groupSize;

	char grupos[len][groupSize+1]; // Arreglo bidimensional para almacenar los grupos de 3 caracteres

	HAL_UART_SplitChar(cadena, grupos, groupSize);

    char hexa[60]= "";
    char msg_tlv[300] = "";

    HAL_UART_Transmit(huart, MSG1, sizeof(MSG1), 10);

    char tlv_sequence[120] ="";

    tlv_response_template(grupos, 1, tlv_sequence);

    sprintf(buf_tx, "\r\n tlv_sequence: %s \r\n", tlv_sequence);
    HAL_UART_Transmit(huart, (uint8_t *)buf_tx, strlen(buf_tx), 10);

    memset(grupos, 0, sizeof(grupos));

    len = strlen(tlv_sequence)/groupSize;
    //grupos[len][groupSize+1];

    HAL_UART_SplitChar(tlv_sequence, grupos, groupSize);

	// Ahora los grupos divididos están en la matriz grupos
	for (int i = 0; i < len; i++) {
		for (int j=0; j< 16  ; j++){
			if( strcmp(data_marks[j],grupos[i] )== 0 ){

				tlv_set_values(grupos, i, hexa, huart, hi2c3, tmp102_address, mpu6050_address);
				strcat(msg_tlv, hexa);
				memset(hexa, 0, sizeof(hexa));
				break;
			}
		}
	}
	memset(buf_tx, 0, sizeof(buf_tx));

	char tlv[400]="";
	char cs[20]="";

	sprintf(tlv, "2419%02X%s", ( (uint8_t)(strlen(msg_tlv))>>1), msg_tlv);

	sprintf(cs, "%02X", verifyChecksum(tlv,0) );
	strcat(tlv,cs);

	HAL_UART_Transmit(huart, (uint8_t *)tlv, strlen(tlv), HAL_MAX_DELAY);

}

uint8_t singleCharToDecimal(char caracter){
    if (isdigit(caracter))
        return caracter - '0';
    return 10 + (toupper(caracter) - 'A');
}

uint8_t verifyChecksum2(char *msg, uint8_t mode){
	//mode 0 = just sum - for generate checksum
	//mode 1 =  verify checksum for incoming message
	uint8_t len = strlen(msg);

    if (len < 2 || len % 2 != 0) {
        // Invalid length
        return 0;
    }

	uint16_t sum = 0;
	len = strlen(msg);

	for (uint8_t i = 0; i < len-2; i += 2) {
		uint8_t byte1 = singleCharToDecimal(msg[i]);
		uint8_t byte2 = singleCharToDecimal(msg[i + 1]);
		uint8_t value = (byte1 << 4) | byte2;
		sum += value;
	}

	if (mode==0){
		return sum;
	}else{
		uint8_t checksum = ((singleCharToDecimal(msg[len-2])) << 4) | (singleCharToDecimal(msg[len-1]));
		return (checksum == sum) ? 1 : 0;
	}
}

uint8_t verifyChecksum(char *msg, uint8_t mode){
	//mode 0 = just sum - for generate checksum - summ all characters
	//mode 1 =  verify checksum for incoming message - ignore last byte
	uint8_t len = strlen(msg);

    if (len < 2 || len % 2 != 0) {
        // Invalid length
        return 0;
    }

    uint8_t last = (mode) ? 2 : 0;

	uint8_t sum = 0;
	for (uint8_t i = 0; i < len - last; i += 2) {
		uint8_t byte1 = singleCharToDecimal(msg[i]);
		uint8_t byte2 = singleCharToDecimal(msg[i + 1]);
		uint8_t value = (byte1 << 4) | byte2;
		sum += value;
		if (last){
		    //printf("%d: %02X \n\r", i, value );
		}
	}
    return sum;
}

