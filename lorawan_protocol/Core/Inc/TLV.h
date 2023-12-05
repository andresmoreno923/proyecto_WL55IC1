#ifndef INC_TLV_H_
#define INC_TLV_H_


#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdint.h>

void TLV_payload(uint8_t *msg_rx, uint8_t msg_len);
uint8_t TLV_packet_length(uint8_t msg_rx);
uint8_t TLV_set_values(uint8_t msg_rx, uint8_t indx);

#endif /* INC_TLV_H_ */
