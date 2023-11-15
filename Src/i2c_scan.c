/*
 * i2c_scan.c
 *
 *  Created on: Nov 3, 2023
 *      Author: SE0019
 */

#include "i2c_scan.h"
#include <stdio.h>  // Para la función sprintf


void transmitirMensajes1(UART_HandleTypeDef *huart, I2C_HandleTypeDef *hi2c) {
    uint8_t StartMSG[] = "Start\n";
    uint8_t Space[] = "-";
    uint8_t EndMSG[] = "End\r\n";
    char Buffer[25] = {0};
    HAL_StatusTypeDef ret;

    HAL_UART_Transmit(huart, StartMSG, sizeof(StartMSG), 10000);

    for (int i = 1; i < 128; i++) {
        ret = HAL_I2C_IsDeviceReady(hi2c, (uint16_t)(i << 1), 3, 5);
        if (ret != HAL_OK) {
            HAL_UART_Transmit(huart, Space, sizeof(Space), 10000);
        } else {
            sprintf(Buffer, "0x%X", i);
            HAL_UART_Transmit(huart, Buffer, sizeof(Buffer), 10000);
        }
    }

    HAL_UART_Transmit(huart, EndMSG, sizeof(EndMSG), 10000);

}


// Declaración de la función
void transmitirMensajes2(UART_HandleTypeDef *huart, I2C_HandleTypeDef *hi2c, uint8_t *buffer, size_t buffer_size) {
    uint8_t StartMSG[] = "Start\n";
    uint8_t Space[] = "_";
    uint8_t EndMSG[] = "End\n";
    char Buffer[25] = {0};
    HAL_StatusTypeDef ret;

    HAL_UART_Transmit(huart, StartMSG, sizeof(StartMSG), 10000);

    int i_values[128];
    int i_count = 0;

    for (int i = 1; i < 128; i++) {
        ret = HAL_I2C_IsDeviceReady(hi2c, (uint16_t)(i << 1), 3, 5);
        if (ret != HAL_OK) {
            HAL_UART_Transmit(huart, Space, sizeof(Space), 10000);
        } else {
        	sprintf(Buffer, "0x%X", i);
        	i_values[i_count] = i;
        	i_count++;
        }
    }



    uint8_t tmp102_address[i_count];


	HAL_UART_Transmit(huart, (uint8_t*)Buffer, strlen(Buffer), HAL_MAX_DELAY);
	strcpy(buffer, Buffer);
    HAL_UART_Transmit(huart, EndMSG, sizeof(EndMSG), 10000);

}




