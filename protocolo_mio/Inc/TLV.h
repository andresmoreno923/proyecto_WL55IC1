

#ifndef INC_TLV_H_
#define INC_TLV_H_


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "main.h"

#define MAX_TLV_LENGTH 6

typedef struct {
	uint8_t deg;
	uint8_t min;
	uint8_t sec;
	char NS;
}LATITUDE;

typedef struct {
	uint8_t deg;
	uint8_t min;
	uint8_t sec;
	char EW;
}LONGITUDE;

typedef struct {
	uint8_t hour;
	uint8_t min;
	uint8_t sec;
}TIME;

typedef struct {
	uint8_t year;
	uint8_t mon;
	uint8_t day;
}DATE;

typedef struct {
    TIME time_;
    LATITUDE lat_;
    LONGITUDE long_;
	DATE date_;
	uint8_t isValid;
}RMCSTRUCT;

typedef struct {
    uint16_t ax;
    uint16_t ay;
    uint16_t az;
}MPU6050;

typedef struct {
    uint16_t temp;
    uint16_t hum;
    uint16_t hPa;
}BME280;

typedef struct {
    uint16_t temp;
}TMP102;

typedef struct {
    char id_sensor;
    char id_error;
}ERROR_;

uint8_t decodeRMC (char *RMCbuffer, RMCSTRUCT *rmc);
void printRMCStruct(const RMCSTRUCT *data);


void tlv_set_values(const char grupos[][3], int i, char *hexa, UART_HandleTypeDef *huart, I2C_HandleTypeDef *hi2c3, const uint8_t tmp102_address, const uint8_t mpu6050_address);

uint8_t verifyChecksum2(char *msg, uint8_t mode);
uint8_t verifyChecksum(char *msg, uint8_t mode);

uint8_t singleCharToDecimal(char caracter);

void payload_msg(char *cadena, const char *data_marks[], UART_HandleTypeDef *huart, I2C_HandleTypeDef *hi2c3, const uint8_t tmp102_address, const uint8_t mpu6050_address);
void tlv_response_template(const char grupos[][3], int i, char *tlv_sequence);

#endif /* INC_TLV_H_ */
