#ifndef TMP102_H
#define TMP102_H

#include "main.h"
#include <stdio.h>  // Para la función sprintf

void read_temp(UART_HandleTypeDef *huart, I2C_HandleTypeDef *hi2c3, const uint8_t tmp102_address);
int16_t read_temp2( I2C_HandleTypeDef *hi2c3, const uint8_t tmp102_address);

void MPU6050_Init(I2C_HandleTypeDef *hi2c3, const uint8_t mpu6050_address);
int16_t mpu_read_data(I2C_HandleTypeDef *hi2c3, const uint8_t mpu6050_address);

void mpu_read_data2(UART_HandleTypeDef *huart, I2C_HandleTypeDef *hi2c3, const uint8_t mpu6050_address);

uint16_t MPU6050_Read_Accel2(I2C_HandleTypeDef *hi2c3, uint8_t mode);
void MPU6050_Init2 (I2C_HandleTypeDef *hi2c3);

#endif /* TMP102_H */
