
#ifndef APPLICATION_USER_CORE_GLOBALS_H
#define APPLICATION_USER_CORE_GLOBALS_H

extern char buf_tx[300];
extern uint8_t msg_[27];

#define SIZE_payload 50 // Tamaño del array Buffer
#define SIZE_msg_tlv 15 // Tamaño del array Buffer

typedef struct {
	uint8_t deg;
	uint8_t min;
	uint16_t sec;
	uint8_t NS;
}LATITUDE;

typedef struct {
	uint8_t deg;
	uint8_t min;
	uint16_t sec;
	uint8_t EW;
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
    uint16_t a_in[4];
}ADS1115;

typedef struct {
    uint16_t temp;
    uint16_t hum;
    uint16_t hPa;
}BME280;

typedef struct {
    uint16_t temp;
}TMP102;

typedef struct {
	uint8_t id_sensor;
	uint8_t id_error;
}ERROR_;

typedef struct {
    uint8_t valid;
}VALID_;

typedef struct {
    uint8_t Buffer[SIZE_payload];
    uint8_t BufferSize;
}TLV_Responce;

// Declarar los struct con extern
extern LATITUDE lat;
extern LONGITUDE lon;
extern TIME time_stamp;
extern DATE date;
extern RMCSTRUCT rmc;
extern ADS1115 ads;
extern BME280 bme;
extern TMP102 tmp;
extern ERROR_ err;
extern VALID_ vqc;
extern TLV_Responce data;

#endif /* APPLICATION_USER_CORE_GLOBALS_H_ */
