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

#define MPU6050_ADDR 0xD0

#define SMPLRT_DIV_REG 0x19
#define GYRO_CONFIG_REG 0x1B
#define ACCEL_CONFIG_REG 0x1C
#define ACCEL_XOUT_H_REG 0x3B
#define TEMP_OUT_H_REG 0x41
#define GYRO_XOUT_H_REG 0x43
#define PWR_MGMT_1_REG 0x6B
#define WHO_AM_I_REG 0x75

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

void MPU6050_Init2 (I2C_HandleTypeDef *hi2c3)
{
	uint8_t check;
	uint8_t Data;

	// check device ID WHO_AM_I

	HAL_I2C_Mem_Read (hi2c3, MPU6050_ADDR,WHO_AM_I_REG,1, &check, 1, 1000);

	if (check == 104)  // 0x68 will be returned by the sensor if everything goes well
	{
		// power management register 0X6B we should write all 0's to wake the sensor up
		Data = 0;
		HAL_I2C_Mem_Write(hi2c3, MPU6050_ADDR, PWR_MGMT_1_REG, 1,&Data, 1, 1000);

		// Set DATA RATE of 1KHz by writing SMPLRT_DIV register
		Data = 0x07;
		HAL_I2C_Mem_Write(hi2c3, MPU6050_ADDR, SMPLRT_DIV_REG, 1, &Data, 1, 1000);

		// Set accelerometer configuration in ACCEL_CONFIG Register
		// XA_ST=0,YA_ST=0,ZA_ST=0, FS_SEL=0 -> � 2g
		Data = 0x00;
		HAL_I2C_Mem_Write(hi2c3, MPU6050_ADDR, ACCEL_CONFIG_REG, 1, &Data, 1, 1000);

		// Set Gyroscopic configuration in GYRO_CONFIG Register
		// XG_ST=0,YG_ST=0,ZG_ST=0, FS_SEL=0 -> � 250 �/s
		Data = 0x00;
		HAL_I2C_Mem_Write(hi2c3, MPU6050_ADDR, GYRO_CONFIG_REG, 1, &Data, 1, 1000);
	}
}


uint16_t MPU6050_Read_Accel2(I2C_HandleTypeDef *hi2c3, uint8_t mode)
{
	uint8_t Rec_Data[6];


	// Read 6 BYTES of data starting from ACCEL_XOUT_H register

	HAL_I2C_Mem_Read (hi2c3, MPU6050_ADDR, ACCEL_XOUT_H_REG, 1, Rec_Data, 6, 1000);

	/*** convert the RAW values into acceleration in 'g'
	     we have to divide according to the Full scale value set in FS_SEL
	     I have configured FS_SEL = 0. So I am dividing by 16384.0
	     for more details check ACCEL_CONFIG Register              ****/

	switch(mode) {
	        case 0:
	            return (int16_t)(Rec_Data[0] << 8 | Rec_Data [1]);

	        case 1:
	        	return (int16_t)(Rec_Data[2] << 8 | Rec_Data [3]);

	        case 2:
	        	return (int16_t)(Rec_Data[4] << 8 | Rec_Data [5]);
	 return 0;

	}
}

