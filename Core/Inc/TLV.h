

#ifndef INC_TLV_H_
#define INC_TLV_H_


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "main.h"

#define MAX_TLV_LENGTH 6


typedef struct {
	unsigned char tag;
    unsigned char length;
    unsigned char *value;
} tlv_t;



void tlv_free(tlv_t *tlv);
void tlv_set_values(const char grupos[][3], int i, char *hexa, UART_HandleTypeDef *huart, I2C_HandleTypeDef *hi2c3, const uint8_t tmp102_address, const uint8_t mpu6050_address);

uint8_t verifyChecksum2(char *msg, uint8_t mode);
uint8_t verifyChecksum(char *msg, uint8_t mode);
uint8_t singleCharToDecimal(char caracter);

void payload_msg(char *cadena, const char *data_marks[], UART_HandleTypeDef *huart, I2C_HandleTypeDef *hi2c3, const uint8_t tmp102_address, const uint8_t mpu6050_address);
void tlv_response_template(const char grupos[][3], int i, char *tlv_sequence);

#endif /* INC_TLV_H_ */
