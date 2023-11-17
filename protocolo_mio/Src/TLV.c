
#include "TLV.h"

//#include "mpu6050.h"

void tlv_response_template(const char grupos[][3], int i, char *tlv_sequence)
{

	switch(grupos[i][0]) {

	        case '0':
	                switch(grupos[i][1]){
	                        case '9':
	                        case 'A':
	                        case 'B':
	                        case 'C':
	                        case 'D':
	                        case 'E':
	                        case 'F':
	                        	sprintf(tlv_sequence,"161C1B%s22",grupos[i]);
	                        	break;
	                      }
	                      break;
	        case '1':

	                switch(grupos[i][1]){

	                        case '6':
	                        case '9':
	                        case 'B':
	                        case 'C':
	                        case 'F':
	                        	sprintf(tlv_sequence,"161C1B%s22",grupos[i]);
	                        	break;
	                      }
	                      break;
	        case '2':
	                switch(grupos[i][1]){
	                        case '2':
	                        	sprintf(tlv_sequence,"161C1B22");
	                        break;
	                      }
	                      break;
	    }
}

void tlv_set_values(const char grupos[][3], int i, char *hexa, UART_HandleTypeDef *huart, I2C_HandleTypeDef *hi2c3, const uint8_t tmp102_address, const uint8_t mpu6050_address) {

    switch(grupos[i][0]) {

        case '0':
                switch(grupos[i][1]){
                        case '9':

							sprintf( hexa, "09%08X", ( MPU6050_Read_Accel2( hi2c3, 0))  );
                        	break;

                        case 'A':

                        	sprintf( hexa, "0A%08X", ( MPU6050_Read_Accel2( hi2c3, 1))  );
                        	break;

                        case 'B':

                        	sprintf( hexa, "0B%08X", ( MPU6050_Read_Accel2( hi2c3, 2))  );
                        	break;
                        case 'C':

							sprintf( hexa, "0C%08X", ( read_temp2( hi2c3, tmp102_address))   ); //TMP102(
							break;

                        case 'D':

							sprintf( hexa, "0D%08X", ( read_temp2( hi2c3, tmp102_address))  ); //BMPE TEMP
							break;

                        case 'E':

							sprintf( hexa, "0E%08X", ( read_temp2( hi2c3, tmp102_address))  ); //BMPE HUM
							break;

                        case 'F':

							sprintf( hexa, "0F%08X", ( read_temp2( hi2c3, tmp102_address))  ); //BMPE ALT
							break;
                      }
                      break;
        case '1':

                switch(grupos[i][1]){

                        case '6':  //METER NO.
                        	int meter_no = 0x12345678;
                        	sprintf(hexa, "16%08X", meter_no);
                        	break;

                        case '9':  //PACKET SEQUENCE
                            //CODIGO
                        	// not necesary, static value
                        break;

                        case 'B':  //METER TYPE

                        	uint8_t A = HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_1);
                        	uint8_t B = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10);
                        	uint8_t C = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8);
                        	uint8_t D = HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_5);

                            sprintf(hexa, "1B%02X", A+B+C+D);
                            break;

                        case 'C':  //MODULE TIME GPS
                        	sprintf(hexa,"1C130301000000");
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
                                break;
                      }
                      break;
        case '2':
                switch(grupos[i][1]){
                        case '2':  //TRIGGER SOURCE
                            //CODIGO
							sprintf(hexa,"223141");
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

	}

	if (mode==0){
		return sum;
	}else{
		uint8_t checksum = ((singleCharToDecimal(msg[len-2])) << 4) | (singleCharToDecimal(msg[len-1]));
		return (checksum == sum) ? 1 : 0;
	}
    //return sum;
}

