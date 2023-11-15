#include "tmp102.h"

uint16_t Error_NoDevice = 0xF1FF;
uint16_t Error_NoData = 0xF0FF;

uint8_t ErrorMSG1[] = "No device \n\r";
uint8_t ErrorMSG2[] = "No data \n\r";

char Buffer[25] = {0};
uint8_t buf[12];
const uint8_t reg_temp = 0x00; //tmp102 give to me 8 bits value
HAL_StatusTypeDef ret;
float temp_c;
int16_t val;

uint8_t data_tx[2];
uint8_t data_rx[15];


void read_temp(UART_HandleTypeDef *huart, I2C_HandleTypeDef *hi2c3, const uint8_t tmp102_address){
	  buf[0] = reg_temp;
	  ret = HAL_I2C_Master_Transmit(hi2c3, tmp102_address, buf, 1, HAL_MAX_DELAY);
	  if (ret != HAL_OK){
		  HAL_UART_Transmit(huart, ErrorMSG1, sizeof(ErrorMSG1), 10000);
	  }else{
		  ret = HAL_I2C_Master_Receive(hi2c3,tmp102_address, buf, 2, HAL_MAX_DELAY);
		  if (ret != HAL_OK){
		  		  HAL_UART_Transmit(huart, ErrorMSG2, sizeof(ErrorMSG2), HAL_MAX_DELAY);
		  	  }else{
		  		  //revise the datasheet
		  		  val = ((int16_t)buf[0]<<4) | (buf[1]>>4);

		  		  if ( val > 0x7FF){
		  			  val |= 0xF000;
		  		  }
		  		  temp_c = val * 0.0625;

		          // Convert temperature to decimal format
		          temp_c *= 100;
		          sprintf((char*)buf,
		                "\r\n %u.%u C \r\n",
		                ((unsigned int)temp_c / 100),
		                ((unsigned int)temp_c % 100));
		          HAL_UART_Transmit(huart, buf, strlen((char*)buf), HAL_MAX_DELAY);


		  	  }
	  }
}


int16_t read_temp2(I2C_HandleTypeDef *hi2c3, const uint8_t tmp102_address){
	  buf[0] = reg_temp;
	  ret = HAL_I2C_Master_Transmit(hi2c3, tmp102_address, buf, 1, HAL_MAX_DELAY);
	  if (ret != HAL_OK){
		  return Error_NoDevice;
	  }else{
		  ret = HAL_I2C_Master_Receive(hi2c3,tmp102_address, buf, 2, HAL_MAX_DELAY);
		  if (ret != HAL_OK){
		  		  return Error_NoData;
		  	  }else{

		  		  val = ((uint16_t)buf[0]<<4) | (buf[1]>>4);

		  		  if ( val > 0x7FF){
		  			  val |= 0xF000;
		  		  }
		  		  return val;
		  	  }
	  }
}


void MPU6050_Init(I2C_HandleTypeDef *hi2c3, const uint8_t mpu6050_address)
{
	data_tx[0] = 0x6B;
	data_tx[1] = 0x00;
	HAL_I2C_Master_Transmit(hi2c3, mpu6050_address, data_tx, 2, 100);

	data_tx[0] = 0x19;
	data_tx[1] = 0x07;
	HAL_I2C_Master_Transmit(hi2c3, mpu6050_address, data_tx, 2, 100);
}

int16_t mpu_read_data(I2C_HandleTypeDef *hi2c3, const uint8_t mpu6050_address)
{
		data_tx[0] = 0x3B;
		data_tx[1] = 0x00;

		ret =HAL_I2C_Master_Transmit(hi2c3, mpu6050_address, &data_tx[0], 1, 100);
		if(ret != HAL_OK){
			return Error_NoDevice;
		}else{
			ret = HAL_I2C_Master_Receive(hi2c3, mpu6050_address, data_rx, 14, 100);
			if(ret != HAL_OK){
				return Error_NoData;
			}else{
				return (int16_t)(data_rx[0]<<8 | data_rx[1]);
			}

		}
}

void mpu_read_data2(UART_HandleTypeDef *huart, I2C_HandleTypeDef *hi2c3, const uint8_t mpu6050_address)
{
		uint8_t buf_mpu[120];
		data_tx[0] = 0x3B;
		data_tx[1] = 0x00;

		ret =HAL_I2C_Master_Transmit(hi2c3, mpu6050_address, &data_tx[0], 1, 100);
		if(ret != HAL_OK){
			HAL_UART_Transmit(huart, ErrorMSG1, sizeof(ErrorMSG1), HAL_MAX_DELAY);
		}else{
			ret = HAL_I2C_Master_Receive(hi2c3, mpu6050_address, data_rx, 14, 100);
			if(ret != HAL_OK){
				HAL_UART_Transmit(huart, ErrorMSG2, sizeof(ErrorMSG2), HAL_MAX_DELAY);
			}else{

		          sprintf((char*)buf_mpu,
		                "\r\n a_x: 0x%08X | a_y: 0x%08X | a_z: 0x%08X \r\n",
		                ((unsigned int)(data_rx[0]<<8 | data_rx[1]) ),
						((unsigned int)(data_rx[2]<<8 | data_rx[3]) ),
						((unsigned int)(data_rx[4]<<8 | data_rx[5]) )
						);
		          HAL_UART_Transmit(huart, buf_mpu, strlen((char*)buf_mpu), HAL_MAX_DELAY);
			}
		}
}


