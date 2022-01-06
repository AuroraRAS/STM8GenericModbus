#include "stm8s105k4.h"

#include <stdbool.h>
#include <string.h>
#include <modbus.h>

static bool frame_timeout;

static uint8_t uart_rx_head;
static uint8_t uart_rx_size;
static uint8_t uart_rx_buffer[UINT8_MAX + 1];

static uint8_t uart_tx_head;
static uint8_t uart_tx_size;
static uint8_t uart_tx_buffer[UINT8_MAX + 1];

const char test[] = { "2333333" };

void frame_timer(void)
__interrupt 23
{
	frame_timeout = true;
	TIM4_SR &= 0b11111110;
}

void uart_rx(void)
__interrupt 21
{
	// frame timeout set to false
	frame_timeout = false;

	uart_rx_buffer[uart_rx_size++] = UART2_DR;

	// frame timer set to 0
	TIM4_CNTR = 0;
	// enable frame timer
	TIM4_CR1 |= 0b00000001;
}

void uart_tx(void)
__interrupt 20
{
	// clear TC bit
	UART2_SR &= 0b10111111;
	// we have data in the buffer need to send
	if(uart_tx_size != uart_tx_head)
	{
		// start data transmission
		UART2_DR = uart_tx_buffer[uart_tx_head++];
	}
	else
	{
		// transmission complete, stop TX interrupt
		UART2_CR2 &= 0b01111111;
	}
}

void uart_send(uint8_t *data, uint8_t size) {
	uint8_t i;
	// stop TX interrupt, update the uart TX buffer
	UART2_CR2 &= 0b01111111;
	for (i = 0; i < size; i++)
		uart_tx_buffer[(uint8_t)(uart_tx_head + i)] = data[i];
	uart_tx_size += size;
	// restart TX interrupt
	UART2_CR2 |= 0b10000000;
}

void main(void) {
	frame_timeout = false;
	uart_tx_head = 0;
	uart_tx_size = 0;
	uart_rx_head = 0;
	uart_rx_size = 0;

	/*
	 The format for each byte ( 11 bits ) in RTU mode is :
	 Coding System: 8–bit binary
	 Bits per Byte: 1 start bit
	 8 data bits, least significant bit sent first
	 1 bit for parity completion
	 1 stop bit
	 */
	// UART init
	// Set even parity
	UART2_CR1 &= 0b11111101;
	// Parity control enabled, 1 Start bit, 8 Data bits + 1 parity bit, 1 Stop bit
	UART2_CR1 |= 0b00010100;
	// RI,TX,RX enable
	UART2_CR2 |= 0b00101100;
	UART2_CR3 &= 0b11001111;
	// set baud to 9600 in 2MHz
	UART2_BRR1 = 0x0D;
	UART2_BRR2 = 0x01;
	//*/

	// Timer init
	// 4010us = (11bits * 1000000us / 9600baud) * 3.5chars
	TIM4_PSCR = 4;
	// 250.625 = 4010us / 2^TIM4_PSCR
	TIM4_ARR = 251;
	// enable TIM4 Update Interrupt
	TIM4_IER |= 0b00000001;
	// enable One-pulse mode
	TIM4_CR1 |= 0b00001000;
	// enable frame timer
	TIM4_CR1 |= 0b00000001;

	// globle interrupt enable
	__asm__("rim");

	uart_send(test, sizeof(test));
//	uart_send((volatile uint8_t*)0x48CD, 12);

	while (true) {
		if(uart_rx_size == uart_rx_head)
			continue;
		if (frame_timeout == false)
			continue;

		uint8_t request_buffer[UINT8_MAX + 1];
		uint8_t str_size;
		for (str_size = 0; uart_rx_size != uart_rx_head; str_size++) {
			request_buffer[str_size] = uart_rx_buffer[uart_rx_head++];
		}

		uint8_t response_buffer[UINT8_MAX + 1];

		if(modbus((struct modbus_response *)response_buffer, (struct modbus_request *)request_buffer))
		{
			if(((struct modbus_request *)request_buffer)->func==3)
				uart_send(response_buffer, ((struct modbus_response *)response_buffer)->data_len+5);
			else if(((struct modbus_request *)request_buffer)->func==6)
				uart_send(request_buffer, sizeof(struct modbus_request));
		}
		else
			uart_send("error", 6);
	}
}
