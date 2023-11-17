

#include "nmea.h"


uint8_t decodeRMC (char *RMCbuffer, RMCSTRUCT *rmc){
    uint8_t hr=0,min=0,day=0,mon=0,yr=0;
    uint8_t inx = 0;
	char buffer[15];
	int i = 0;
	//valid ?
	while (RMCbuffer[inx] != ',') inx++;  // 1st ,
	inx++;
	while (RMCbuffer[inx] != ',') inx++;  // After time ,
	inx++;
	if (RMCbuffer[inx] == 'A')  // Here 'A' Indicates the data is valid, and 'V' indicates invalid data
	{
		rmc->isValid = 1;
	}
	else
	{
		rmc->isValid =0;
		return 0;
	}
	
	// Get time
	inx = 0;
	while (RMCbuffer[inx] != ',') inx++;
	inx++;
	i=0;
	memset(buffer, '\0', 15);
	while (RMCbuffer[inx] != ',')
	{
		buffer[i] = RMCbuffer[inx];
		i++;
		inx++;
	}

	rmc->time_.hour = (atoi(buffer)/10000);  
	rmc->time_.min = ((atoi(buffer)/100)%100);  
	rmc->time_.sec = ((atoi(buffer))%100);   

	// Get latitude
	inx++;
	while (RMCbuffer[inx] != ',') inx++;
	inx++;
	i=0;
	memset(buffer, '\0', 15);
	while (RMCbuffer[inx] != ',')
	{
		buffer[i] = RMCbuffer[inx];
		i++;
		inx++;
	}

	rmc->lat_.deg = ((atoi(buffer)/100)%1000);
	rmc->lat_.min = ((atoi(buffer))%100);
	uint8_t j;
	while (buffer[j] != '.') j++;   // Figure out how many digits before the decimal
	j++;
	rmc->lat_.sec = ((atoi(buffer+j)/100)%100);
	
	//indicate N/s
	inx++;
	rmc->lat_.NS = RMCbuffer[inx];
	
	// Get longitude
	inx+=2;
	i=0;
	memset(buffer, '\0', 15);
	while (RMCbuffer[inx] != ',')
	{
		buffer[i] = RMCbuffer[inx];
		i++;
		inx++;
	}

	rmc->long_.deg = ((atoi(buffer)/100)%1000);
	rmc->long_.min = ((atoi(buffer))%100);
	j=0;
	while (buffer[j] != '.') j++;   // Figure out how many digits before the decimal
	j++;
	rmc->long_.sec = ((atoi(buffer+j)/100)%100);
    //rmc->longitude = buffer;
    
    //indicate W/E
	inx++;
	rmc->long_.EW = RMCbuffer[inx];
	
	//others dates
	while (RMCbuffer[inx] != ',') inx++;  // 8vo ,
	inx++;
	while (RMCbuffer[inx] != ',') inx++;  // 9mo ,
	inx++;
	while (RMCbuffer[inx] != ',') inx++;  // 9mo ,
	inx++;
	
	// Get date
	i=0;
	memset(buffer, '\0', 15);
	while (RMCbuffer[inx] != ',')
	{
		buffer[i] = RMCbuffer[inx];
		i++;
		inx++;
	}
	inx++;
	
	rmc->date_.day = (atoi(buffer)/10000);  
	rmc->date_.mon = ((atoi(buffer)/100)%100);  
	rmc->date_.year = ((atoi(buffer))%100);

	return 1;
}
