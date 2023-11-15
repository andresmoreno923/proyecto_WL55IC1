

#ifndef INC_COMMON_H_
#define INC_COMMON_H_

#include "main.h"

struct data_sctruc {
	//data_time
	//tag_1C
    uint8_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
    uint8_t met_mode;  	//tag_0x12;
    uint8_t pul_const;  //tag_0x14;
    uint32_t meter_no;  //tag_0x16;
    char ver_info[];	//tag_0x18;
    uint16_t bat_volt;  //tag_0x1A
    uint8_t met_type;  	//tag_0x1B;
    uint8_t valv_cont;  //tag_0x1F;
    uint8_t tgg_source; //tag_0x23;

    uint8_t


    uint8_t tag_0x18[255];        // Tamaño: n bytes (tamaño máximo 255)
    uint8_t tag_0x19;            // Tamaño: 1 byte
    uint16_t tag_0x1A;           // Tamaño: 2 bytes
    uint8_t tag_0x1B;            // Tamaño: 1 byte
    uint8_t tag_0x1C[6];         // Tamaño: 6 bytes
};

#endif /* INC_COMMON_H_ */
