/*
 * ublox_6m.h
 *
 *  Created on: Nov 3, 2023
 *      Author: SE0019
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "main.h"

#ifndef INC_UBLOX_6M_H_
#define INC_UBLOX_6M_H_


void Geo_update(UART_HandleTypeDef *huart, uint32_t *lat,  uint32_t *lon);

#endif /* INC_UBLOX_6M_H_ */
