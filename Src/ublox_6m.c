/*
 * ublox_6m.c
 *
 *  Created on: Nov 3, 2023
 *      Author: SE0019
 */



#include "ublox_6m.h"




void Geo_update(UART_HandleTypeDef *huart, uint32_t *lat, uint32_t *lon){
	//char Buffer[60] = {0};

	srand(time(NULL));

//    sprintf(Buffer, "before lat: %d; long: -%d \n\r", lat, lon);
//    HAL_UART_Transmit(huart, Buffer, sizeof(Buffer), 10000);

	// Genera un número aleatorio entre 0 y RAND_MAX
	*lat = *lat + (rand()%101)- (rand()%101);
	*lon = *lon + (rand()%101)- (rand()%101);

//    sprintf(Buffer, "after lat: %d; long: -%d \n\r", lat, lon);
//    HAL_UART_Transmit(huart, Buffer, sizeof(Buffer), 10000);

}
