
#ifndef INC_BME280_H_
#define INC_BME280_H_

#include "main.h"

#define CTRLMEASREG 0x74
#define CTRLMEASVAL 0x25
#define CONFIGREG 0x75
#define CONFIGVAL 0xA0
#define CTRLHUMREG 0x72
#define CTRLHUMVAL 0x01
#define COMPTEMPPRES 0x88
#define COMPHUMINIT 0xA0
#define COMPHUMREST 0xE1
#define RAWREAD 0xF7

void BME280_CONFIG_SETUP(SPI_HandleTypeDef *hspi2);
void BME280_GET_COMP_VALS(SPI_HandleTypeDef *hspi2);
void BME280_CALC_FINAL_VALS(SPI_HandleTypeDef *hspi2);

#endif /* INC_BME280_H_ */
