#ifndef MODBUS_H_
#define MODBUS_H_

#include <stdint.h>
#include <stdbool.h>
#include <asm/stm8/features.h>

struct modbus_response
{
	uint8_t dev_addr;
	uint8_t func;
	uint8_t data_len;
	uint8_t data[];
};

struct modbus_request
{
	uint8_t dev_addr;
	uint8_t func;
	uint8_t reg_addr_hi;
	uint8_t reg_addr_lo;
	union
	{
		uint8_t reg_count_hi;
		uint8_t write_data_hi;
	};
	union
	{
		uint8_t reg_count_lo;
		uint8_t write_data_lo;
	};
	uint8_t crc_lo;
	uint8_t crc_hi;
};

bool modbus(struct modbus_response *response, struct modbus_request *request, uint8_t dev_addr);

#endif /* MODBUS_H_ */
