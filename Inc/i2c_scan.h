/*
 * i2c_scan.h
 *
 *  Created on: Nov 3, 2023
 *      Author: SE0019
 */

#ifndef I2C_SCAN_H
#define I2C_SCAN_H

#include "main.h"

void transmitirMensajes1(UART_HandleTypeDef *huart, I2C_HandleTypeDef *hi2c);

void transmitirMensajes2(UART_HandleTypeDef *huart, I2C_HandleTypeDef *hi2c, uint8_t *buffer, size_t buffer_size);


#endif /* I2C_SCAN_H */

