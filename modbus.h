#ifndef MODBUS_H_
#define MODBUS_H_

#include <stdint.h>
#include <stdbool.h>
#ifdef __SDCC
#include <asm/stm8/features.h>
#endif

#define READ_COIL_STATUS 01
#define READ_INPUT_STATUS 02
#define READ_HOLDING_REGISTERS 03
#define READ_INPUT_REGISTERS 04
#define WRITE_SINGLE_COIL 05
#define WRITE_SINGLE_REGISTER 06
#define WRITE_MULTIPLE_COILS 15
#define WRITE_MULTIPLE_REGISTERS 16

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
