
#ifndef INC_NMEA_H_
#define INC_NMEA_H_


#include <stdio.h>
#include <stdint.h>
#include "string.h"
#include "stdlib.h"

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

uint8_t decodeRMC (char *RMCbuffer, RMCSTRUCT *rmc);




#endif /* INC_NMEA_H_ */
